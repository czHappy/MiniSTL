#pragma once

#include <cstddef>  // ptrdiff_t
#include "allocator.h"
#include "uninitialized.h"
#include <iostream>
namespace MiniSTL {
// use sub_allocator as default allocator
template <class T, class Alloc = simpleAlloc<T> >
class vector {
public:  // alias declarartions
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;  // iterator is raw pointer
    typedef const value_type * const_iterator;
    typedef __reverse_iterator<iterator> reverse_iterator;
    typedef __reverse_iterator<const_iterator> const_reverse_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

private:  // data member
    // iterator to indicate the vector's memory location
    iterator start;//首地址
    iterator finish;//使用的尾地址
    iterator end_of_storage;//实际分配的内存尾地址

private:  // allocate and construct aux functions
    typedef Alloc data_allocator;
    // 把n个元素都填充为value
    void fill_initialize(size_type n, const value_type &value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
    //整型初始化  _true_type初始化
    template <class Integer>
    void initialize_aux(Integer n, Integer val, _true_type) {
        fill_initialize(static_cast<size_type>(n),
                        static_cast<value_type>(val));
    }
    //非整型初始化 其实就是用迭代器初始化
    template <class InputIterator>
    void initialize_aux(InputIterator first, InputIterator last, _false_type) {
        start = allocate_and_copy(first, last);
        finish = end_of_storage = start + MiniSTL::distance(first, last);
    }
    
    //fill_initialize实际就是调用allocate_and_fill 然后记录start和finish
    iterator allocate_and_fill(size_type n, const value_type &value) {
        iterator result = data_allocator::allocate(n);
        MiniSTL::uninitialized_fill_n(result, n, value);//uninitialized.h 全局函数
        return result;
    }
    //先分配一块空间，首地址为result然后把[first, last)内容拷贝到分配的空间里去
    template <class InputIterator>
    iterator allocate_and_copy(InputIterator first, InputIterator last) {
        size_type n = MiniSTL::distance(first, last);
        iterator result = data_allocator::allocate(n);
        MiniSTL::uninitialized_copy(first, last, result);
        return result;
    }
    void deallocate() noexcept {
        if (start) //如果有元素
            data_allocator::deallocate(start, end_of_storage - start);
    }
    //先析构对象 然后回收内存
    void destroy_and_deallocate() noexcept {
        destroy(start, finish);  // destroy in "construct.h"
        deallocate();
    }

public:  // swap
    void swap(vector &) noexcept;

    
public:  // ctor && dtor
    vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
    explicit vector(size_type n) { fill_initialize(n, value_type()); }
    //元素个数+填充值初始化
    vector(size_type n, const value_type &value) { fill_initialize(n, value); }
    //判定不是整型才调用迭代器初始化
    template <class InputIterator>
    vector(InputIterator first, InputIterator last) {
        initialize_aux(first, last, _is_integer_t<InputIterator>());
    }
    //初始化列表的形式初始化
    vector(std::initializer_list<T>);
    //拷贝赋值
    vector(const vector &);
    vector(vector &&) noexcept;

    ~vector() {
        destroy(start, finish);  // destory in "construct.h"
        deallocate();
    }

public:  // copy assignment operator
    vector& operator = (const vector &);

public:  // move assignment
    vector &operator=(vector &&) noexcept;

public:  // getter 都声明为const不能修改只能查询
    const_iterator begin() const noexcept { return start; }
    const_iterator end() const noexcept { return finish; }
    const_iterator cbegin() const noexcept { return start; }
    const_iterator cend() const noexcept { return finish; }
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(finish);
    }
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(start);
    }
    // 没有做空判断
    const_reference front() const noexcept {
//        if(empty()){
//            return NULL;
//        }
        return *begin();
    }
    const_reference back() const noexcept { return *(end() - 1); }
    
    // 没有做越界检查
    const_reference operator[](const size_type n) const noexcept {
        return *(start + n);
    }
    size_type size() const noexcept {
        return static_cast<size_type>(finish - start);
    }
    size_type capacity() const noexcept {
        return static_cast<size_type>(end_of_storage - start);
    }
    bool empty() const noexcept { return start == finish; }

public:  // setter
    iterator begin() noexcept { return start; }
    iterator end() noexcept { return finish; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(finish); }
    reverse_iterator rend() noexcept { return reverse_iterator(start); }
    reference operator[](const size_type n) noexcept { return *(start + n); }
    reference front() noexcept { return *begin(); }
    reference back() noexcept { return *(end() - 1); }

public:  // interface for size and capacity
    void resize(size_type, const value_type &);
    void resize(size_type new_size) { resize(new_size, value_type()); }
    void reserve(size_type);
    
