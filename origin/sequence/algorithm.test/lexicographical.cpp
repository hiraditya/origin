// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <iostream>
#include <vector>

#include <origin/sequence/algorithm.hpp>
#include <origin/type/typestr.hpp>

using namespace std;
using namespace origin;

template <typename T> using Pair_of = pair<T, T>;

int
main ()
{
  using V = vector<int>;
  V v1{ 0, 1, 2, 3, 4 };
  V v2{ 0, 1, 2, 3, 4 };
  std::less<int> lt;

  assert (lexicographical_compare (v1, v2)
          == lexicographical_compare (v1.begin (), v1.end (), v2.begin (),
                                      v2.end ()));

  assert (lexicographical_compare (v1, v2, lt)
          == lexicographical_compare (v1.begin (), v1.end (), v2.begin (),
                                      v2.end (), lt));
}
