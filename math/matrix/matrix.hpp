// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MATH_MATRIX_MATRIX_HPP
#define ORIGIN_MATH_MATRIX_MATRIX_HPP

#include <algorithm>
#include <cassert>

#include <origin/type/concepts.hpp>

namespace origin
{
  // Declarations
  template <typename T, std::size_t N, typename S>
    class matrix;

  template <typename T, std::size_t N>
    class matrix_ref;

  template <typename T, std::size_t N>
    class matrix_shape;


// Include traits needed to define the following type functions.
#include "impl/traits.hpp"


  // An alias to the reference-to-element type of the Matrix, M. The type
  // denoted by this alias depends on whehter or not M is const. For example:
  //
  //    using M = matrix<T, N>;
  //    Matrix_reference_type<M>       // is T&
  //    Matrix_reference_type<const M> // is const T&
  //
  // Note that M can be any type modeling the Matrix concept. If M does not
  // satisfy the requirements of the Matrix concept, then the resulting type
  // indicates substitution failure.
  template <typename M>
    using Matrix_reference = 
      If<Const<M>(), Associated_const_reference<M>, Associated_reference<M>>;


  // An alias to the pointer-to-element type of the matrix, M. The type
  // denoted by this alias depends on whehter or not M is const. For example:
  //
  //    using M = matrix<T, N>;
  //    Matrix_pointer_type<M>       // is T*
  //    Matrix_pointer_type<const M> // is const T*
  //
  // Note that M can be any type modeling the Matrix concept. If M does not
  // satisfy the requirements of the Matrix concept, then the resulting type
  // indicates substitution failure.
  template <typename M>
    using Matrix_pointer =
      If<Const<M>(), Associated_const_pointer<M>, Associated_pointer<M>>;


  // An alias to the reference-to-row type of the matrix, M. The type denoted
  // by this alias depends on the const-ness and rank of M. When the rank of
  // M is 1, this type is the same as the matrice's reference-to-eleemnt type.
  // Otherwise, the type is an instance of the matrix_ref class template.
  // Examples of usage and results are:
  //
  //    using M1 = matrix<T, 1>;
  //    using M2 = matrix<T, 2>;
  //    Matrix_row_reference
  //
  // Note that M can be any type modeling the Matrix concept. If M does not
  // satisfy the requirements of the Matrix concept, then the resulting type
  // indicates substitution failure.
  template <typename M>
    using Matrix_row_reference =
      If<Const<M>(),
        typename matrix_impl::get_associated_row_reference<M>::type,
        typename matrix_impl::get_associated_const_row_reference<M>::type>;



  // An alias to the shape type associated with a matrix.
  template <typename M>
    using Matrix_shape_type = typename matrix_impl::get_shape_type<M>::type;


  // Returns true if T is a matrix.
  //
  // FIXME: A matrix is substantially more complex than this. Finish defining
  // and implementing the concept.
  template <typename M>
    constexpr bool Matrix()
    {
      return Subst_succeeded<Matrix_shape_type<M>>();
    }



// Include additionl support operations and traits.
#include "impl/support.hpp"


  //////////////////////////////////////////////////////////////////////////////
  // Matrix
  //
  // The matrix template specifies an implementaiton of an N-dimensional
  // matrix parameterized over some value type T.
  //
  // The matrix is also parameterized over an underlying Storage type which
  // is responsible for the allocation and ownership of the underlying value
  // types. Storage is required to be a Random_access_container. 
  template <typename T, std::size_t N, typename Store = std::vector<T>>
    class matrix
    {
      using this_type           = matrix<T, N, Store>;
      using store_type          = Store;
    public:
      using allocator_type      = typename store_type::allocator_type;
      using value_type          = typename store_type::value_type;
      using reference           = typename store_type::reference;
      using const_reference     = typename store_type::const_reference;
      using pointer             = typename store_type::pointer;
      using const_pointer       = typename store_type::const_pointer;
      using size_type           = typename store_type::size_type;
      using difference_type     = typename store_type::difference_type;

