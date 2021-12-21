#pragma once

namespace MiniSTL {



struct _true_type {};
struct _false_type {};

// 默认自定义类型均为non-POD类型
template <class T>
struct _type_traits {
    using has_trivial_default_constructor = _false_type;
    using has_trivial_copy_constructor = _false_type;
    using has_trivial_assignment_operator = _false_type;
    using has_trivial_destructor = _false_type;
    using is_POD_type = _false_type;
};

template <>
struct _type_traits<bool> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<char> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned char> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<signed char> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<wchar_t> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<short> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned short> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<int> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned int> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<long> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned long> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<long long> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned long long> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<float> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<double> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<long double> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <class T>
struct _type_traits<T *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <class T>
struct _type_traits<const T *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<unsigned char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<signed char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<const char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<const unsigned char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

template <>
struct _type_traits<const signed char *> {
    using has_trivial_default_constructor = _true_type;
    using has_trivial_copy_constructor = _true_type;
    using has_trivial_assignment_operator = _true_type;
    using has_trivial_destructor = _true_type;
    using is_POD_type = _true_type;
};

// is_integer(默认自定义类型为false)

template <class T>
struct _is_integer {
    using _integral = _false_type;
};

// simluate C++14
template <class T>
using _is_integer_t = typename _is_integer<T>::_integral;

// vector构造函数（n,value） (_InputIterator __first, _InputIterator __last) 有两种语义
// 需要区分开来方便调用 如果判定参数类型为整型调用第一种 否则调用第二种
//语义一：指定元素数量和初始值，构造vector
//语义二：指定起始iterator和终止iterator, 构造vector

//以下均视为integer 整型
//bool
//char
//signed char
//unsigned char
//wchar_t
//short
//unsigned short
//int
//unsigned int
//long
//unsigned long
//long long
//unsigned long long


template <>
struct _is_integer<bool> {
    using _integral = _true_type;
};

template <>
struct _is_integer<char> {
    using _integral = _true_type;
};

template <>
struct _is_integer<signed char> {
    using _integral = _true_type;
};

template <>
struct _is_integer<unsigned char> {
    using _integral = _true_type;
};

template <>
struct _is_integer<wchar_t> {
    using _integral = _true_type;
};

template <>
struct _is_integer<short> {
    using _integral = _true_type;
};

template <>
struct _is_integer<unsigned short> {
    using _integral = _true_type;
};

template <>
struct _is_integer<int> {
    using _integral = _true_type;
};

template <>
struct _is_integer<unsigned int> {
    using _integral = _true_type;
};

template <>
struct _is_integer<long> {
    using _integral = _true_type;
};

template <>
struct _is_integer<unsigned long> {
    using _integral = _true_type;
};

template <>
struct _is_integer<long long> {
    using _integral = _true_type;
};

template <>
struct _is_integer<unsigned long long> {
    using _integral = _true_type;
};

}  // namespace MiniSTL


// Summary
/*
1. typeTraits.h 文件就是定义了一些原生类型的4种平凡信息和POD类型信息
  has_trivial_default_constructor ;
  has_trivial_copy_constructor ;
  has_trivial_assignment_operator ;
  has_trivial_destructor ;
  is_POD_type ;
 用_true_type或者_false_type区分
 
 2. 默认自定义类型都是_false_type，原生类型都是_true_type
*/
