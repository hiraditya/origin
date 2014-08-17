// Copyright (c)
//
// This file is distributed under the MIT License. See
// LICENCE.txt attached with this project or visit
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.
//

#include <origin/sequence/functional_programming.hpp>

#include<deque>
#include<vector>
#include<list>
#include<cassert>

using namespace origin;
template<template <class, class> class container_type, class value_type>
int test_functional()
{
  using T = container_type<value_type, std::allocator<value_type>>;
  T vi{1,2,3,4};


  int first = *std::begin(car(vi));
  assert(first == 1);

  auto remaining_list = cdr(vi);
  T remaining_list_copy{2, 3, 4};
  assert(remaining_list == remaining_list_copy);

  auto comb = cons(first, remaining_list);
  assert(comb == vi);

  using ToT = container_type<T, std::allocator<T>>;
  ToT vov(5,vi);
  ToT vov_copy{{1, 2, 3, 4},
                 {1, 2, 3, 4},
                 {1, 2, 3, 4},
                 {1, 2, 3, 4},
                 {1, 2, 3, 4}};

  assert(vov == vov_copy);

  auto fof_caar = begin(caar(vov));
  assert(*fof_caar == 1);

  auto cdr_vov = cdr(vov);

  // TODO: Not working for 'cons' only works for cons_no_copy because cons
  // returns a sequence.
  auto cons_vec_range = cons_no_copy(car_no_copy(vov), cdr_no_copy(vov));
  ToT cons_vec(std::begin(cons_vec_range), std::end(cons_vec_range));
  assert(cons_vec == vov);
  assert(begin(cons_vec_range) == begin(vov));
  assert(end(cons_vec_range) == end(vov));

  ToT cdr_vov_copy{{1, 2, 3, 4},
                 {1, 2, 3, 4},
                 {1, 2, 3, 4},
                 {1, 2, 3, 4}};
  assert(cdr_vov == cdr_vov_copy);
  assert(*std::begin(cadr(vov)) == vi);
  assert(*std::begin(cdr_no_copy(cdr_no_copy(cdr_no_copy(vi)))) == 4);

  ToT cdr_vec(std::begin(cdr_no_copy(vov)), std::end(cdr_no_copy(vov)));
  assert(cdr_vec == cdr_vov);
  assert(*std::begin(car(cadr_no_copy(vov))) == vi);
  // list operations return a bounded range of the same type.
  // To take the element out of the bounded range we need to do std::begin()
  assert(*std::begin(car(*begin(cadr_no_copy(vov)))) == 1);
  assert(*std::begin(car(cadr(vov))) == vi);

  assert(*succ(vi.begin()) == 2);
  assert(*pred(vi.end()) == 4);
  return 0;
}

int test_hof() {
  return 0;
}

int main() {
  test_functional<std::vector, int>();
  test_functional<std::list, int>();
  test_functional<std::deque, int>();
  test_functional<std::deque, char>();
  // TODO: Test for C arrays.
  test_hof();
  return 0;
}
