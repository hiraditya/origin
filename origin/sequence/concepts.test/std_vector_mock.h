#ifndef STD_VECTOR_MOCK_H
#define STD_VECTOR_MOCK_H

/***
 * This is a badly modified version of gcc's std::vector just to create a mock.
 * Please do not use this file for any purpose other than using a a mock-vector.
 */

// Copyright (C) 2001-2013 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this  software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#include <cstdlib>
#include <cstddef>

namespace mock {
  template <typename _Tp, typename _Alloc = std::allocator<_Tp>>
    class vector {
      public:
        typedef _Tp value_type;
        typedef _Tp* pointer;
        typedef const _Tp* const_pointer;
        typedef _Tp& reference;
        typedef const _Tp& const_reference;
        typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
        typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
                const_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef _Alloc allocator_type;
        struct _Vector_impl
        {
          pointer _M_start;
          pointer _M_finish;
          pointer _M_end_of_storage;

          _Vector_impl()
            : _M_start(0), _M_finish(0), _M_end_of_storage(0)
          { }

          void _M_swap_data(_Vector_impl& __x)
          {
            std::swap(_M_start, __x._M_start);
            std::swap(_M_finish, __x._M_finish);
            std::swap(_M_end_of_storage, __x._M_end_of_storage);
          }
        };
        _Vector_impl _M_impl;
      public:

        vector() {}

        explicit
        vector(size_type __n, const allocator_type &__a = allocator_type())
        {}
        vector(size_type __n, const value_type &__value,
            const allocator_type &__a = allocator_type()) {}

        vector(const vector &__x) {}

        vector &operator=(const vector &__x) {}

        void assign(size_type __n, const value_type &__val) {}

        // iterators

        iterator begin() { return iterator(this->_M_impl._M_start); }

        const_iterator begin() const {
          return const_iterator(this->_M_impl._M_start);
        }

        iterator end() { return iterator(this->_M_impl._M_finish); }

        const_iterator end() const
        { return const_iterator(this->_M_impl._M_finish); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const {
          return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
          return const_reverse_iterator(begin());
        }

        size_type size() const { return _M_impl._M_finish - _M_impl._M_start; }
        size_type max_size() const
        { return _M_impl._M_end_of_storage - _M_impl._M_start; }
        size_type capacity() const { return max_size(); }
        bool empty() const { return _M_impl._M_finish == _M_impl._M_start; }
        void reserve(size_type __n) { }

        // element access

        reference operator[](size_type __n) { return _M_impl._M_start + __n; }
        const_reference operator[](size_type __n) const
        { _M_impl._M_start + __n; }

      public:
        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { return *(end() - 1); }
        const_reference back() const { return *(end() - 1); }
        void push_back(const value_type &__x) {}
        void pop_back() {}
        iterator insert(iterator __position, const value_type &__x)
        { return __position + 1; }
        iterator erase(iterator __position) { return __position; }
        iterator erase(iterator __first, iterator __last) { return __first; }
        void swap(vector &__x) {}
        void clear() {}
    };
} // namespace mock

#endif
