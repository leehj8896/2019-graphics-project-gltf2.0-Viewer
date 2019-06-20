#ifndef KMUVCL_GRAPHICS_MAT_HPP
#define KMUVCL_GRAPHICS_MAT_HPP

#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cassert>

namespace kmuvcl {
  namespace math {

    template <unsigned int M, unsigned int N, typename T>
    class mat
    {
    public:
      mat()
      {
        set_to_zero();
      }

      mat(const T elem)
      {
        std::fill(val, val + M*N, elem);
      }

      T& operator()(unsigned int r, unsigned int c)
      {
        return  val[r + c*M];   // column major
      }

      const T& operator()(unsigned int r, unsigned int c) const
      {
        return  val[r + c*M];   // column major
      }

      // type casting operators
      operator const T* () const
      {
        return  val;
      }

      operator T* ()
      {
        return  val;
      }

      void set_to_zero()
      {
        std::fill(val, val + M*N, static_cast<T>(0));
      }

      void set_to_identity()
      {
        assert(M == N);
        
        set_to_zero();
        for (unsigned int i = 0; i < M; ++i)
          (*this)(i, i) = 1;
      }

      void get_ith_column(unsigned int i, vec<M, T>& col) const
      {
        T* dest       = (T*) col;
        const T* src  = val + i*M;

        std::memcpy(dest, src, sizeof(T)*M);
      }

      void set_ith_column(unsigned int i, const vec<M, T>& col)
      {
        T* dest       = val + i*M;
        const T* src  = (const T*)col;

        std::memcpy(dest, src, sizeof(T)*M);
      }

      void get_ith_row(unsigned int i, vec<N, T>& row) const
      {
        for (unsigned int c = 0; c < N; ++c)
          row(c) = (*this)(i, c);
      }

      void set_ith_row(unsigned int i, const vec<N, T>& row)
      {
        for (unsigned int c = 0; c < N; ++c)
          (*this)(i, c) = row(c);
      }

      mat<N, M, T> transpose() const
      {
        
        mat<N, M, T>  trans;
        vec<M, T>     col;

        for (unsigned int i = 0; i < N; ++i)
        {
          get_ith_column(i, col);
          trans.set_ith_row(i, col);
        }

        return  trans;
      }

    protected:
      T val[M*N];   // column major
    };

    typedef mat<3, 3, float>    mat3x3f;
    typedef mat<3, 3, double>   mat3x3d;
    typedef mat<3, 3, float>    mat3f;
    typedef mat<3, 3, double>   mat3d;

    typedef mat<4, 4, float>    mat4x4f;
    typedef mat<4, 4, double>   mat4x4d;
    typedef mat<4, 4, float>    mat4f;
    typedef mat<4, 4, double>   mat4d;

  } // math
} // kmuvcl

#include "operator.hpp"

#endif // #ifndef KMUVCL_GRAPHICS_MAT_HPP
