#ifndef FUNCTIONAL_PROGRAMMING_HPP
#define FUNCTIONAL_PROGRAMMING_HPP

// Copyright (c)
//
// This file is distributed under the MIT License. See
// LICENCE.txt attached with this project or visit
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.
//

#include "concepts.hpp"
#include "range.hpp"
#include <iterator>
#include <algorithm>
namespace origin
{

namespace non_intrusive
{
// 1. All the following functions except caar, return the same type of
// sequence as the input sequence. This is to maintain uniformity. To access
// an element appropriate accessors can be used e.g., begin, end, next, prev.
// 2. Passing all the sequence by value in a 'hope' that move semantics
// will do a better job in each case.

/// \brief car stands for "Contents of the Address part of Register number"
/// essentially it returns a sequence having only the first element.
template <typename sequence>
inline sequence
car (sequence s)
{
  static_assert (is_STL_forward_container<sequence> (), "");
  return sequence (begin (s), ++begin (s));
}

/// \brief caar stands for car(car s)
/// \returns A reference to the first element of the
///          first element of the sequence_of_sequences.
template <typename sequence_of_sequences>
inline Value_type<sequence_of_sequences>
caar (sequence_of_sequences sos)
{
  static_assert (is_STL_forward_container<sequence_of_sequences> (), "");
  static_assert (
      is_STL_forward_container<Value_type<sequence_of_sequences> > (), "");
  return car (*std::begin (car (sos)));
}

/// \brief cdr stands for
///        "Contents of the Decrement part of Register number"
/// \returns The elements of the sequence except for the first one.
template <typename sequence>
inline sequence
cdr (sequence s)
{
  static_assert (is_STL_forward_container<sequence> (), "");
  sequence s_copy (size (s) - 1);
  std::copy (++begin (s), end (s), begin (s_copy));
  return s_copy;
}

/// \brief cadr stands for car(cdr s)
/// \returns the second element of the sequence.
template <typename sequence>
inline sequence
cadr (sequence s)
{
  return car (cdr (s));
}

/// \brief provide the cons function for a sequence
///        the sequence must have a begin and an end and the value type.
/// \note returning by value, relying on the move semantics of C++11
/// It takes sequence \p s by r-value reference so that user can pass
/// in a temporary sequence as well.
template <typename value_type, typename sequence>
sequence
cons (value_type v, sequence s)
{
  static_assert (is_STL_forward_container<sequence> (), "");
  static_assert (Convertible<value_type, Value_type<sequence> > (), "");
  sequence s_cons (size (s) + 1);
  *(begin (s_cons)) = v;
  std::copy (begin (s), end (s), ++begin (s_cons));
  return s_cons;
}

/// \brief accessors
///
template <typename forward_iterator>
inline forward_iterator
succ (forward_iterator x,
      typename std::iterator_traits<forward_iterator>::difference_type n = 1)
{
  static_assert (has_forward_iterator_property<forward_iterator> (), "");
  return std::next (x, n);
}

template <typename bidirectional_iterator>
inline bidirectional_iterator
pred (bidirectional_iterator x,
      typename std::iterator_traits<bidirectional_iterator>::difference_type n
      = 1)
{
  static_assert (
      has_bidirectional_iterator_property<bidirectional_iterator> (), "");
  return std::prev (x, n);
}
} // namespace non_intrusive

//////////////////////////////////////////////////////////////////////////////
///
/// Functions in the 'intrusive namespace will operate on the sequence
/// provided as input, and won't copy unless absolutely necessary.
///
namespace intrusive
{
// In all the functional style utilities, we return either the iterator,
// or the reference/const-ref.
/// \brief car stands for "Contents of the Address part of Register number"
/// essentially it returns first element of the list
/// returns reference to the first element of the sequence
template <typename sequence>
inline bounded_range<Iterator_of<sequence> >
car (sequence &&s)
{
  static_assert (Range<sequence> (), "");
  return bounded_range<Iterator_of<sequence> > (begin (s), ++begin (s));
}

/// \brief caar stands for car(car s)
/// \returns A reference to the first element of the
///          first element of the sequence_of_sequences.
template <typename sequence_of_sequences>
inline bounded_range<Iterator_of<typename sequence_of_sequences::value_type> >
caar (sequence_of_sequences &sos)
{
  static_assert (Range<sequence_of_sequences> (), "");
  static_assert (Range<typename sequence_of_sequences::value_type> (), "");
  return car (*car (sos).begin ());
}

template <typename sequence_of_sequences>
inline bounded_range<Iterator_of<typename sequence_of_sequences::value_type> >
caar (sequence_of_sequences &&sos)
{
  static_assert (Range<sequence_of_sequences> (), "");
  static_assert (Range<typename sequence_of_sequences::value_type> (), "");
  return car (*car (sos).begin ());
}

// returns the reference to the second element of the sequence
/// \brief cdr stands for
///        "Contents of the Decrement part of Register number"
/// \returns The elements of the list except for the first one.
template <typename sequence>
inline bounded_range<Iterator_of<sequence> >
cdr (sequence &&s)
{
  static_assert (Range<sequence> (), "");
  return bounded_range<Iterator_of<sequence> > (++begin (s), end (s));
}

/// \brief cadr stands for car(cdr s)
/// \returns the second element of the sequence.
template <typename sequence>
inline bounded_range<Iterator_of<sequence> >
cadr (sequence &&s)
{
  return car (cdr (s));
}

// cons_no_copy(f1, l1, f2, l2) -> (f1, l2) iff l1 == f2
template <typename sequence>
inline bounded_range<Iterator_of<sequence> >
cons (sequence &&s1, sequence &&s2)
{
  static_assert (Range<sequence> (), "");
  assert (end (s1) == begin (s2));
  return bounded_range<Iterator_of<sequence> > (begin (s1), end (s2));
}
} // namespace intrusive

//////////////////////////////////////////////////////////////////////////////
// Higher-order functions (HOFs) are functions that take other functions
// as their arguments. A basic example of a HOF is map which takes a function
// and a list as its arguments, applies  the function to all elements of the
// list, and returns the list of its results.
// For instance, we can write a function that subtracts 2 from all elements of
// a list without using loops or recursion:
// subtractTwoFromList l = map (\x -> x - 2) l
//////////////////////////////////////////////////////////////////////////////

/// \brief applies function (T function(T)) to each element
/// of the sequence<T>
/// \returns resulting sequence<T>
/// This is the side effect free version
template <typename function, typename sequence> struct FMap
{
  sequence
  operator() (const function &f, const sequence &s) const
  {
    static_assert (is_STL_forward_container<sequence> (), "");
    sequence seq;
    std::for_each (begin (s), end (s),
                   [f, &seq](typename sequence::value_type const &v)
                   {
                     seq.push_back (f (v));
                   });
    return seq;
  }
};

template <typename function, typename sequence>
inline auto map (const function &f, const sequence &s)
    -> decltype (FMap<function, sequence> () (f, s))
{
  return FMap<function, sequence> () (f, s);
}

/// \brief apply function 'f' to sequence 's', and then
/// again apply the function on the result.
/// \returns resulting sequence.
template <typename function, typename sequence>
inline auto fof (const function &f, const sequence &s)
    -> decltype (FMap<function, sequence> () (f, s))
{
  return FMap<function, sequence> () (f, FMap<function, sequence> () (f, s));
}

} // namespace origin

#endif // FUNCTIONAL_PROGRAMMING_HPP
