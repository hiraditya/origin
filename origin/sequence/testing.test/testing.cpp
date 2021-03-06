// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <origin/sequence/concepts.hpp>
#include <origin/sequence/testing.hpp>

using namespace std;
using namespace origin;
using namespace origin::testing;

// Random number generator.
context cxt;

// Base case.
template <typename T>
void
check ()
{
}

template <typename T, typename property, typename... properties>
void
check ()
{
  // Initialize the container with a base sequence.
  T seq{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  assert (property()(seq));
  auto gen = quantify_over_range (seq);
  assert (property()(gen()));

  // Check rest of the properties.
  check<T, properties...>();
}

template <typename T>
void
check_functions ()
{
  // Initialize the container with a base sequence.
  T seq{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  // Check these for only the default sequences.
  // Cannot check these for a bounded range, because bounded
  // range does not have a size_type.
  check_readable_range(seq);
  check_permutable_range (seq);
  check_mutable_range (seq);
  check_weakly_incrementable_range (seq);
  check_incrementable_range (seq);
  check_input_range (seq);
  check_forward_range (seq);
  //check_writable_range (seq);
  //check_output_range (seq);
}

// All the sequence testing functors which take one argument.
#define SINGLE_ARGS  regularity_of_reading, pre_increment, post_increment, \
                     increment

int
main ()
{
  check<forward_list<int>, SINGLE_ARGS > ();
  check<list<int>, SINGLE_ARGS > ();
  check<vector<int>, SINGLE_ARGS > ();
  check_functions<forward_list<int> > ();
  check_functions<list<int> > ();
  check_functions<vector<int> > ();
  return 0;
}
