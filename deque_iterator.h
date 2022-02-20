//
//  deque_iterator.h
//  mini-stl
//
//  Created by cz-mac on 2022/1/1.
//

#ifndef deque_iterator_h
#define deque_iterator_h

#include <cstddef>
#include "stl_iterator.h"

namespace MiniSTL {

// 缓冲区大小设定函数（在预设情况下传回可容纳的元素个数）
// 若n不为0，则传回n，表示由用户自定
// 若n为0则采用预设值 预设值根据sz（元素大小）而定
inline size_t __deque_buf_size(size_t sz) {
    return sz < 512 ? size_t(512 / sz) : size_t(1);
}

template <class T, class Ref, class Ptr>
struct __deque_iterator {
    // alias declarartions
    typedef __deque_iterator<T, T &, T *> iterator;
    typedef __deque_iterator<T, const T &, const T *> const_iterator;
    typedef __deque_iterator self;

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    // data member
    value_type *cur;    // 当前缓冲区的当前元素
    value_type *first;  // 当前缓冲区头
    value_type *last;   // 当前缓冲区尾(含备用空间）
    map_pointer node;   // 指向管控中心

    static size_t buffer_size() { return __deque_buf_size(sizeof(value_type)); }

    // ctor
    __deque_iterator()
        : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) {}
    __deque_iterator(pointer x, map_pointer y)
        : cur(x), first(*y), last(*y + buffer_size()), node(y) {}
    __deque_iterator(const iterator &rhs)
        : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) {}

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + static_cast<difference_type>(buffer_size());
    }

    // dereference
    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }
    
    // 对于自增自减少操作，实际上增的是cur域，只有跨段时才会真正改变自己的node域
    self &operator++() {
        ++cur;
        if (cur == last) {  // 若已抵达尾端
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }

    self operator++(int) {
        self temp = *this;
        ++*this;
        return temp;
    }

    self &operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    self operator--(int) {
        self temp = *this;
        --*this;
        return temp;
    }

    // random access
    self &operator += (difference_type n) {
        difference_type offset = n + (cur - first);
        if (offset >= 0 &&
            offset < static_cast<difference_type>(buffer_size())) {
            // 不需要跳转
            cur += n;
        } else {
            // off_set小于0则必然需要跳转
            difference_type node_offset =
                offset > 0
                    ? offset / static_cast<difference_type>(buffer_size())
                    : -static_cast<difference_type>((-offset - 1) /
                                                    buffer_size()) -
                          1;
            set_node(node + node_offset);
            cur = first +
                  (offset -
                   node_offset * static_cast<difference_type>(buffer_size()));
        }
        return *this;
    }

    self operator+(difference_type n) {
        self temp = *this;
        return temp += n;
    }

    self &operator-=(difference_type n) { return *this += -n; }

    self operator-(difference_type n) {
        self temp = *this;
        return temp -= n;
    }

    reference operator[](difference_type n) { return *(*this + n); }
};
// 判断两个迭代器是否相等
template <class T, class Ref, class Ptr>
inline bool operator==(const __deque_iterator<T, Ref, Ptr> &lhs,
                       const __deque_iterator<T, Ref, Ptr> &rhs) {
    return lhs.cur == rhs.cur;
}

// compare with const
template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator==(const __deque_iterator<T, RefL, PtrL> &lhs,
                       const __deque_iterator<T, RefR, PtrR> &rhs) {
    return lhs.cur == rhs.cur;
}
// 判断两个迭代器是否不相等
template <class T, class Ref, class Ptr>
inline bool operator!=(const __deque_iterator<T, Ref, Ptr> &lhs,
                       const __deque_iterator<T, Ref, Ptr> &rhs) {
    return !(lhs == rhs);
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator!=(const __deque_iterator<T, RefL, PtrL> &lhs,
                       const __deque_iterator<T, RefR, PtrR> &rhs) {
    return !(lhs == rhs);
}
// 判断两个迭代器 前后关系
template <class T, class Ref, class Ptr>
inline bool operator<(const __deque_iterator<T, Ref, Ptr> &lhs,
                      const __deque_iterator<T, Ref, Ptr> &rhs) {
    return (lhs.node == rhs.node) ? (lhs.cur < rhs.cur) : (lhs.node < rhs.node);
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator<(const __deque_iterator<T, RefL, PtrL> &lhs,
                      const __deque_iterator<T, RefR, PtrR> &rhs) {
    return (lhs.node == rhs.node) ? (lhs.cur < rhs.cur) : (lhs.node < rhs.node);
}

template <class T, class Ref, class Ptr>
inline bool operator>(const __deque_iterator<T, Ref, Ptr> &lhs,
                      const __deque_iterator<T, Ref, Ptr> &rhs) {
    return rhs < lhs;
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator>(const __deque_iterator<T, RefL, PtrL> &lhs,
                      const __deque_iterator<T, RefR, PtrR> &rhs) {
    return rhs < lhs;
}

template <class T, class Ref, class Ptr>
inline bool operator<=(const __deque_iterator<T, Ref, Ptr> &lhs,
                       const __deque_iterator<T, Ref, Ptr> &rhs) {
    return !(rhs < lhs);
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator<=(const __deque_iterator<T, RefL, PtrL> &lhs,
                       const __deque_iterator<T, RefR, PtrR> &rhs) {
    return !(rhs < lhs);
}

template <class T, class Ref, class Ptr>
inline bool operator>=(const __deque_iterator<T, Ref, Ptr> &lhs,
                       const __deque_iterator<T, Ref, Ptr> &rhs) {
    return !(lhs < rhs);
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline bool operator>=(const __deque_iterator<T, RefL, PtrL> &lhs,
                       const __deque_iterator<T, RefR, PtrR> &rhs) {
    return !(lhs < rhs);
}
// 迭代器距离 段间距离和段内距离
template <class T, class Ref, class Ptr>
inline typename __deque_iterator<T, Ref, Ptr>::difference_type operator-(
    const __deque_iterator<T, Ref, Ptr> &lhs,
    const __deque_iterator<T, Ref, Ptr> &rhs) {
    return typename __deque_iterator<T, Ref, Ptr>::difference_type(
        __deque_iterator<T, Ref, Ptr>::buffer_size() *
            (lhs.node - rhs.node - 1) +
        (lhs.cur - lhs.first) + (rhs.last - rhs.cur));
}

template <class T, class RefL, class PtrL, class RefR, class PtrR>
inline typename __deque_iterator<T, RefL, PtrL>::difference_type operator-(
    const __deque_iterator<T, RefL, PtrL> &lhs,
    const __deque_iterator<T, RefR, PtrR> &rhs) {
    return typename __deque_iterator<T, RefL, PtrL>::difference_type(
        __deque_iterator<T, RefL, PtrL>::buffer_size() *
            (lhs.node - rhs.node - 1) +
        (lhs.cur - lhs.first) + (rhs.last - rhs.cur));
}
// 迭代器向前走n步
template <class T, class Ref, class Ptr>
inline __deque_iterator<T, Ref, Ptr> operator+(
    ptrdiff_t n, const __deque_iterator<T, Ref, Ptr> &x) {
    return x + n;
}

}  // namespace MiniSTL
#endif /* deque_iterator_h */
