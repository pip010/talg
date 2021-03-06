#pragma once


#include <initializer_list>
#include <array>
#include <iostream>
#include <cassert>
#include <cmath>

#include <limits>

#include "vector.hpp"

namespace talg
{
	namespace query
	{

		struct q_end {};

		struct q_range {
			size_t begin;
			size_t end;
		};


		struct vector_view
		{
			private:
			q_range range;
		};

		struct matrix_view
		{
			private:
			q_range rows_ranage;
			q_range cols_range;
		};

	}

	namespace details
	{
		template<size_t R,size_t C, typename T>
		struct TMdata
		{
			union {
				T data[R*C];
				T map[R][C];
				//std::array<T, R*C> data;
				//std::array<std::array<T, C>, R> map;
			};

			TMdata() = default;

			TMdata(const std::initializer_list<T>&& il)
			{
				//std::copy(il.begin(), il.end(), data.begin());
				std::copy(il.begin(), il.end(), data);

				/*
				if (values.size() > size()) {
				std::ostringstream message;
				message << "Elements in excess: "
				<< "expected " << size() << ", "
				<< "got " << values.size() << ".";

				throw std::invalid_argument(message.str());
				}
				*/
			}


			/*
			//http://christophercrouzet.com/blog/post/2015/01/12/Nested-Initializer-Lists-for-Multidimensional-Arrays
			//http://www.informit.com/articles/article.aspx?p=1852519
			//http://stackoverflow.com/questions/15848781/constructor-for-nested-initializer-lists
			Tdata(const std::initializer_list< std::initializer_list<T> >&& ill)
			{
				//std::copy(il.begin(), il.end(), data.begin());l
				//std::copy(il.begin(), il.end(), data);
				size_t s = 0;
				for(auto& il : ill)
				{
					std::copy(il.begin(), il.end(), data[s]);
					++s;
				}
			}
			*/

		};

		template<typename T>
		struct TMdata<4,4,T>
		{
			union{
				std::array<std::array<T, 4>, 4> adata;
				//TVector<4, TVector<4, T, vtag>, vtag> amap;
				T data[4*4];
				T map[4][4];

				struct {
					   T M00, M01, M02, M03,
						 M10, M11, M12, M13,
						 M20, M21, M22, M23,
						 M30, M31, M32, M33;
					};
			};

			TMdata() = default;


			TMdata(
				T m00, T m01, T m02, T m03,
				T m10, T m11, T m12, T m13,
				T m20, T m21, T m22, T m23,
				T m30, T m31, T m32, T m33):
				M00(m00), M01(m01), M02(m02), M03(m03),
				M10(m10), M11(m11), M12(m12), M13(m13),
				M20(m20), M21(m21), M22(m22), M23(m23),
				M30(m30), M31(m31), M32(m32), M33(m33)
			{}

			TMdata(std::array<std::array<T, 4>, 4>&& m) 
				: 
				adata(m)
			{}

			TMdata(std::array<std::array<T, 4>, 4>& m) 
				: 
				adata(m)
			{}

			//template <typename T, typename... Types>
			//TMdata(T t, Types... ts) : m_Data{ { t, ts... } } {}

			//TMdata(TVector<4, TVector<4, T, vtag>, vtag>&& m) :
			//	amap( m )
			//{}
		};

	}//details

	template<size_t R,size_t C, typename T>
	struct TMatrix : public details::TMdata<R,C,T>
	{
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef T* pointer;
		using ptr = pointer;

		typedef const T* const_pointer;
		using cptr = const_pointer;

		typedef T& reference;
		using ref = reference;

		typedef const T& const_reference;
		using cref = const_reference;


		TMatrix() = default;

		// inherit constructor
		using details::TMdata<R,C,T>::TMdata;

		// forward brace initializer
		using details::TMdata<R,C,T>::data;
		using details::TMdata<R,C,T>::map;


		static constexpr TMatrix<4, 4, T> ZERO()
		{
			return{
			 0, 0, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0,
			 0, 0, 0, 0
			};
		};

