#pragma once
#include <string.h>  // memcpy
#include <cstdlib>   // malloc and free
#include <new>       // bad_alloc

namespace MiniSTL { //命名空间

//一级配置器
class __malloc_alloc {
public:
    // alias declaration
    using malloc_handler = void (*)();//函数指针

private:
    //以下函数指针用以处理内存不足的情况
    static void *oom_malloc(size_t); //out of memory when malloc
    static void *oom_realloc(void *, size_t);//out of memory when realloc
    static malloc_handler __malloc_alloc_oom_handler;

public:
    // 简单allocate，如果失败就调用oom_malloc函数，成果就返回首地址
    static void *allocate(size_t n) {
        void *result = malloc(n);
        if (result == nullptr) result = oom_malloc(n);
        return result;
    }
    // 简单deallocate 对指针p所指向内存调用free，size_t自动传入
    static void deallocate(void *p, size_t /*n*/) { free(p); }
    
    // 简单reallocate
    static void *reallocate(void *p, size_t /*old_sz*/, size_t new_sz) {
        void *result = realloc(p, new_sz);
        if (result == nullptr) oom_realloc(p, new_sz);
        return result;
    }

    //模拟set_new_handler
    //原因在于并未使用new与delete配置内存，因此无法使用set_new_handler
    static malloc_handler set_malloc_handler(malloc_handler f) {
        malloc_handler old = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return old;
    }
};

//定义handler 空的处理方法
typename __malloc_alloc::malloc_handler
    __malloc_alloc::__malloc_alloc_oom_handler = nullptr;

void *__malloc_alloc::oom_malloc(size_t n) {
    malloc_handler new_alloc_handler;
    void *result;
    for (;;) {  //不断尝试释放、配置
        new_alloc_handler = __malloc_alloc_oom_handler;
        if (!new_alloc_handler) throw std::bad_alloc(); //如果没有设置__malloc_alloc_oom_handler处理方法 直接抛出异常
        (*new_alloc_handler)();  //否则调用handler，试图释放内存
        result = malloc(n);//尝试分配内存
        if (result) return result;
    }
}

// 基本一样的
void *__malloc_alloc::oom_realloc(void *p, size_t n) {
    malloc_handler new_alloc_handler;
    void *result;
    for (;;) {
        new_alloc_handler = __malloc_alloc_oom_handler;
        if (!new_alloc_handler) throw std::bad_alloc();
        (*new_alloc_handler)();
        result = realloc(p, n);
        if (result) return result;
    }
}
// alias
using malloc_alloc = __malloc_alloc;

// freelist参数设定
//区块上调边界，区块上限，freelist个数
// Effective C++所述enum惯用法
enum __freelist_setting {
    __ALIGN = 8,
    __MAX_BYTES = 128,
    __NFREELISTS = __MAX_BYTES / __ALIGN
};

// 第二级配置器
class __default_alloc {
private:
    // 将bytes上调至8的倍数
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes) + static_cast<size_t>(__ALIGN) - 1) &
                ~(static_cast<size_t>(__ALIGN) - 1));
    }

private:
    // free_list节点
    // 由于union特性，并不需要占用额外的内存
    union obj {
        union obj *free_list_link;  //指向下一节点
        char client_data[1];        //指向资源
    };

private:
    static obj *volatile free_list[__NFREELISTS];//volatile告诉编译器这个变量可能随时都被修改 不要用寄存器保存 可能会脏读
    // 决定使用第几号节点，从1起算
    static size_t FREELIST_INDEX(size_t bytes) {
        return (bytes + static_cast<size_t>(__ALIGN) - 1) /
                   static_cast<size_t>(__ALIGN) -
               1;
    }
    // 传回一个大小为n的对象，并且可能加入大小为n的其它区块到free_list
    static void *refill(size_t n);
    
    // 配置一大块空间，可容纳nobjs个大小为size的区块
    // nobjs可能会降低 以实际分配为准
    static char *chunk_alloc(size_t size, int &nobjs);

    // chunk allocation state
    static char *start_free;  //内存池起始位置，只在chunk_alloc()中变化
    static char *end_free;  //内存池结束位置，只在chunk_alloc()中变化
    static size_t heap_size;//一共分配的大小

public:
    static void *allocate(size_t n);
    static void deallocate(void *p, size_t n);
    static void *reallocate(void *p, size_t old_sz, size_t new_sz);
};

char *__default_alloc::start_free = nullptr;
char *__default_alloc::end_free = nullptr;
size_t __default_alloc::heap_size = 0;
__default_alloc::obj *volatile __default_alloc::free_list[__NFREELISTS] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

