// Copyright (c)
//
// This file is distributed under the MIT License. See
// LICENCE.txt attached with this project or visit
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.
//

#include <origin/sequence/functional_programming.hpp>

#include <deque>
#include <vector>
#include <list>
#include <cassert>

template <template <class, class> class container_type, class value_type>
int
test_functional ()
{
  using T = container_type<value_type, std::allocator<value_type> >;
  T vi{ 1, 2, 3, 4 };

  using ToT = container_type<T, std::allocator<T> >;
  ToT vov (5, vi);
  ToT vov_copy{ { 1, 2, 3, 4 },
                { 1, 2, 3, 4 },
                { 1, 2, 3, 4 },
                { 1, 2, 3, 4 },
                { 1, 2, 3, 4 } };

  assert (vov == vov_copy);
  {
    using namespace origin::non_intrusive;
    int first = *std::begin (car (vi));
    assert (first == 1);

    T remaining_list = cdr (vi);
    T remaining_list_copy{ 2, 3, 4 };
    assert (remaining_list == remaining_list_copy);

    T comb = cons (first, remaining_list);
    assert (comb == vi);

    T fof_caar = caar (vov);
    assert (*std::begin (fof_caar) == 1);
    assert (origin::size (fof_caar) == 1);

    ToT cdr_vov_copy{
      { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 }
    };
    auto cdr_vov = cdr (vov);
    assert (cdr_vov == cdr_vov_copy);
    assert (*std::begin (cadr (vov)) == vi);
    assert (*std::begin (cdr (cdr (cdr (vi)))) == 4);

    ToT cdr_vec (std::begin (cdr_vov), std::end (cdr_vov));
    assert (cdr_vec == cdr_vov);
    assert (*std::begin (car (cadr (vov))) == vi);
    // list operations return a bounded range of the same type.
    // To take the element out of the bounded range we need to do std::begin()
    assert (*std::begin (car (*begin (cadr (vov)))) == 1);
    assert (*std::begin (car (cadr (vov))) == vi);

    assert (*succ (vi.begin ()) == 2);
    assert (*pred (vi.end ()) == 4);
  }

  {
    using namespace origin::intrusive;

    auto first = car (vi);
    assert (*std::begin (first) == 1);

    auto remaining_list = cdr (vi);
    T remaining_list_copy{ 2, 3, 4 };
    assert (T (std::begin (remaining_list), std::end (remaining_list))
            == remaining_list_copy);

    auto comb = cons (first, remaining_list);
    assert (T (std::begin (comb), std::end (comb)) == vi);

    auto fof_caar = caar (vov);
    assert (*std::begin (fof_caar) == 1);

    ToT cdr_vov_copy{
      { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 }
    };
    auto cdr_vov = cdr (vov);
    assert (ToT (std::begin (cdr_vov), std::end (cdr_vov)) == cdr_vov_copy);
    assert (*std::begin (cadr (vov)) == vi);
    assert (*std::begin (cdr (cdr (cdr (vi)))) == 4);
    assert (*std::begin (car (cadr (vov))) == vi);
    // list operations return a bounded range of the same type.
    // To take the element out of the bounded range we need to do std::begin()
    assert (*std::begin (car (*begin (cadr (vov)))) == 1);
    assert (*std::begin (car (cadr (vov))) == vi);

    auto cons_vec_range = cons (car (vov), cdr (vov));
    ToT cons_vec (std::begin (cons_vec_range), std::end (cons_vec_range));
    assert (cons_vec == vov);
    assert (begin (cons_vec_range) == begin (vov));
    assert (end (cons_vec_range) == end (vov));
  }
  return 0;
}

int
test_hof ()
{
  return 0;
}

int
main ()
{
  test_functional<std::vector, int> ();
  test_functional<std::list, int> ();
  test_functional<std::deque, int> ();
  test_functional<std::deque, char> ();
  // TODO: Test for C arrays.
  test_hof ();
  return 0;
}