		static constexpr TMatrix<4,4,T> IDENTITY() 
		{
			return{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			};
		};

		// actually operator [][]
		T* operator[](size_t index_row)
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			return map[index_row];
		}

		// actually operator [][]
		const T* operator[](size_t index_row) const
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			return map[index_row];
		}

		T& operator()(size_t index_row, size_t index_col)
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			assert(index_col < C && "INDEX OUT OF RANGE");
			return map[index_row][index_col];
		}
		const T& operator()(size_t index_row, size_t index_col) const
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			assert(index_col < C && "INDEX OUT OF RANGE");
			return map[index_row][index_col];
		}

		T& operator()(size_t index)
		{
			//out of range check DEBUG
			assert(index < R*C && "INDEX OUT OF RANGE");

			return data[index];
		}

		const T& operator()(size_t index) const
		{
			//out of range check DEBUG
			assert(index < R*C && "INDEX OUT OF RANGE");
			return data[index];
		}

		T& at(size_t index_row, size_t index_col)
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			assert(index_col < C && "INDEX OUT OF RANGE");

			if (index_row >= R)
				throw std::out_of_range();

			if (index_col >= C)
				throw std::out_of_range();

			return map[index_row][index_col];
		}

		const T& at(size_t index_row, size_t index_col) const
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			assert(index_col < C && "INDEX OUT OF RANGE");

			if (index_row >= R)
				throw std::out_of_range();

			if (index_col >= C)
				throw std::out_of_range();

			return map[index_row][index_col];
		}

		T& at(size_t index)
		{
			//out of range check DEBUG
			assert(index < R*C && "INDEX OUT OF RANGE");

			if (index >= R*C)
				throw std::out_of_range();


			return data[index];
		}

		const T& at(size_t index) const
		{
			//out of range check DEBUG
			assert(index < R*C && "INDEX OUT OF RANGE");

			if (index >= R*C)
				throw std::out_of_range();

			return data[index];
		}

		constexpr size_t size() const
		{
			return R*C;
		}

		template<typename Tcat>
		TVector<C, T, Tcat> query(size_t index_row, query::q_end empty_col) const
		{
			TVector<C, T, Tcat> row_vec;

			  for (size_t c = 0; c < C; ++c)
			  {
				  row_vec[c] = map[index_row][c];
			  }

			return row_vec;
		}

		template<typename Tcat>
		TVector<R, T, Tcat> query(query::q_end empty_row, size_t index_col) const
		{
			TVector<R, T, Tcat> col_vec;

			  for (size_t r = 0; r < R; ++r)
			  {
				  col_vec[r] = map[r][index_col];
			  }

			return col_vec;
		}

		template<typename Tcat>
		TMatrix<4, 4, T> operator*= (const TVector<R, T, Tcat>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		TMatrix<4, 4, T> operator*= (const TMatrix<4, 4, T>& rhs)
		{
			*this = *this * rhs;
			return *this;
		}

		//dynamic?
		//matrix_view<T> operator()(query::q_end, query::q_range)
		//matrix_view<T> operator()(query::q_range, query::q_end)
		//matrix_view<T> operator()(query::q_range, query::q_range)
		//matrix_view<T> operator()(query::q_end, query::q_end) //worth doing symmetry?

		cptr begin() const
		{
			return data;
		}

		cptr end() const
		{
			return data+(R*C);
		}

		ptr begin()
		{
			return data;
		}

		ptr end()
		{
			return data+(R*C);
		}

	};




	//TODO gcc has no ambiguty but for VS I have to explictly disabel the case for matrix 4x4 and other overloads
	template<size_t R,size_t C, typename T>
	TMatrix<R,C,T> operator*(const TMatrix<R,C,T>& lhs, const typename std::enable_if<R==C && R != 4, TMatrix<R,C,T> >::type& rhs)
	{
		TMatrix<R,C,T> z;

		  for (size_t r = 0; r < R; r++) {
			  for (size_t c = 0; c < C; c++) {
					z(r,c) = 0;
					  for (size_t i = 0; i < C; i++)
						  z(r,c) += lhs(r,i) * rhs(i,c);
                  }
          }

          return z;
	}


	template<typename T>
	TMatrix<4,4,T> operator*(const TMatrix<4,4,T>& lhs, const TMatrix<4,4,T>& rhs)
	{

		TMatrix<4, 4, T> m(
			lhs.M00*rhs.M00 + lhs.M01*rhs.M10 + lhs.M02*rhs.M20 + lhs.M03*rhs.M30,
			lhs.M00*rhs.M01 + lhs.M01*rhs.M11 + lhs.M02*rhs.M21 + lhs.M03*rhs.M31,
			lhs.M00*rhs.M02 + lhs.M01*rhs.M12 + lhs.M02*rhs.M22 + lhs.M03*rhs.M32,
			lhs.M00*rhs.M03 + lhs.M01*rhs.M13 + lhs.M02*rhs.M23 + lhs.M03*rhs.M33,

			lhs.M10*rhs.M00 + lhs.M11*rhs.M10 + lhs.M12*rhs.M20 + lhs.M13*rhs.M30,
			lhs.M10*rhs.M01 + lhs.M11*rhs.M11 + lhs.M12*rhs.M21 + lhs.M13*rhs.M31,
			lhs.M10*rhs.M02 + lhs.M11*rhs.M12 + lhs.M12*rhs.M22 + lhs.M13*rhs.M32,
			lhs.M10*rhs.M03 + lhs.M11*rhs.M13 + lhs.M12*rhs.M23 + lhs.M13*rhs.M33,

			lhs.M20*rhs.M00 + lhs.M21*rhs.M10 + lhs.M22*rhs.M20 + lhs.M23*rhs.M30,
			lhs.M20*rhs.M01 + lhs.M21*rhs.M11 + lhs.M22*rhs.M21 + lhs.M23*rhs.M31,
			lhs.M20*rhs.M02 + lhs.M21*rhs.M12 + lhs.M22*rhs.M22 + lhs.M23*rhs.M32,
			lhs.M20*rhs.M03 + lhs.M21*rhs.M13 + lhs.M22*rhs.M23 + lhs.M23*rhs.M33,

			lhs.M30*rhs.M00 + lhs.M31*rhs.M10 + lhs.M32*rhs.M20 + lhs.M33*rhs.M30,
			lhs.M30*rhs.M01 + lhs.M31*rhs.M11 + lhs.M32*rhs.M21 + lhs.M33*rhs.M31,
			lhs.M30*rhs.M02 + lhs.M31*rhs.M12 + lhs.M32*rhs.M22 + lhs.M33*rhs.M32,
			lhs.M30*rhs.M03 + lhs.M31*rhs.M13 + lhs.M32*rhs.M23 + lhs.M33*rhs.M33
			 );

		return m;

	}


	template<typename T, typename Tcat>
	TVector<4, T, Tcat> operator*(const TMatrix<4,4,T>& m, const TVector<4, T, Tcat>& vec)
	{
		return {
			m.map[0][0]*vec[0] + m.map[0][1]*vec[1] + m.map[0][2]*vec[2] + m.map[0][3]*vec[3],
			m.map[1][0]*vec[0] + m.map[1][1]*vec[1] + m.map[1][2]*vec[2] + m.map[1][3]*vec[3],
			m.map[2][0]*vec[0] + m.map[2][1]*vec[1] + m.map[2][2]*vec[2] + m.map[2][3]*vec[3],
			m.map[3][0]*vec[0] + m.map[3][1]*vec[1] + m.map[3][2]*vec[2] + m.map[3][3]*vec[3]
		};
	}


