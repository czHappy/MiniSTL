#pragma once
#include <cstring>  // memove
#include "construct.h"
#include "stl_algobase.h"
#include "stl_iterator.h"
#include "typeTraits.h"

namespace MiniSTL {

template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first,
                                          InputIterator last,
                                          ForwardIterator result) {
    using isPODType =
        typename _type_traits<value_type_t<InputIterator>>::is_POD_type;
    return __uninitialized_copy_aux(first, last, result, isPODType());
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first,
                                                InputIterator last,
                                                ForwardIterator result,
                                                _true_type) {
    return MiniSTL::copy(first, last, result);  // in stl_algobase.h
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first,
                                                InputIterator last,
                                                ForwardIterator result,
                                                _false_type) {
    ForwardIterator cur = result;
    for (; first != last; ++cur, ++first) construct(&*cur, *first);
    return cur;
}

//针对char*、wchar_t*存在特化版本 memmove直接移动内存
inline char *uninitialized_copy(const char *first, const char *last,
                                char *result) {
    memmove(result, first, last - first);
    return result + (last - first);
}

inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last,
                                   wchar_t *result) {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}

template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                               const T &value) {
    using isPODType =
        typename _type_traits<value_type_t<ForwardIterator>>::is_POD_type;
    __uninitialized_fill_aux(first, last, value, isPODType());
}

template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first,
                                     ForwardIterator last, const T &value,
                                     _true_type) {
    MiniSTL::fill(first, last, value);
}

template <class ForwardIterator, class T>
void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                              const T &value, _false_type) {
    ForwardIterator cur = first;
    for (; cur != last; ++cur) construct(&*cur, value);
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                            const T &value) {
    using isPODType =
        typename _type_traits<value_type_t<ForwardIterator>>::is_POD_type;
    return __uninitialized_fill_n_aux(first, n, value, isPODType());
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                                  const T &value, _true_type) {
    return MiniSTL::fill_n(first, n, value);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                           const T &value, _false_type) {
    // 忽略异常处理
    // 需要明确的是一旦一个对象构造失败则需要析构所有对象
    ForwardIterator cur = first;
    for (; n > 0; --n, ++cur) construct(&*cur, value);
    return cur;
}


}  // namespace MiniSTL


// Summary
/*
uninitialized.h 文件实际定义了一些批量内存操作的方法
1. 需要迭代器指明范围 和定位
2. 需要借助construct.h中的一些构造方法和destroy方法
3. 需要借助stl_algobase中的一些copy和fill方法
4. 利用萃取机获得类型，对POD类型的构建使用系统底层的构造方法，速度极快，偏特化处理

*/