    void shrink_to_fit() noexcept {
        vector temp(*this);
        swap(temp);
    }

public:  // compare operator(member function)
    bool operator == (const vector &) const noexcept;
    bool operator != (const vector &rhs) const noexcept {
        return !(*this == rhs);
    }

public:  // push && pop
    void push_back(const value_type &);
    void pop_back() {
        --finish;
        destroy(finish);
    }

public:  // erase
    iterator erase(iterator, iterator);
    iterator erase(iterator position) { return erase(position, position + 1); }
    void clear() { erase(begin(), end()); }

private:  // aux_interface for insert
    void insert_aux(iterator, const value_type &);
    void fill_insert(iterator, size_type, const value_type &);
    template <class InputIterator>
    void range_insert(iterator pos, InputIterator first, InputIterator last,
                      input_iterator_tag);
    template <class ForwardIterator>
    void range_insert(iterator pos, ForwardIterator first, ForwardIterator last,
                      forward_iterator_tag);
    template <class Integer>
    void insert_dispatch(iterator pos, Integer n, Integer value, _true_type) {
        fill_insert(pos, static_cast<int>(n), value_type(value));
    }
    template <class InputIterator>
    void insert_dispatch(iterator pos, InputIterator first, InputIterator last,
                         _false_type) {
        range_insert(pos, first, last, iterator_category_t<InputIterator>());
    }

public:  // insert
    iterator insert(iterator);
    iterator insert(iterator, const value_type &);
    template <class InputIterator>
    void insert(iterator pos, InputIterator first, InputIterator last) {
        insert_dispatch(pos, first, last, _is_integer_t<InputIterator>());
    }

private:  // aux_interface for assign
    void fill_assign(size_type, const value_type &);
    template <class Integer>
    void assign_dispatch(Integer n, Integer val, _true_type) {
        fill_assign(static_cast<size_type>(n), static_cast<value_type>(val));
    }
    template <class InputIterator>
    void assign_dispatch(InputIterator first, InputIterator last, _false_type) {
        assign_aux(first, last, iterator_category_t<InputIterator>());
    }
    template <class InputIterator>
    void assign_aux(InputIterator first, InputIterator last,
                    input_iterator_tag);
    template <class ForwardIterator>
    void assign_aux(ForwardIterator first, ForwardIterator last,
                    forward_iterator_tag);

public:  // assign
    void assign(size_type n, const value_type &val) { fill_assign(n, val); }
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        assign_dispatch(first, last, _is_integer_t<InputIterator>());
    }
    void assign(std::initializer_list<value_type> ils) {
        assign(ils.begin(), ils.end());
    }
    vector& operator = (std::initializer_list<value_type> ils) {
        assign(ils);
        return *this;
    }
};

// 具体实现

// 在指定位置插入一个值
// 应该先保证这个位置在[start, finish]之间 这里先不检查
template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const value_type &value) {
    if (finish != end_of_storage) {  // needn't expand
        construct(finish, *(finish - 1));
        ++finish;
        value_type value_copy = value;  // STL copy in copy out
        MiniSTL::copy_backward(position, finish - 2, finish - 1);
        *position = value_copy;
    } else {  // expand
        const size_type old_size = size();
        const size_type new_size =
            old_size ? 2 * old_size : 1;  // 如果原来是0则新的size为1，否则new_cap = 2 * old_cap
        iterator new_start = data_allocator::allocate(new_size);
        iterator new_finish = new_start;
        try {
            new_finish = MiniSTL::uninitialized_copy(start, position, new_start);  // Copy the first segment
            construct(new_finish, value);//插入值
            ++new_finish;
            new_finish = MiniSTL::uninitialized_copy(
                position, finish, new_finish);  // Copy the second segment
        } catch (std::exception &) {
            // commit or rollback
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, new_size);
            throw;
        }
        destroy_and_deallocate(); //原本的vector回收
        start = new_start; //通过设置三个重要指针，新的空间被指定
        finish = new_finish;
        end_of_storage = new_start + new_size;
    }
}