//===============================

	// template<typename T, typename Tcat>
	// TVector<4, T, Tcat> TMatrix<4,4,T>::q(size_t index_row, query::q_end empty_col) const
	// {
	// 	return { map[index_row][0], map[index_row][1], map[index_row][2], map[index_row][3] };
	// }

//===============================

	//Builds Matrix minor via inclusive explicit defenition of row-columns
	template<typename T>
	T build_minor(const TMatrix<4, 4, T>& m,
		const size_t r0, const size_t r1, const size_t r2,
		const size_t c0, const size_t c1, const size_t c2)
	{
		T ret(
			m(r0,c0) * ( m(r1,c1) * m(r2,c2) - m(r2,c1) * m(r1,c2) ) -
			m(r0,c1) * ( m(r1,c0) * m(r2,c2) - m(r2,c0) * m(r1,c2) ) +
			m(r0,c2) * ( m(r1,c0) * m(r2,c1) - m(r2,c0) * m(r1,c1) )
			);

 		return ret;
	}

	/*
	template<size_t R, size_t C, typename T>
	T determinant( const typename std::enable_if<R == C && R != 4, TMatrix<R, C, T> >::type& m)
	{

	}
	template<size_t R, size_t C, typename T>
	TMatrix<R, C, T> inverse(const typename std::enable_if<R == C && R != 4, TMatrix<R, C, T> >::type& m)
	{

	}
	*/

	template<size_t R, size_t C, typename T>
	typename std::enable_if<R == C, T >::type trace( const TMatrix<R, C, T>& m)
	{
			T v = 0;
			for(int i = 0; i < R; ++i)
			{
				v += m[i][i];
			}
			return v;
	}

	//TODO adjoin / conjugate transpose
	template<typename T>
	TMatrix<4, 4, T> transpose(const TMatrix<4, 4, T>& m)
	{
		TMatrix<4, 4, T> mt(m);

		mt.M01 = m.M10;
		mt.M02 = m.M20;
		mt.M03 = m.M30;

		mt.M10 = m.M01;
		mt.M12 = m.M21;
		mt.M13 = m.M31;

		mt.M20 = m.M02;
		mt.M21 = m.M12;
		mt.M23 = m.M32;

		mt.M30 = m.M03;
		mt.M31 = m.M13;
		mt.M32 = m.M23;

		return mt;
	}

	template<typename T>
	T determinant(const TMatrix<4, 4, T>& m)
	{
		T ret(
			m[0][0] * build_minor(m, 1, 2, 3, 1, 2, 3) -
			m[0][1] * build_minor(m, 1, 2, 3, 0, 2, 3) +
			m[0][2] * build_minor(m, 1, 2, 3, 0, 1, 3) -
			m[0][3] * build_minor(m, 1, 2, 3, 0, 1, 2)
			);

		return ret;
	}

	template<typename T>
	TMatrix<4, 4, T> inverse(const TMatrix<4, 4, T>& m)
	{
		T det = determinant(m);

		assert(det != 0);

		if (det == 0.0) throw std::invalid_argument("invalid operation (divison by 0)");

		return
		{
			(m.M12*m.M23*m.M31 - m.M13*m.M22*m.M31 + m.M13*m.M21*m.M32 - m.M11*m.M23*m.M32 - m.M12*m.M21*m.M33 + m.M11*m.M22*m.M33) / det,
			(m.M03*m.M22*m.M31 - m.M02*m.M23*m.M31 - m.M03*m.M21*m.M32 + m.M01*m.M23*m.M32 + m.M02*m.M21*m.M33 - m.M01*m.M22*m.M33) / det,
			(m.M02*m.M13*m.M31 - m.M03*m.M12*m.M31 + m.M03*m.M11*m.M32 - m.M01*m.M13*m.M32 - m.M02*m.M11*m.M33 + m.M01*m.M12*m.M33) / det,
			(m.M03*m.M12*m.M21 - m.M02*m.M13*m.M21 - m.M03*m.M11*m.M22 + m.M01*m.M13*m.M22 + m.M02*m.M11*m.M23 - m.M01*m.M12*m.M23) / det,
			(m.M13*m.M22*m.M30 - m.M12*m.M23*m.M30 - m.M13*m.M20*m.M32 + m.M10*m.M23*m.M32 + m.M12*m.M20*m.M33 - m.M10*m.M22*m.M33) / det,
			(m.M02*m.M23*m.M30 - m.M03*m.M22*m.M30 + m.M03*m.M20*m.M32 - m.M00*m.M23*m.M32 - m.M02*m.M20*m.M33 + m.M00*m.M22*m.M33) / det,
			(m.M03*m.M12*m.M30 - m.M02*m.M13*m.M30 - m.M03*m.M10*m.M32 + m.M00*m.M13*m.M32 + m.M02*m.M10*m.M33 - m.M00*m.M12*m.M33) / det,
			(m.M02*m.M13*m.M20 - m.M03*m.M12*m.M20 + m.M03*m.M10*m.M22 - m.M00*m.M13*m.M22 - m.M02*m.M10*m.M23 + m.M00*m.M12*m.M23) / det,
			(m.M11*m.M23*m.M30 - m.M13*m.M21*m.M30 + m.M13*m.M20*m.M31 - m.M10*m.M23*m.M31 - m.M11*m.M20*m.M33 + m.M10*m.M21*m.M33) / det,
			(m.M03*m.M21*m.M30 - m.M01*m.M23*m.M30 - m.M03*m.M20*m.M31 + m.M00*m.M23*m.M31 + m.M01*m.M20*m.M33 - m.M00*m.M21*m.M33) / det,
			(m.M01*m.M13*m.M30 - m.M03*m.M11*m.M30 + m.M03*m.M10*m.M31 - m.M00*m.M13*m.M31 - m.M01*m.M10*m.M33 + m.M00*m.M11*m.M33) / det,
			(m.M03*m.M11*m.M20 - m.M01*m.M13*m.M20 - m.M03*m.M10*m.M21 + m.M00*m.M13*m.M21 + m.M01*m.M10*m.M23 - m.M00*m.M11*m.M23) / det,
			(m.M12*m.M21*m.M30 - m.M11*m.M22*m.M30 - m.M12*m.M20*m.M31 + m.M10*m.M22*m.M31 + m.M11*m.M20*m.M32 - m.M10*m.M21*m.M32) / det,
			(m.M01*m.M22*m.M30 - m.M02*m.M21*m.M30 + m.M02*m.M20*m.M31 - m.M00*m.M22*m.M31 - m.M01*m.M20*m.M32 + m.M00*m.M21*m.M32) / det,
			(m.M02*m.M11*m.M30 - m.M01*m.M12*m.M30 - m.M02*m.M10*m.M31 + m.M00*m.M12*m.M31 + m.M01*m.M10*m.M32 - m.M00*m.M11*m.M32) / det,
			(m.M01*m.M12*m.M20 - m.M02*m.M11*m.M20 + m.M02*m.M10*m.M21 - m.M00*m.M12*m.M21 - m.M01*m.M10*m.M22 + m.M00*m.M11*m.M22) / det
		};
	}

	template<size_t R, size_t C>
	bool eq(const TMatrix<R, C, float>& lhs, const TMatrix<R, C, float>& rhs, float epsilon = (std::numeric_limits<float>::epsilon()*100) )
	{
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (abs(lhs(i) - rhs(i)) > epsilon) return false;
		}

		return true;
	}

	template<size_t R, size_t C>
	bool eq(const TMatrix<R, C, double>& lhs, const TMatrix<R, C, double>& rhs, double epsilon = (std::numeric_limits<float>::epsilon()*100) )
	{
		for (size_t i = 0; i < lhs.size(); ++i)
		{
			if (abs(lhs(i) - rhs(i)) > epsilon) return false;
		}

		return true;
	}

	template<size_t R,size_t C, typename T>
	std::ostream& operator<< (std::ostream &os, const TMatrix<R,C,T>& m)
	{
		for (auto a : m.data)
			os << a << " ";

		return os;
	}

	template<size_t R,size_t C, typename T>
	std::istream& operator>> (std::istream &is, const TMatrix<R,C,T>& m)
	{
		for (auto a : m.data)
			is >> a;

		return is;
	}

}//end namespace
