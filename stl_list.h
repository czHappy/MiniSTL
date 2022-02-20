//
//  stl_list.h
//  mini-stl
//
//  Created by cz-mac on 2021/12/21.
//
#pragma once
#include "allocator.h"
#include "stl_list_iterator.h"
#include "uninitialized.h"

namespace MiniSTL {

template <class T, class Alloc = simpleAlloc<T>>
class list {
public:  // alias declarations
    typedef T value_type;
    typedef T* pointer ;
    typedef const T* const_pointer ;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef __list_iterator<T> iterator;
    typedef __list_const_iterator<T> const_iterator ;
    typedef MiniSTL::__reverse_iterator<iterator> reverse_iterator;
    typedef MiniSTL::__reverse_iterator<const_iterator> const_reverse_iterator;

private:  // interface about allocate/deallocate litsNode
    typedef __list_node<T> list_node;
    typedef simpleAlloc<list_node> list_node_allocator;
    typedef list_node* link_type;
    // 获取一个节点 分配内存
    link_type get_node() { return list_node_allocator::allocate(); }
    // 销毁一个节点
    void put_node(list_node *p) { list_node_allocator::deallocate(p); }
    
    // 使用值创建一个节点
    list_node *create_node(const value_type &);
    // 销毁一个节点
    void destroy_node(list_node *p) {
        destroy(&p->data); //先析构数据域 由分配器调用析构函数
        put_node(p); //再把节点自己的内存还给分配器管理
    }

private:  // only data member(tail)
    link_type node; //只需要一个指针就能完整表示整个环状双向链表

private:  // aux_interface
    // 配置一个节点空间 头尾都指向自己 也就是链表的初始化
    void empety_initialized();
    
    // 核心函数 迁移 [first, last)的节点到position之后 然后两个链表都要链接起来 P139
    void transfer(iterator position, iterator first, iterator last);

public:  // ctor && dtor
    list() { empety_initialized(); } //默认初始化为空链表
    explicit list(size_type, const value_type& value = value_type());
    // don't need any dispatching tricks here, because insert does all of that
    // anyway
    template <class InputIterator>
    list(InputIterator first, InputIterator last) {
        empety_initialized();
        insert(begin(), first, last);
    }
    list(std::initializer_list<value_type> il) {
        empety_initialized();
        insert(begin(), il.begin(), il.end());
    }
    ~list() {
        clear();
        put_node(node);
    }

public:  // swap
    void swap(list &rhs) noexcept { MiniSTL::swap(node, rhs.node); }

public:  // copy operation
    list(const list &);//拷贝构造
    list& operator = (const list &) noexcept; //拷贝赋值

private:  // aux interface for assign
    // 从begin处开始 把n个节点的值设置为val
    // 如果n大于列表长度则再在后面新插入一些节点
    // 如果n小于列表长度则后面未赋值的结点全部擦除
    void fill_assign(size_type, const value_type &);
    
    //dispatch总有两种参数
    //n,val，在起始处赋值n个节点为val
    //[first, last) 在这段区间内赋值
    // 由于迭代器指针本身也是整数无法区分，所以额外加一个参数_true_type/_false_type
    template <class Integer>
    void assign_dispatch(Integer n, Integer val, _true_type) {
        fill_assign(static_cast<size_type>(n), static_cast<value_type>(val));
    }
    template <class InputIterator>
    void assign_dispatch(InputIterator, InputIterator, _false_type);

public:  // assignment
    void assign(size_type n, const value_type &val) { fill_assign(n, val); }
    void assign(std::initializer_list<value_type> ils) {
        assign_dispatch(ils.begin(), ils.end(), _false_type());
    }
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        assign_dispatch(first, last, _is_integer_t<InputIterator>());
    }
    list& operator = (std::initializer_list<T> ils) {
        assign(ils.begin(), ils.end());
        return *this;
    }

public:  // move operation
    list(list &&rhs) noexcept { //移动构造
        empety_initialized(); //初始化
        MiniSTL::swap(node, rhs.node); //交换右值引用的node域，相当于把它的整个链表都拿过来了
        // 右值引用的node域变成只有一个节点的链表 实际上相当于被掏空
    }
    list& operator = (list &&rhs) noexcept { //移动赋值
        clear();
        swap(rhs);
        return *this;
    }

public:  // getter
    bool empty() const noexcept { return node->next == node; }
    size_type size() const noexcept {
        return MiniSTL::distance(cbegin(), cend());
    }
    // begin被指定成当前节点的next end是自己 自己这个节点是不用的
    // 因为可以把链表想象成一个环 这样遍历的时候是可以全部遍历到的
    const_iterator begin() const noexcept { return const_iterator(node->next); }
    const_iterator end() const noexcept { return const_iterator(node); }
    const_iterator cbegin() const noexcept {
        return const_iterator(node->next);
    }
    const_iterator cend() const noexcept { return const_iterator(node); }
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }
    const_reference front() const noexcept { return *begin(); }
    const_reference back() const noexcept { return *(--end()); }