      using shape_type          = matrix_shape<size_type, N>;
      using row_reference       = matrix_impl::Row_type<this_type, N - 1>;
      using const_row_reference = matrix_impl::Row_type<const this_type, N - 1>;

      using iterator            = typename store_type::iterator;
      using const_iterator      = typename store_type::const_iterator;


      // Default construction
      explicit matrix(const allocator_type& a = {})
        : dims(), elems()
      { }


      // Move semantics
      // Moving a matrix transfers the underlying state of the object x into
      // this object, leaving x empty.
      matrix(matrix&& x, const allocator_type& alloc = {})
        : dims(std::move(x.dims)), elems(std::move(x.elems), alloc)
      { }
      
      matrix& operator=(matrix&& x)
      {
        dims = std::move(x.dims);
        elems = std::move(x.elems);
        return *this;
      }


      // Copy semantics
      matrix(matrix const& x, const allocator_type& alloc = {})
        : dims(x.dims), elems(x.elems, alloc)
      { }

      matrix& operator=(matrix const& x) 
      { 
        dims = x.dims;
        elems = x.elems;
        return *this;
      }


      // Conversion from matrix_ref
      matrix(const matrix_ref<this_type, N>& x)
        : dims(x.shape()), elems(x.begin(), x.end())
      { }

      matrix& operator=(const matrix_ref<this_type, N>& x)
      {
        dims = x.shape();
        elems.assign(x.begin(), x.end());
      }


      // Construct a matrix of the specified shape.
      explicit
      matrix(const shape_type& shape, 
             const value_type& value = {},
             const allocator_type& alloc = {})
        : dims(shape), elems(shape.size(), value, alloc)
      { }

      // Refinement of the shape constructor for 1-D matrices. This allows
      // intialization over a single integer value.
      template <typename Int>
        explicit 
        matrix(Int n,
               const value_type& value = {},
               const allocator_type& alloc = {},
               matrix_impl::Requires_1D<Int, N>* = {})
          : dims(size_type(n)), elems(n, value, alloc)
        { }


      // Range initialization
      //
      // TODO: Can we make this work for arbitrary levels of nesting for the
      // initializer list? Probably, but we'll do that later.
      //
      // FIXME: Provide iterator-based operators too.
      matrix(const shape_type& shape,
             std::initializer_list<value_type> list,
             const allocator_type& alloc = {})
        : dims(shape), elems(list, alloc)
      {
        assert(dims.size() == elems.size());
      }



      // Returns the shape of the matrix.
      const shape_type& shape() const { return dims; }

      // Returns the rank of the matrix.
      static constexpr size_type rank() { return N; }

      // Returns the extent of the matrix in the nth dimension.
      size_type extent(size_type n) const { return dims.extent(n); }

      // Returns the total number of elements contained in the matrix.
      size_type size() const { return elems.size(); }


      // Element access
      template <typename... Args>
        reference operator()(Args... args);
      template <typename... Args>
        const_reference operator()(Args... args) const;


      // Row access
      row_reference       operator[](size_type n);
      const_row_reference operator[](size_type n) const;


      // Data access
      pointer       data()       { return elems.data(); }
      const_pointer data() const { return elems.data(); }


      // Vector addition
      template <typename M>
        Requires<Matrix<M>(), matrix&> operator+=(const M& x);
      template <typename M>
        Requires<Matrix<M>(), matrix&> operator-=(const M& x);

      // Scalar addition
      matrix& operator=(const value_type& value);
      matrix& operator+=(const value_type& value);
      matrix& operator-=(const value_type& value);

      // Scalar multiplication
      matrix& operator*=(const value_type& value);
      matrix& operator/=(const value_type& value);
      matrix& operator%=(const value_type& value);


      // Iterators
      iterator begin() { return elems.begin(); }
      iterator end()   { return elems.end(); }

