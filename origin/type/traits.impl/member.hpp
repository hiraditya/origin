// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_TYPE_TRAITS_HPP
#error This file cannot be included directly. Include type/traits.hpp.
#endif

namespace type_impl
{
//////////////////////////////////////////////////////////////////////////////
// Associated Member Types
//
// The following traits provide support for deducing (or not!) the explicitly
// associated type names (e.g., T::foo_type).
//////////////////////////////////////////////////////////////////////////////

// Deduce the type expression T::size_type.
template <typename T> struct get_associated_value_type
{
private:
  template <typename X> static typename X::value_type check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Deduce the type expression T::size_type.
template <typename T> struct get_associated_difference_type
{
private:
  template <typename X> static typename X::difference_type check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the type expression T::size_type.
template <typename T> struct get_associated_size_type
{
private:
  template <typename X> static typename X::size_type check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the type expression T::size_type.
template <typename T> struct get_associated_key_type
{
private:
  template <typename X> static typename X::key_type check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the type expression T::hasher.
template <typename T> struct get_associated_hasher
{
private:
  template <typename X> static typename X::hasher check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

template <typename T> struct get_associated_key_equal
{
private:
  template <typename X> static typename X::key_equal check (const X &);
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the associated type name T::reference.
template <typename T> struct get_associated_reference
{
private:
  template <typename X> static typename X::reference check (const X &);

  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the associatd type name T::const_reference.
template <typename T> struct get_associated_const_reference
{
private:
  template <typename X> static typename X::const_reference check (const X &);

  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the associated type name T::pointer.
template <typename T> struct get_associated_pointer
{
private:
  template <typename X> static typename X::pointer check (const X &);

  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the associatd type name T::const_pointer.
template <typename T> struct get_associated_const_pointer
{
private:
  template <typename X> static typename X::const_pointer check (const X &);

  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

//////////////////////////////////////////////////////////////////////////////
// Common member functions
//
//
//////////////////////////////////////////////////////////////////////////////

// Safely deduce get the result type of the expression t.size().
template <typename T> struct get_member_size_result
{
private:
  template <typename X> static auto check (const X &x) -> decltype (x.size ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce get the result type of the expression t.bucket_count().
template <typename T> struct get_member_bucket_count_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.bucket_count ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce get the result type of the expression t.hash_funct().
template <typename T> struct get_member_hash_funct_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.hash_funct ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce get the result type of the expression t.hash_function().
template <typename T> struct get_member_hash_function_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.hash_function ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce get the result type of the expression t.max_size().
template <typename T> struct get_member_max_size_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.max_size ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the result type of the expression t.empty().
template <typename T> struct get_member_empty_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.empty ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the result type of the expression t.empty().
template <typename T> struct get_member_front_result
{
private:
  template <typename X>
  static auto check (const X &x) -> decltype (x.front ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce the result type of the expression t.clear().
template <typename T> struct get_member_clear_result
{
private:
  // For modifiers, take the argument by rvalue-ref as passing by
  // ref wasn't working.
  template <typename X> static auto check (X &&x) -> decltype (x.clear ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deducethe result type of the expression t.find(u).
//
// NOTE: This was added here so that we can dispatch the find algorithm
// to classes implementing associative data structures.
template <typename T, typename U> struct get_member_find_result
{
private:
  template <typename X, typename Y>
  static auto check (X &&x, Y &&y) -> decltype (x.find (y));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> ()));
};

template <typename T, typename U> struct get_member_erase_result
{
private:
  template <typename X, typename Y>
  static auto check (X &&x, Y &&y) -> decltype (x.erase (y));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> ()));
};

// Safely deduce the result of the expression insert(r, t).
template <typename T, typename U, typename V> struct get_member_insert_result
{
private:
  template <typename X, typename Y, typename Z>
  static auto check (X &&x, Y &&y, Z &&z) -> decltype (x.insert (y, z));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> (),
                                std::declval<V> ()));
};

// Safely deduce the result type of the expression t.key_eq().
template <typename T> struct get_member_key_eq_result
{
private:
  template <typename X> static auto check (X &&x) -> decltype (x.key_eq ());
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> ()));
};

// Safely deduce get the result type of the expression t.resize(n).
template <typename T, typename U> struct get_member_resize_result
{
private:
  template <typename X, typename Y>
  static auto check (X &&x, Y &&y) -> decltype (x.resize (y));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> ()));
};

template <typename T, typename U> struct get_member_count_result
{
private:
  template <typename X, typename Y>
  static auto check (X &&x, Y &&y) -> decltype (x.count (y));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> ()));
};

template <typename T, typename U> struct get_member_equal_range_result
{
private:
  template <typename X, typename Y>
  static auto check (X &&x, Y &&y) -> decltype (x.equal_range (y));
  static subst_failure check (...);

public:
  using type = decltype (check (std::declval<T> (), std::declval<U> ()));
};

} // namespace type_impl