// 当free_list无可用区块时，重新填充空间
// 新空间取自内存池，默认获取20个节点(区块）
// 若内存池不足，则获取的将小于20
void *__default_alloc::refill(size_t n) {
    int nobjs = 20;
    // 尝试调用chunk_alloc,注意nobjs以pass-by-reference传入
    char *chunk = chunk_alloc(n, nobjs);
    obj *volatile *my_free_list;
    obj *result;
    obj *current_obj, *next_obj;

    // 若只获取了一个区块则直接分配给调用者，不加入free_list
    if (1 == nobjs) return (chunk);
    my_free_list = free_list + FREELIST_INDEX(n);

    // 在chunk空间内建立free_list
    result = reinterpret_cast<obj *>(chunk);
    // 引导free_list指向内存池分配的空间
    // chunk指向的内存直接分给用户，free_list指向剩下（19或更少）的区块
    *my_free_list = next_obj = reinterpret_cast<obj *>(chunk + n);
    for (int i = 1;; ++i) {
        current_obj = next_obj;
        next_obj =
            reinterpret_cast<obj *>(reinterpret_cast<char *>(next_obj) + n);
        if (nobjs - 1 == i) {
            current_obj->free_list_link = nullptr;
            break;
        } else {
            current_obj->free_list_link = next_obj;
        }
    }
    return result;
}

// 默认size为8的整数倍
char *__default_alloc::chunk_alloc(size_t size, int &nobjs) {
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;  //内存池剩余空间
    if (bytes_left >= total_bytes) {
        // 容量满足需求
        result = start_free;
        start_free += total_bytes;
        return result;
    } else if (bytes_left > size) {
        // 容量至少满足一个区块需求
        nobjs = static_cast<int>(bytes_left / size);
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    } else {
        // 内存池一个区块都无法提供
        size_t bytes_to_get =
            2 * total_bytes +
            ROUND_UP(
                heap_size >>
                4);  // 向heap申请注入的内存，heap_size将随着配置次数增加而增加
        if (bytes_left > 0) {
            // 当前内存池还有一部分内存，为了不浪费分配给free_list
            obj *volatile *my_free_list =
                free_list + FREELIST_INDEX(bytes_left);
            reinterpret_cast<obj *>(start_free)->free_list_link = *my_free_list;
            *my_free_list = reinterpret_cast<obj *>(start_free);
        }
        // 配置heap空间以补充内存池
        start_free = reinterpret_cast<char *>(malloc(bytes_to_get));
        if (!start_free) {
            // heap空间不足，malloc失败
            obj *volatile *my_free_list;
            obj *p;
            // 在free_list中检查是否有符合需求的区块
            for (size_t i = size; i <= static_cast<size_t>(__MAX_BYTES);
                 i += static_cast<size_t>(__ALIGN)) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (p) {
                    // 存在足以分配的区块
                    *my_free_list = p->free_list_link;  // 抽离当前区块
                    start_free = reinterpret_cast<char *>(p);
                    end_free = start_free + i;
                    return (chunk_alloc(
                        size,
                        nobjs));  // 递归调用以修正nobjs，此时必然进入else_if分支
                }
            }
            end_free = nullptr;  // 到处都找不到内存
            // 调用第一级适配器观察其能否分配内存，或抛出异常
            start_free =
                reinterpret_cast<char *>(malloc_alloc::allocate(bytes_to_get));
        }
        heap_size += bytes_to_get;  // 已占用的堆内存
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);  // 调用自身以修正nobjs
    }
}

void *__default_alloc::allocate(size_t n) {
    obj *volatile *my_free_list;
    obj *result;
    // 若n大于128,则采用第一级适配器
    if (n > __MAX_BYTES) return (malloc_alloc::allocate(n));
    // 选择采用第几区块
    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;
    if (result == nullptr) {
        // 未找到可用free_list，准备填充free_list
        void *r = refill(ROUND_UP(n));
        return r;
    }
    // 调整freelist
    *my_free_list = result->free_list_link;
    return result;
}

void __default_alloc::deallocate(void *p, size_t n) {
    // p不可为nullptr
    if (n > static_cast<size_t>(__MAX_BYTES))
        malloc_alloc::deallocate(p, n);
    else {
        // 寻找对应的free list
        obj *volatile *my_free_list = free_list + FREELIST_INDEX(n);
        obj *q = reinterpret_cast<obj *>(p);
        // 调整free list，回收区块
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }
}

void *__default_alloc::reallocate(void *p, size_t old_sz, size_t new_sz) {
    void *result;
    size_t copy_sz;

    if (old_sz > static_cast<size_t>(__MAX_BYTES) &&
        new_sz > static_cast<size_t>(__MAX_BYTES))
        return realloc(p, new_sz);
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz)) return p;
    result = allocate(new_sz);
    copy_sz = new_sz > old_sz ? old_sz : new_sz;
    memcpy(result, p, copy_sz);
    deallocate(p, old_sz);
    return result;
}

}  // namespace MiniSTL

// Summary
/*
alloc.h 文件实际定义了两种分配器的内存管理方法
第一种是简单分配，实际上就是malloc的加皮封装
第二种使用了8～128不同空间的空闲链表，对系统的索要内存块放在空闲链表上，对该空闲链表进行管理
包含了内存池的操作 避免反复进行malloc申请系统的内存
包含内存碎片的收集，在没有足够内存情况下挪用小的碎片
 
 
*/