// 对InputIterator的range_insert 调用的是insert(pos, *first);
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::range_insert(iterator pos, InputIterator first,
                                    InputIterator last, input_iterator_tag) {
    for (; first != last; ++first) {
        pos = insert(pos, *first);
        ++pos;
    }
}
// 对ForwardIterator的range_insert
template <class T, class Alloc>
template <class ForwardIterator>
void vector<T, Alloc>::range_insert(iterator position, ForwardIterator first,
                                    ForwardIterator last,
                                    forward_iterator_tag) {
    if (first != last) {
        size_type n = MiniSTL::distance(first, last);
        if (static_cast<size_type>(end_of_storage - finish) >= n) {
            const size_type elems_after = finish - position;
            iterator old_finish = finish;
            if (elems_after > n) {
                MiniSTL::uninitialized_copy(finish - n, finish, finish);
                finish += n;
                MiniSTL::copy_backward(position, old_finish - n, old_finish);
                MiniSTL::copy(position, position + n, position);
            } else {
                ForwardIterator mid = first;
                advance(mid, elems_after);
                MiniSTL::uninitialized_copy(mid, last, finish);
                finish += n - elems_after;
                MiniSTL::uninitialized_copy(position, old_finish, finish);
                finish += elems_after;
                MiniSTL::copy(first, mid, position);
            }
        } else {  // expand
            const size_type old_size = size();
            const size_type new_size = old_size + MiniSTL::max(old_size, n);
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish =
                    MiniSTL::uninitialized_copy(start, position, new_start);
                new_finish =
                    MiniSTL::uninitialized_copy(first, last, new_finish);
                new_finish =
                    MiniSTL::uninitialized_copy(position, finish, new_finish);
            } catch (std::exception &) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            destroy_and_deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + new_size;
        }
    }
}

// 书上的insert
template <class T, class Alloc>
void vector<T, Alloc>::fill_insert(iterator position, size_type n,
                                   const value_type &value) {
    if (n) {
        if (static_cast<size_type>(end_of_storage - finish) >=
            n) {  // needn't expand
            value_type value_copy = value;
            const size_type elems_after = finish - position;
            iterator old_finish = finish;
            if (elems_after > n) {
                MiniSTL::uninitialized_copy(finish - n, finish, finish);
                finish += n;
                MiniSTL::copy_backward(position, old_finish - n, old_finish);
                MiniSTL::fill(position, position + n, value_copy);
            } else {
                MiniSTL::uninitialized_fill_n(finish, n - elems_after,
                                              value_copy);
                finish += n - elems_after;
                MiniSTL::uninitialized_copy(position, old_finish, finish);
                finish += elems_after;
                MiniSTL::fill(position, old_finish, value_copy);  // complement
            }
        } else {  // expand
            const size_type old_size = size();
            const size_type new_size = old_size + MiniSTL::max(old_size, n);
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish =
                    MiniSTL::uninitialized_copy(start, position, new_start);
                new_finish =
                    MiniSTL::uninitialized_fill_n(new_finish, n, value);
                new_finish =
                    MiniSTL::uninitialized_copy(position, finish, new_finish);
            } catch (std::exception &) {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            destroy_and_deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + new_size;
        }
    }
}
// 指定位置插个默认值
template <class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator position) {
    return insert(position, value_type());//insert默认值
}
// 指定位置插入指定值
template <class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator position, const value_type &value) {
    size_type n = position - begin();
    if (finish != end_of_storage && position == end()) {
        construct(finish, value);
        ++finish;
    } else
        insert_aux(position, value);
    return begin() + n;
}

// push_back函数 就是在最后面新插入一个
template <class T, class Alloc>
inline void vector<T, Alloc>::push_back(const value_type &value) {
    if (finish != end_of_storage) {
        construct(finish, value);
        ++finish;
    } else
        insert_aux(end(), value);
}


//swap函数实际上就是换了迭代器 指针
template <class T, class Alloc>
inline void vector<T, Alloc>::swap(vector &rhs) noexcept {
    MiniSTL::swap(start, rhs.start);
    MiniSTL::swap(finish, rhs.finish);
    MiniSTL::swap(end_of_storage, rhs.end_of_storage);
}
template <class T, class Alloc>
inline void swap(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
    lhs.swap(rhs);
}



//

// 重新调整大小
template <class T, class Alloc>
inline void vector<T, Alloc>::resize(size_type new_size,
                                     const value_type &value) {
    if (new_size < size())
        erase(begin() + new_size, end());
    else
        fill_insert(end(), new_size - size(), value);
}

// 重新分配空间 如果新空间不会更大就不处理 否则就新开辟一块大空间并把原来的内容copy进去
template <class T, class Alloc>
inline void vector<T, Alloc>::reserve(size_type new_capacity) {
    if (new_capacity <= capacity()) return;
    T *new_start = data_allocator::allocate(new_capacity);
    T *new_finish = MiniSTL::uninitialized_copy(start, finish, new_start);
    destroy_and_deallocate();
    start = new_start;
    finish = new_finish;
    end_of_storage = start + new_capacity;
}



