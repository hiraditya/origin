// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.


#include <deque>
#include <list>
#include <map>
#include <vector>

#include <origin/sequence/concepts.hpp>

using namespace std;
using namespace origin;

int main()
{
  using list_seq = std::list<int>;
  static_assert(is_STL_container<list_seq>(), "");
  static_assert(is_STL_forward_container<list_seq>(), "");
  static_assert(is_STL_reversible_container<list_seq>(), "");
  static_assert(!is_STL_random_access_container<list_seq>(), "");

  using vec_seq = std::vector<int>;
  static_assert(is_STL_container<vec_seq>(), "");
  static_assert(is_STL_forward_container<vec_seq>(), "");
  static_assert(is_STL_reversible_container<vec_seq>(), "");
  static_assert(is_STL_random_access_container<vec_seq>(), "");

  using deque_seq = std::deque<int>;
  static_assert(is_STL_container<deque_seq>(), "");
  static_assert(is_STL_forward_container<deque_seq>(), "");
  static_assert(is_STL_reversible_container<deque_seq>(), "");
  static_assert(is_STL_random_access_container<deque_seq>(), "");

  using map_ass = std::map<int, int>;
  static_assert(is_STL_container<map_ass>(), "");
  static_assert(is_STL_forward_container<map_ass>(), "");
  static_assert(is_STL_reversible_container<map_ass>(), "");
  static_assert(!is_STL_random_access_container<map_ass>(), "");
  static_assert(is_STL_associative_container<map_ass>(), "");

  using mmap_ass = std::multimap<int, int>;
  static_assert(is_STL_container<mmap_ass>(), "");
  static_assert(is_STL_forward_container<mmap_ass>(), "");
  static_assert(is_STL_reversible_container<mmap_ass>(), "");
  static_assert(!is_STL_random_access_container<mmap_ass>(), "");
  static_assert(is_STL_associative_container<mmap_ass>(), "");
return 0;
}