public:  // setter
    iterator begin() noexcept { return iterator(node->next); }
    iterator end() noexcept { return iterator(node); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    reference front() noexcept { return *begin(); }
    reference back() noexcept { return *(--end()); }

public:  // resize
    void resize(size_type, const value_type &val = value_type());

private:  // aux interface for insert
    void fill_insert(iterator, size_type, const value_type &);
    
    template <class Integer>
    void insert_dispatch(iterator pos, Integer n, Integer val, _true_type) {
        fill_insert(pos, static_cast<size_type>(n),
                    static_cast<value_type>(val));
    }
    template <class InputIterator>
    void insert_dispatch(iterator, InputIterator, InputIterator, _false_type);

public:  // insert
    // 在pos处插入一个默认值
    iterator insert(iterator pos) { return insert(pos, value_type()); }
    // 在pos处插入一个指定值
    iterator insert(iterator, const value_type &);
    // 在pos处插入 [first, last)之间的值
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last) {
        insert_dispatch(pos, first, last, _is_integer_t<InputIterator>());
    }

public:  // erase
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void clear();

public:  // push && pop
    void push_front(const T &value) { insert(begin(), value); } //头插
    void push_back(const T &value) { insert(end(), value); } //尾插
    void pop_fornt() { erase(begin()); } // 去头
    void pop_back() { //去尾
        iterator temp = end();
        erase(--temp);
    }

public:  // other interface
    void unique(); //移除连续而相同的元素，只保留一个
    void splice(iterator pos, list &rhs) {  //将rhs接到pos之前
        if (!rhs.empty()) transfer(pos, rhs.begin(), rhs.end());
    }
    void splice(iterator, list &, iterator);
    void splice(iterator pos, list &, iterator first, iterator last) {
        if (first != last) transfer(pos, first, last);
    }
    void merge(list &); //有序链表合并
    void reverse(); //逆转链表
    void sort(); // 排序
    void remove(const T &); //erase指定值的结点
};

// 按照值创建一个list_node并返回其指针
template <class T, class Alloc>
inline typename list<T, Alloc>::list_node* list<T, Alloc>::create_node(const T &value) {
    list_node *p = get_node();
    try {
        construct(&p->data, value); //调用的construct.h文件里的construct
    } catch (std::exception) {
        put_node(p);
        throw;
    }
    return p;
}
// 空链表只有一个节点 其next和prev都指向自己
template <class T, class Alloc>
inline void list<T, Alloc>::empety_initialized() {
    node = get_node();
    node->next = node;
    node->prev = node;
}
// 从begin处开始 把n个节点的值设置为val
// 如果n大于列表长度则再在后面新插入一些节点
// 如果n小于列表长度则后面未赋值的结点全部擦除
template <class T, class Alloc>
void list<T, Alloc>::fill_assign(size_type n, const value_type &val) {
    iterator i = begin();
    for (; i != end(); ++i, --n) *i = val;
    if (n > 0)
        fill_insert(end(), n, val);// 在结尾处再插入n个值为val的对象
    else
        erase(i, end());// 擦出
}

template <class T, class Alloc>
template <class InputIterator>
void list<T, Alloc>::assign_dispatch(InputIterator first, InputIterator last,
                                     _false_type) {
    iterator start = begin();
    iterator finish = end();
    for (; start != finish && first != last; ++start, ++first) *start = *first;
    if (first == last)
        erase(start, finish);
    else
        insert(finish, first, last);
}
//resize
template <class T, class Alloc>
inline void list<T, Alloc>::resize(size_type new_size, const value_type &val) {
    iterator cur = begin();
    size_type len = 0;
    for (; cur != end() && len < new_size; ++cur, ++len)
        ;
    if (len == new_size)
        erase(cur, end());
    else  // i == end()
        fill_insert(end(), new_size - len, val);
}
// 在position前一个位置插入一个结点 并且要与前后链接起来
// 返回的是指向新插入节点的迭代器
template <class T, class Alloc>
inline typename list<T, Alloc>::iterator list<T, Alloc>::insert(
    iterator position, const value_type &val) {
    link_type temp = create_node(val);
    temp->next = position.node;
    temp->prev = position.node->prev;
    position.node->prev->next = temp;
    position.node->prev = temp;
    return iterator(temp);
}

// 使用固定值在指定位置开始插入n个节点
template <class T, class Alloc>
void list<T, Alloc>::fill_insert(iterator position, size_type n,
                                 const value_type &val) {
    for (size_type i = n; i != 0; --i) position = insert(position, val);
}
//区间插 insert_dispatch是深拷贝
// 插入函数是插入position之前 返回的是position
template <class T, class Alloc>
template <class InputIterator>
void list<T, Alloc>::insert_dispatch(iterator position, InputIterator first,
                                     InputIterator last, _false_type) {
    for (; first != last; ++first) insert(position, *first);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::iterator list<T, Alloc>::erase(
    iterator position) {
    list_node *next_node = position.node->next;
    list_node *prev_node = position.node->prev;
    prev_node->next = next_node;
    next_node->prev = prev_node;
    destroy_node(position.node);
    return iterator(next_node);
}

template <class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator first,
                                                        iterator last) {
    iterator res;
    while (first != last) res = erase(first++);
    return res;
}