// erase掉一个区间 相当于把后面的一段元素copy到前面来实现覆盖
template <class T, class Alloc>
inline typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    iterator first, iterator last) {
    iterator i = MiniSTL::copy(last, finish, first);
    destroy(i, finish);
    finish -= (last - first);
    return first;
}


// assign操作
template <class T, class Alloc>
void vector<T, Alloc>::fill_assign(size_type n, const value_type &val) {
    if (n > capacity()) {
        vector<T, Alloc> temp(n, val);
        temp.swap(*this);
    } else if (n > size()) {
        MiniSTL::fill(begin(), end(), val);
        finish = MiniSTL::uninitialized_fill_n(finish, n - size(), val);
    } else
        erase(MiniSTL::fill_n(begin(), n, val), end());
}

template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::assign_aux(InputIterator first, InputIterator last,
                                  input_iterator_tag) {
    iterator cur = begin();
    for (; first != last && cur != end(); ++cur, ++first) *cur = *first;
    if (first == last)
        erase(cur, end());
    else
        insert(end(), first, last);
}

template <class T, class Alloc>
template <class ForwardIterator>
void vector<T, Alloc>::assign_aux(ForwardIterator first, ForwardIterator last,
                                  forward_iterator_tag) {
    size_type len = MiniSTL::distance(first, last);
    if (len > capacity()) {
        iterator temp = allocate_and_copy(first, last);
        destroy_and_deallocate();
        start = temp;
        end_of_storage = finish = start + len;
    } else if (size() >= len) {
        iterator new_finish = MiniSTL::copy(first, last, start);
        destroy(new_finish, finish);
        finish = new_finish;
    } else {
        ForwardIterator mid = first;
        MiniSTL::advance(mid, size());
        MiniSTL::copy(first, mid, start);
        finish = MiniSTL::uninitialized_copy(mid, last, finish);
    }
}

// 构造函数
//迭代器构造 复制
template <class T, class Alloc>
inline vector<T, Alloc>::vector(const vector &rhs) {
    start = allocate_and_copy(rhs.begin(), rhs.end());
    finish = end_of_storage = start + rhs.size();
}
// 列表构造
template <class T, class Alloc>
inline vector<T, Alloc>::vector(std::initializer_list<T> il) {
    start = allocate_and_copy(il.begin(), il.end());
    finish = end_of_storage = start + il.size();
}
template <class T, class Alloc>
inline vector<T, Alloc>::vector(vector &&rhs) noexcept {
    start = rhs.start;
    finish = rhs.finish;
    end_of_storage = rhs.end_of_storage;
    rhs.start = rhs.finish = rhs.end_of_storage = nullptr;
}

//操作符重载
template <class T, class Alloc>
inline vector<T, Alloc>& vector<T, Alloc>::operator = (const vector &rhs) {
    vector temp(rhs);
    swap(temp);
    return *this;
}

template <class T, class Alloc>
inline vector<T, Alloc>& vector<T, Alloc>::operator = (vector &&rhs) noexcept {
    if (this != &rhs) {
        destroy_and_deallocate();
        start = rhs.start;
        finish = rhs.finish;
        end_of_storage = rhs.end_of_storage;
        rhs.start = rhs.finish = rhs.end_of_storage = nullptr;
    }
    return *this;
}

template <class T, class Alloc>
bool vector<T, Alloc>::operator==(const vector &rhs) const noexcept {
    if (size() != rhs.size()) {
        return false;
    } else {
        iterator ptr1 = start;
        iterator ptr2 = rhs.start;
        for (; ptr1 != finish && ptr2 != rhs.finish; ++ptr1, ++ptr2)
            if (*ptr1 != *ptr2) return false;
        return true;
    }
}

template <class T, class Alloc>
inline bool operator == (const vector<T, Alloc> &lhs,
                       const vector<T, Alloc> &rhs) {
    return lhs.operator == (rhs);
}

template <class T, class Alloc>
inline bool operator!=(const vector<T, Alloc> &lhs,
                       const vector<T, Alloc> &rhs) {
    return !(lhs == rhs);
}

// 小于号重载 实际上是字典序列比较
template <class T>
inline bool operator < (const vector<T> &lhs, const vector<T> &rhs) {
    return MiniSTL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                            rhs.end());  // in stl_algobase.h
}

template <class T>
inline bool operator > (const vector<T> &lhs, const vector<T> &rhs) {
    return rhs < lhs;
}

template <class T>
inline bool operator <= (const vector<T> &lhs, const vector<T> &rhs) {
    return !(rhs < lhs);
}

template <class T>
inline bool operator >= (const vector<T> &lhs, const vector<T> &rhs) {
    return !(lhs < rhs);
}



}  // namespace MiniSTL
