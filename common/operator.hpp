#ifndef KMUVCL_GRAPHICS_OPERATOR_HPP
#define KMUVCL_GRAPHICS_OPERATOR_HPP

#include "vec.hpp"
#include "mat.hpp"

namespace kmuvcl {
  namespace math {

    /// w_n = u_n + v_n
    template <unsigned int N, typename T>
    vec<N, T> operator+ (const vec<N, T>& u, const vec<N, T>& v)
    {
      vec<N, T>  w;

      for (unsigned int i = 0; i < N; ++i)
        w(i) = u(i) + v(i);

      return  w;
    }

    /// w_n = u_n - v_n
    template <unsigned int N, typename T>
    vec<N, T> operator- (const vec<N, T>& u, const vec<N, T>& v)
    {
      vec<N, T>  w;

      for (unsigned int i = 0; i < N; ++i)
        w(i) = u(i) - v(i);

      return  w;
    }

    /// y_n = s * x_n
    template <unsigned int N, typename T>
    vec<N, T> operator* (const T s, const vec<N, T>& x)
    {
      vec<N, T>  y;
      
      for (unsigned int i = 0; i < N; ++i)
        y(i) = s*x(i);

      return  y;
    }

    /// s = u_n * v_n (dot product)
    template <unsigned int N, typename T>
    T dot(const vec<N, T>& u, const vec<N, T>& v)
    {
      T val = 0;
      
      for (unsigned int i = 0; i < N; ++i)
        val += u(i) * v(i);

      return  val;
    }

    /// w_3 = u_3 x v_3 (cross product, only for vec3)
    template <typename T>
    vec<3,T> cross(const vec<3, T>& u, const vec<3, T>& v)
    {
      vec<3, T>  w;

      w(0) = u(1)*v(2) - u(2)*v(1);
      w(1) = u(2)*v(0) - u(0)*v(2);
      w(2) = u(0)*v(1) - u(1)*v(0);

      return  w;
    }

    /// y_m = A_{mxn} * x_n
    template <unsigned int M, unsigned int N, typename T>
    vec<M, T> operator* (const mat<M, N, T>& A, const vec<N, T>& x)
    {
      vec<M, T>   y, col;

      for (unsigned int i = 0; i < N; ++i)
      {
        A.get_ith_column(i, col);
        y += x(i)*col;
      }        

      return  y;
    }

    /// y_n = x_m * A_{mxn}
    template <unsigned int M, unsigned int N, typename T>
    vec<N, T> operator* (const vec<M, T>& x, const mat<M, N, T>& A)
    {
      vec<N, T>   y;
      vec<M, T>   col;

      for (unsigned int i = 0; i < N; ++i)
      {
        A.get_ith_column(i, col);
        y(i) = dot(x, col);
      }

      return  y;
    }

    /// C_{mxl} = A_{mxn} * B_{nxl}
    template <unsigned int M, unsigned int N, unsigned int L, typename T>
    mat<M, L, T> operator* (const mat<M, N, T>& A, const mat<N, L, T>& B)
    {
      mat<M, L, T>   C;
      vec<N, T>   row;
      vec<N, T>   col;

      for (unsigned int i = 0; i < M; ++i)
      {
        A.get_ith_row(i, row);

        for (unsigned int j = 0; j < L; ++j)
        {
	  B.get_ith_column(j, col);
          C(i,j) = dot(row, col);
        }
      }

      return  C;
    }

    /// ostream for vec class
    template <unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const vec<N, T>& v)
    {
      os << "[";
      for (unsigned int i = 0; i < N - 1; ++i)
        os << v(i) << ", ";
      os << v(N - 1);
      os << "]";

      return  os;
    }

    /// ostream for mat class
    template <unsigned int M, unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const mat<M, N, T>& A)
    {
      vec<N, T>  row;
      for (unsigned int i = 0; i < M; ++i)
      {
        A.get_ith_row(i, row);
        os << row << std::endl;
      }

      return  os;
    }

  } // math
} // kmuvcl

#endif // KMUVCL_GRAPHICS_OPERATOR_HPP
