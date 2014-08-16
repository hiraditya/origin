#ifndef STD_LIST_MOCK_H
#define STD_LIST_MOCK_H
// List implementation -*- C++ -*-

/***
 * This is a badly modified version of gcc's std::list just to create a mock.
 * Please do not use this file for any purpose other than using a a mock-list.
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
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#include <cstdlib>
#include <cstddef>
namespace mock
{
/// Common part of a node in the %list.
struct _List_node_base
{
  _List_node_base* _M_next;
  _List_node_base* _M_prev;

  static void swap(_List_node_base& __x, _List_node_base& __y);

  void _M_transfer(_List_node_base* const __first,
              _List_node_base* const __last);

  void _M_reverse() ;

  void _M_hook(_List_node_base* const __position);

};

/// An actual node in the %list.
template<typename _Tp>
struct _List_node : public _List_node_base
{
  ///< User's data.
  _Tp _M_data;
};


template<typename _Tp>
struct _List_iterator
{
  typedef _List_iterator<_Tp>                _Self;
  typedef _List_node<_Tp>                    _Node;

  typedef std::ptrdiff_t                     difference_type;
  typedef std::bidirectional_iterator_tag    iterator_category;
  typedef _Tp                                value_type;
  typedef _Tp*                               pointer;
  typedef _Tp&                               reference;

  _List_iterator()
    : _M_node() { }

  explicit _List_iterator(_List_node_base* __x)
    : _M_node(__x) { }

  // Must downcast from _List_node_base to _List_node to get to _M_data.
  reference operator*() const
  { return static_cast<_Node*>(_M_node)->_M_data; }

  pointer operator->() const
  { return std::__addressof(static_cast<_Node*>(_M_node)->_M_data); }

  _Self& operator++()
  {
    _M_node = _M_node->_M_next;
    return *this;
  }

  _Self operator++(int)
  {
    _Self __tmp = *this;
    _M_node = _M_node->_M_next;
    return __tmp;
  }

  _Self& operator--()
  {
    _M_node = _M_node->_M_prev;
    return *this;
  }

  _Self operator--(int)
  {
    _Self __tmp = *this;
    _M_node = _M_node->_M_prev;
    return __tmp;
  }

  bool operator==(const _Self& __x) const
  { return _M_node == __x._M_node; }

  bool operator!=(const _Self& __x) const
  { return _M_node != __x._M_node; }

  // The only member points to the %list element.
  _List_node_base* _M_node;
};


template<typename _Tp>
struct _List_const_iterator
{
  typedef _List_const_iterator<_Tp>          _Self;
  typedef const _List_node<_Tp>              _Node;
  typedef _List_iterator<_Tp>                iterator;

  typedef ptrdiff_t                          difference_type;
  typedef std::bidirectional_iterator_tag    iterator_category;
  typedef _Tp                                value_type;
  typedef const _Tp*                         pointer;
  typedef const _Tp&                         reference;

  _List_const_iterator()
    : _M_node() { }

  explicit _List_const_iterator(const _List_node_base* __x)
    : _M_node(__x) { }

  _List_const_iterator(const iterator& __x)
    : _M_node(__x._M_node) { }

  // Must downcast from List_node_base to _List_node to get to
  // _M_data.
  reference operator*() const
  { return static_cast<_Node*>(_M_node)->_M_data; }

  pointer operator->() const
  { return std::__addressof(static_cast<_Node*>(_M_node)->_M_data); }

  _Self& operator++()
  {
    _M_node = _M_node->_M_next;
    return *this;
  }

  _Self operator++(int)
  {
    _Self __tmp = *this;
    _M_node = _M_node->_M_next;
    return __tmp;
  }

  _Self& operator--()
  {
    _M_node = _M_node->_M_prev;
    return *this;
  }

  _Self operator--(int)
  {
    _Self __tmp = *this;
    _M_node = _M_node->_M_prev;
    return __tmp;
  }

  bool operator==(const _Self& __x) const
  { return _M_node == __x._M_node; }

  bool operator!=(const _Self& __x) const
  { return _M_node != __x._M_node; }

  // The only member points to the %list element.
  const _List_node_base* _M_node;
};

template<typename _Val>
inline bool
operator==(const _List_iterator<_Val>& __x,
           const _List_const_iterator<_Val>& __y)
{ return __x._M_node == __y._M_node; }

template<typename _Val>
inline bool
operator!=(const _List_iterator<_Val>& __x,
           const _List_const_iterator<_Val>& __y)
{ return __x._M_node != __y._M_node; }


/// See bits/stl_deque.h's _Deque_base for an explanation.
template<typename _Tp, typename _Alloc>
class _List_base
{
protected:

  typedef typename _Alloc::template rebind<_List_node<_Tp> >::other
  _Node_alloc_type;

  typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;

  struct _List_impl
      : public _Node_alloc_type
  {
    _List_node_base _M_node;

    _List_impl()
      : _Node_alloc_type(), _M_node()
    { }

    _List_impl(const _Node_alloc_type& __a)
      : _Node_alloc_type(__a), _M_node()
    { }
  };

  _List_impl _M_impl;

  _List_node<_Tp>* _M_get_node()
  { return _M_impl._Node_alloc_type::allocate(1); }

  void _M_put_node(_List_node<_Tp>* __p)
  { _M_impl._Node_alloc_type::deallocate(__p, 1); }

public:
  typedef _Alloc allocator_type;

  _Node_alloc_type& _M_get_Node_allocator()
  { return *static_cast<_Node_alloc_type*>(&_M_impl); }

  const _Node_alloc_type&
  _M_get_Node_allocator() const
  { return *static_cast<const _Node_alloc_type*>(&_M_impl); }

  _Tp_alloc_type _M_get_Tp_allocator() const
  { return _Tp_alloc_type(_M_get_Node_allocator()); }

  allocator_type get_allocator() const
  { return allocator_type(_M_get_Node_allocator()); }

  _List_base()
    : _M_impl()
  { _M_init(); }

  _List_base(const _Node_alloc_type& __a)
    : _M_impl(__a)
  { _M_init(); }

  // This is what actually destroys the list.
  ~_List_base()
  { _M_clear(); }

  void _M_clear()
  { }

  void _M_init()
  {
    this->_M_impl._M_node._M_next = &this->_M_impl._M_node;
    this->_M_impl._M_node._M_prev = &this->_M_impl._M_node;
  }
};

template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
class list : protected _List_base<_Tp, _Alloc>
{

public:
  typedef _Tp                                        value_type;
  typedef _Tp*          pointer;
  typedef const _Tp*    const_pointer;
  typedef _Tp&          reference;
  typedef const _Tp&    const_reference;
  typedef _List_iterator<_Tp>                        iterator;
  typedef _List_const_iterator<_Tp>                  const_iterator;
  typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;
  typedef std::reverse_iterator<iterator>            reverse_iterator;
  typedef size_t                                     size_type;
  typedef std::ptrdiff_t                             difference_type;
  typedef _Alloc                                     allocator_type;

protected:
  // Note that pointers-to-_Node's can be ctor-converted to
  // iterator types.
  typedef _List_node<_Tp>				 _Node;

  template<typename... _Args>
  _Node*
  _M_create_node(_Args&&... __args)
  {
    _Node* __p = this->_M_get_node();
    return __p;
  }

public:

  list()
  { }

  explicit list(const allocator_type& __a)
  { }

  explicit list(size_type __n, const value_type& __value = value_type(),
       const allocator_type& __a = allocator_type())
  { }

  list& operator=(const list& __x);

  void assign(size_type __n, const value_type& __val)
  { }

  iterator begin()
  { return iterator(this->_M_impl._M_node._M_next); }

  const_iterator begin() const
  { return const_iterator(this->_M_impl._M_node._M_next); }

  iterator end()
  { return iterator(&this->_M_impl._M_node); }

  const_iterator end() const
  { return const_iterator(&this->_M_impl._M_node); }

  reverse_iterator rbegin()
  { return reverse_iterator(end()); }

  const_reverse_iterator rbegin() const
  { return const_reverse_iterator(end()); }

  reverse_iterator rend()
  { return reverse_iterator(begin()); }

  const_reverse_iterator rend() const
  { return const_reverse_iterator(begin()); }

  bool empty() const
  { return this->_M_impl._M_node._M_next == &this->_M_impl._M_node; }

  size_type size() const
  { return std::distance(begin(), end()); }

  size_type max_size() const
  { return this->_M_get_Node_allocator().max_size(); }

  void resize(size_type __new_size)
  { }

  reference front()
  { return *begin(); }


  const_reference front() const
  { return *begin(); }

  reference back()
  {
    iterator __tmp = end();
    --__tmp;
    return *__tmp;
  }

  const_reference back() const
  {
    const_iterator __tmp = end();
    --__tmp;
    return *__tmp;
  }

  void push_front(const value_type& __x)
  { this->_M_insert(begin(), __x); }

  void pop_front()
  { this->_M_erase(begin()); }

  void push_back(const value_type& __x)
  { this->_M_insert(end(), __x); }

  void pop_back()
  { this->_M_erase(iterator(this->_M_impl._M_node._M_prev)); }

  iterator insert(iterator __position, const value_type& __x);
  void insert(iterator __position, size_type __n, const value_type& __x)
  {
    list __tmp(__n, __x, this->get_allocator());
    splice(__position, __tmp);
  }

  template<typename _InputIterator>
  void insert(iterator __position, _InputIterator __first,
         _InputIterator __last)
  {
    list __tmp(__first, __last, this->get_allocator());
    splice(__position, __tmp);
  }


  iterator erase(iterator __position);

  iterator erase(iterator __first, iterator __last)
  {
    while (__first != __last)
      __first = erase(__first);
    return __last;
  }

  void swap(list& __x)
  {
    _List_node_base::swap(this->_M_impl._M_node,
                          __x._M_impl._M_node);
  }

  void clear()
  {
    this->_M_clear();
    this->_M_init();
  }

  void remove(const _Tp& __value)
  { }

  template<typename _Predicate>
  void remove_if(_Predicate)
  { }

  void reverse()
  { this->_M_impl._M_node._M_reverse(); }

};


template<typename _Tp, typename _Alloc>
inline bool
operator==(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{
  typedef typename list<_Tp, _Alloc>::const_iterator const_iterator;
  const_iterator __end1 = __x.end();
  const_iterator __end2 = __y.end();

  const_iterator __i1 = __x.begin();
  const_iterator __i2 = __y.begin();
  while (__i1 != __end1 && __i2 != __end2 && *__i1 == *__i2)
  {
    ++__i1;
    ++__i2;
  }
  return __i1 == __end1 && __i2 == __end2;
}

template<typename _Tp, typename _Alloc>
inline bool
operator<(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{ return std::lexicographical_compare(__x.begin(), __x.end(),
                                      __y.begin(), __y.end()); }

/// Based on operator==
template<typename _Tp, typename _Alloc>
inline bool
operator!=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{ return !(__x == __y); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{ return __y < __x; }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator<=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{ return !(__y < __x); }

/// Based on operator<
template<typename _Tp, typename _Alloc>
inline bool
operator>=(const list<_Tp, _Alloc>& __x, const list<_Tp, _Alloc>& __y)
{ return !(__x < __y); }

/// See std::list::swap().
template<typename _Tp, typename _Alloc>
inline void
swap(list<_Tp, _Alloc>& __x, list<_Tp, _Alloc>& __y)
{ __x.swap(__y); }

} // namespace mock

#endif // STD_LIST_MOCK_H
