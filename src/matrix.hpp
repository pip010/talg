#pragma once


#include <initializer_list>
#include <array>
#include <iostream>
#include <cassert>
#include <cmath>

#include <vector.hpp>

namespace talg
{
	// multi-dim indexing
	//http://nadeausoftware.com/articles/2012/06/c_c_tip_how_loop_through_multi_dimensional_arrays_quickly
	

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
			{
			}
			
			TMdata(std::array<std::array<T, 4>, 4>&& m) : adata(m)
			{

			}

			TMdata(std::array<std::array<T, 4>, 4>& m) : adata(m)
			{
				
			}

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
		TMatrix() = default;

		using details::TMdata<R,C,T>::TMdata;//forward brace initializer
		
		using details::TMdata<R,C,T>::data;
		using details::TMdata<R,C,T>::map;
		
		
		T* operator[](size_t index_row)
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			return map[index_row];
		}

		const T* operator[](size_t index_row) const
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			return map[index_row];
		}
		
		
		//basic
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


		
		//query
		//vector<R> operator()(size_t index_row, query::q_end)
		//vector<C> operator()(query::q_end, size_t index_col)
		
		//dynamic?
		//matrix_view<T> operator()(query::q_end, query::q_range)
		//matrix_view<T> operator()(query::q_range, query::q_end)
		//matrix_view<T> operator()(query::q_range, query::q_range)
		//matrix_view<T> operator()(query::q_end, query::q_end) //worth doing symmetry?
	};
	
    
    //TODO operator >>    
    template<size_t R,size_t C, typename T>
	std::ostream& operator << (std::ostream &o, const TMatrix<R,C,T>& m)
	{
		o << "mat(|";

		for (auto a : m.data)
			o << a << "|";

		o << ")";

		return o;
	}
	

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
          
          //TODO in order to support larger static/dynamic matrices
          //http://functionspace.com/articles/40/Cache-aware-Matrix-Multiplication---Naive-isn--039;t-that-bad-
          
          /*
          n = 4096;
			for(i=0;i<n;i++)
			{
				for(k=0;k<n;k++)
				{
					for(j=0;j<n;j++)
						C[i][j]+=A[i][k]*B[k][j];
				 }
			}
          */
          
          return z;
	}
	
	
	template<typename T>
	TMatrix<4,4,T> operator*(const TMatrix<4,4,T>& lhs, const TMatrix<4,4,T>& rhs)
	{
		
		//TODO VS2015 completely got confused and tried to return TVector<16, T, Tcat> !!!!???
		/*
		return 	{{{
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
			}}};
		*/

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

		if (det == 0.0) throw std::invalid_argument("invalid operation (devison by 0)");

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


}