template <class T, class Alloc>
inline void list<T, Alloc>::transfer(iterator position, iterator first,
                                     iterator last) {
    if (position != last) {
        last.node->prev->next = position.node;
        first.node->prev->next = last.node;
        position.node->prev->next = first.node;
        list_node *temp = position.node->prev;
        position.node->prev = last.node->prev;
        last.node->prev = first.node->prev;
        first.node->prev = temp;
    }
}
// 构造链表 使用一个指定值构造N个节点
template <class T, class Alloc>
list<T, Alloc>::list(size_type n, const value_type &val) {
    empety_initialized();
    fill_insert(begin(), n, val);
}

template <class T, class Alloc>
list<T, Alloc>::list(const list &rhs) {
    empety_initialized();
    insert(begin(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
inline list<T, Alloc> &list<T, Alloc>::operator=(const list &rhs) noexcept {
    list temp(rhs);
    swap(temp);
    return *this;
}

template <class T, class Alloc>
void list<T, Alloc>::clear() {
    list_node *cur = node->next;
    while (cur != node) {
        list_node *temp = cur;
        cur = cur->next;
        destroy_node(temp);
    }
    node->next = node;
    node->prev = node;
}

template <class T, class Alloc>
void list<T, Alloc>::remove(const T &value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) erase(first);
        first = next;
    }
}

template <class T, class Alloc>
void list<T, Alloc>::unique() {
    iterator first = begin();
    iterator last = end();
    if (first == last) return;
    iterator next = first;
    while (++next != last) {
        if (*first == *next) {
            erase(next);
            next = first;
        } else
            first = next;
    }
}

template <class T, class Alloc>
inline void list<T, Alloc>::splice(iterator position, list &, iterator i) {
    iterator j = i;
    ++j;
    // i==pos 自身无法插于自身之前
    // j==pos 已处于pos之前
    if (position == i || position == j) return;
    transfer(position, i, j);
}

// need two lists' elements are ordered
template <class T, class Alloc>
void list<T, Alloc>::merge(list &x) {
    iterator first1 = begin();
    iterator last1 = end();
    iterator first2 = x.begin();
    iterator last2 = x.end();

    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) {
            iterator next = first2;
            transfer(first1, first2, ++next);
            first2 = next;
        } else
            ++first1;
    }
    if (first2 != last2) transfer(last1, first2, last2);
}

template <class T, class Alloc>
void list<T, Alloc>::reverse() {
    // empty || size()==1
    if (node->next == node || node->next->next == node) return;
    iterator first = begin();
    ++first;  // begin自身并不需要移动，它将作为指示末元素的哨兵（确切地说，最终begin.node->next
              // == end.node)
    while (first != end()) {
        iterator old = first;
        ++first;
        transfer(begin(), old, first);
    }
}

// More information can be seen at
// https://blog.csdn.net/qq276592716/article/details/7932483
template <class T, class Alloc>
void list<T, Alloc>::sort() {
    if (node->next == node || node->next->next == node) return;
    // 数据缓存区
    // counter[n]中最多存放2^(n+1)个元素，若大于则与counter[n+1]作归并
    list carry;
    list counter[64];
    int fill = 0;
    while (!empty()) {
        carry.splice(carry.begin(), *this, begin());
        int i = 0;
        while (i < fill && !counter[i].empty()) {
            counter[i].merge(carry);
            carry.swap(counter[i++]);
        }
        carry.swap(counter[i]);
        if (i == fill) ++fill;
    }
    for (int i = 1; i < fill; ++i) counter[i].merge(counter[i - 1]);
    swap(counter[fill - 1]);
}

template <class T>
inline void swap(list<T> &lhs, list<T> &rhs) {
    lhs.swap(rhs);
}

template <class T>
bool operator==(const list<T> &lhs, const list<T> &rhs) {
    auto it1 = lhs.begin(), it2 = rhs.begin();  // same as cbegin()
    for (; it1 != lhs.end() && it2 != rhs.end(); ++it1, ++it2)
        if (*it1 != *it2) return false;
    return it1 == lhs.end() && it2 == rhs.end();
}

template <class T>
inline bool operator!=(const list<T> &lhs, const list<T> &rhs) {
    return !(lhs == rhs);
}

template <class T>
inline bool operator<(const list<T> &lhs, const list<T> &rhs) {
    return MiniSTL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                            rhs.end());  // in stl_algobase.h
}

template <class T>
inline bool operator>(const list<T> &lhs, const list<T> &rhs) {
    return rhs < lhs;
}

template <class T>
inline bool operator<=(const list<T> &lhs, const list<T> &rhs) {
    return !(rhs < lhs);
}

template <class T>
inline bool operator>=(const list<T> &lhs, const list<T> &rhs) {
    return !(lhs < rhs);
}

}  // namespace MiniSTL