      const_iterator begin() const { return elems.begin(); }
      const_iterator end() const   { return elems.end(); }

      private:
        shape_type dims;
        store_type elems;
      };


  // Element access
  //
  // FIXME: Write type constraints on Args.
  template <typename T, std::size_t N, typename S>
    template <typename... Args>
      inline auto
      matrix<T, N, S>::operator()(Args... args) -> reference
      {
        // Explicitly convert to size_type so that all of the argument types
        // will be the same when calling address. That will make it easy to
        // write optimizations against common cases later on.
        size_type off = matrix_impl::offset(dims.sizes(), size_type(args)...);
        return *(data() + off);
      }

  template <typename T, std::size_t N, typename S>
    template <typename... Args>
      inline auto
      matrix<T, N, S>::operator()(Args... args) const -> const_reference
      {
        size_type off = matrix_impl::offset(dims.sizes(), size_type(args)...);
        return *(data() + off);
      }

  template <typename T, std::size_t N, typename S>
    inline auto
    matrix<T, N, S>::operator[](size_type n) -> row_reference
    {
      return matrix_impl::row(*this, *this, n);
    }


  template <typename T, std::size_t N, typename S>
    inline auto
    matrix<T, N, S>::operator[](size_type n) const -> const_row_reference
    {
      return matrix_impl::row(*this, *this, n);
    }


  // Matrix addition
  // One matrix can be added to another (elementwise) only when they have the
  // same shape.
  template <typename T, std::size_t N, typename S>
    template <typename M>
      inline Requires<Matrix<M>(), matrix<T, N, S>&>
      matrix<T, N, S>::operator+=(const M& x)
      {
        static_assert(rank() == M::rank(), "");
        assert(shape() == x.shape());
        matrix_impl::assign_elements(
          begin(), end(), x.begin(), matrix_impl::plus_assign<value_type>{});
        return *this;
      }

  template <typename T, std::size_t N, typename S>
    template <typename M>
      inline Requires<Matrix<M>(), matrix<T, N, S>&>
      matrix<T, N, S>::operator-=(const M& x)
      {
        static_assert(rank() == M::rank(), "");
        assert(shape() == x.shape());
        matrix_impl::assign_elements(
          begin(), end(), x.begin(), matrix_impl::minus_assign<value_type>{});
        return *this;
      }


  // Scalar addition
  // A scalar can be added to a matrix, adding that value to each element of
  // the matrix.
  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator=(const value_type& value)  
    { 
      matrix_impl::assign_value(
        begin(), end(), value, matrix_impl::assign<value_type>{}); 
      return *this;
    }
      
  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator+=(const value_type& value) 
    { 
      matrix_impl::assign_value(
        begin(), end(), value, matrix_impl::plus_assign<value_type>{}); 
      return *this;
    }
      
  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator-=(value_type const& value) 
    { 
      matrix_impl::assign_value(
        begin(), end(), value, matrix_impl::minus_assign<value_type>{}); 
      return *this;
    }
  

  // Scalar multiplication
  // A matrix can be multiplied by a scalar, scaling each element by that
  // value.
  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator*=(value_type const& value) 
    { 
      matrix_impl::assign_value(
        begin(), end(), value, matrix_impl::multiplies_assign<value_type>{}); 
      return *this;
    }

  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator/=(value_type const& value) 
    { 
      matrix_impl::assign_value(begin(), end(), value, 
        matrix_impl::divides_assign<value_type>{}); 
      return *this;
    }
      
  // This operation is only defined when T is a model of Euclidean domain.
  template <typename T, std::size_t N, typename S>
    inline matrix<T, N, S>& 
    matrix<T, N, S>::operator%=(value_type const& value) 
    { 
      matrix_impl::assign_value(begin(), end(), value, 
        matrix_impl::modulus_assign<value_type>{}); 
      return *this;
    }

} // namespace origin

#include "matrix_shape.hpp"
#include "matrix_ref.hpp"
#include "matrix_ops.hpp"

#endif
