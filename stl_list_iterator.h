//
//  stl_list_iterator.h
//  mini-stl
//
//  Created by cz-mac on 2021/12/21.
//
#pragma once

#include <cstddef>  // ptrdiff_t
#include "stl_iterator.h"
#include "stl_list_node.h"

namespace MiniSTL {

template <class T>
struct __list_iterator {
    // alias declarations
    typedef __list_iterator<T> self;
    typedef __list_node<T>* link_type; //链接指针
    typedef bidirectional_iterator_tag iterator_category; //迭代器类型 双向
    typedef T value_type; //值
    typedef T* pointer ; //指针
    typedef T&  reference; //引用
    typedef ptrdiff_t difference_type; //指针距离类型

    // data member
    link_type node;  // 指向list节点 从这个节点迭代

    // ctor
    __list_iterator() {}
    explicit __list_iterator(link_type x) : node(x) {}

    // dtor(trivial)

    // 判定迭代器是否指向同一个节点
    bool operator == (const self &rhs) const noexcept { return node == rhs.node; }
    bool operator != (const self &rhs) const noexcept { return node != rhs.node; }

    // dererence
    reference operator*() const { return node->data; }

    // member access 实际上可以把iterator看成指针 需要重载->操作
    pointer operator->() const { return &(operator*()); }

    // increasement
    self& operator ++ () {
        node = node->next;
        return *this;
    }
    // 用一个冗余参数来区分先加还是后加
    self operator ++(int i) {
        self temp = *this;
        ++(*this);
        return temp;
    }

    // decreasement
    self& operator -- () {
        node = node->prev;
        return *this;
    }

    self operator -- (int i) {
        self temp = *this;
        --(*this);
        return temp;
    }
};

template <class T>
struct __list_const_iterator {
    // alias declarations
    using iterator = __list_iterator<T>;
    using self = __list_const_iterator<T>;
    using link_type = __list_node<T> *;

    using iterator_category = bidirectional_iterator_tag;
    using value_type = T;
    using pointer = const T *; //指针是一个常量指针 表示不能修改此迭代器所指向的内容
    using reference = const T &;
    using difference_type = ptrdiff_t;

    // data member
    link_type node;  // raw pointer link to list_node

    // ctor
    __list_const_iterator() {}
    explicit __list_const_iterator(link_type x) : node(x) {}
    __list_const_iterator(const iterator &x) : node(x.node) {}

    // dtor(trivial)

    bool operator==(const self &rhs) const noexcept { return node == rhs.node; }
    bool operator!=(const self &rhs) const noexcept { return node != rhs.node; }

    // dererence
    reference operator*() const { return node->data; }

    // member access
    pointer operator->() const { return &(operator*()); }

    // increasement
    self &operator++() {
        node = node->next;
        return *this;
    }

    self operator++(int i) {
        self temp = *this;
        ++(*this);
        return temp;
    }

    // decreasement
    self &operator--() {
        node = node->prev;
        return *this;
    }

    self operator--(int i) {
        self temp = *this;
        --(*this);
        return temp;
    }
};

}  // namespace MiniSTL
