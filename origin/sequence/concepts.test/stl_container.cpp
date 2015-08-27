// Copyright (c)
//
// This file is distributed under the MIT License. See
// LICENCE.txt attached with this project or visit
// http://www.opensource.org/licenses/mit-license.php
// for terms and conditions.
//

#include <deque>
#include <list>
#include <map>
#include <vector>
#include <unordered_map>

#include <origin/sequence/concepts.hpp>
#include "std_vector_mock.h"
#include "std_list_mock.h"

using namespace origin;

void check_list() {
  using list_seq = std::list<int>;
  static_assert(is_STL_container<list_seq>(), "");
  static_assert(is_STL_sequence<list_seq>(), "");
  static_assert(is_STL_forward_container<list_seq>(), "");
  static_assert(is_STL_reversible_container<list_seq>(), "");
  static_assert(!is_STL_random_access_container<list_seq>(), "");
  static_assert(!is_STL_associative_container<list_seq>(), "");
  static_assert(!is_STL_hashed_associative_container<list_seq>(), "");
}

void check_vector() {
  using vec_seq = std::vector<int>;
  static_assert(is_STL_container<vec_seq>(), "");
  static_assert(is_STL_sequence<vec_seq>(), "");
  static_assert(is_STL_forward_container<vec_seq>(), "");
  static_assert(is_STL_reversible_container<vec_seq>(), "");
  static_assert(is_STL_random_access_container<vec_seq>(), "");
  static_assert(!is_STL_associative_container<vec_seq>(), "");
  static_assert(!is_STL_hashed_associative_container<vec_seq>(), "");
}

void check_deque() {
  using deque_seq = std::deque<int>;
  static_assert(is_STL_container<deque_seq>(), "");
  static_assert(is_STL_sequence<deque_seq>(), "");
  static_assert(is_STL_forward_container<deque_seq>(), "");
  static_assert(is_STL_reversible_container<deque_seq>(), "");
  static_assert(is_STL_random_access_container<deque_seq>(), "");
  static_assert(!is_STL_associative_container<deque_seq>(), "");
  static_assert(!is_STL_hashed_associative_container<deque_seq>(), "");
}

void check_map() {
  using map_ass = std::map<int, int>;
  static_assert(is_STL_container<map_ass>(), "");
  // TODO: Is map not a sequence?
  static_assert(!is_STL_sequence<map_ass>(), "");
  static_assert(is_STL_forward_container<map_ass>(), "");
  static_assert(is_STL_reversible_container<map_ass>(), "");
  static_assert(!is_STL_random_access_container<map_ass>(), "");
  static_assert(is_STL_associative_container<map_ass>(), "");
  static_assert(!is_STL_hashed_associative_container<map_ass>(), "");
}

void check_multimap() {
  using mmap_ass = std::multimap<int, int>;
  static_assert(is_STL_container<mmap_ass>(), "");
  static_assert(!is_STL_sequence<mmap_ass>(), "");
  static_assert(is_STL_forward_container<mmap_ass>(), "");
  static_assert(is_STL_reversible_container<mmap_ass>(), "");
  static_assert(!is_STL_random_access_container<mmap_ass>(), "");
  static_assert(is_STL_associative_container<mmap_ass>(), "");
  static_assert(!is_STL_hashed_associative_container<mmap_ass>(), "");
}

void check_hash() {
  using hash_ass = std::unordered_map<int, int>;
  static_assert(is_STL_container<hash_ass>(), "");
  static_assert(!is_STL_sequence<hash_ass>(), "");
  static_assert(is_STL_forward_container<hash_ass>(), "");
  static_assert(!is_STL_reversible_container<hash_ass>(), "");
  static_assert(!is_STL_random_access_container<hash_ass>(), "");
  static_assert(is_STL_associative_container<hash_ass>(), "");
  // std::unordered_map does not have resize function. At least for now.
  static_assert(!is_STL_hashed_associative_container<hash_ass>(), "");
}

void suggest_vector() {
  using vec_seq = mock::vector<int>;
  constexpr bool is_vector = is_STL_random_access_container<vec_seq>();
  static_assert(is_vector, "std::vector can be used in this case");
}

void suggest_list() {
  using list_seq = mock::list<int>;
  constexpr bool is_list = is_STL_reversible_container<list_seq>();
  static_assert(is_list, "std::list can be used in this case");
}

int main()
{
  check_list();
  check_vector();
  check_deque();
  check_map();
  check_multimap();
  check_hash();
  suggest_vector();
  suggest_list();
  return 0;
}

