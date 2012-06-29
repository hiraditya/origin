// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <iostream>

#include <origin/math/matrix.hpp>

using namespace std;
using namespace origin;


int main()
{
  typedef matrix<int, 1> Matrix;
  
  Matrix m1;
  assert(m1.size() == 0);
  assert(m1.dim() == 0);
  
  Matrix m2(3);
  cout << m2 << '\n';
  
  Matrix m3(3, 1);
  cout << m3 << '\n';
  
  m3 += 2;
  cout << m3 << '\n';
  assert(m3 == Matrix(3, 3));

  Matrix m4 = m3 + 3;
  cout << m4 << '\n';
  assert(m4 == Matrix(3, 6));

  Matrix m5 = m3 * 3;
  cout << m5 << '\n';
  assert((m5 == Matrix{9, 9, 9}));
  
  Matrix m6 = {1, 2, 3, 4};
  cout << m6 << '\n';
  cout << m6 % 2 << '\n';
  assert((m6 % 2 == Matrix{1, 0, 1, 0}));
}
