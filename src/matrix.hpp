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
		// Armadilo 
		// http://arma.sourceforge.net/docs.html#syntax
		
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
		struct Tdata
		{	
			union {
				std::array<T, R*C> data;
				std::array<std::array<T, C>, R> map;
			};

			Tdata() = default;
			
			Tdata(const std::initializer_list<T>&& il)
			{
				std::copy(il.begin(), il.end(), data.begin());

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
		};
		
		template<typename T>
		struct Tdata<4,4,T>
		{	
			union{
				std::array<T, 4*4> data;
				std::array<std::array<T, 4>, 4> map;
					struct {
					   T M00, M01, M02, M03,
						 M10, M11, M12, M13,
						 M20, M21, M22, M23,
						 M30, M31, M32, M33; 
					};
			};
			
			Tdata() = default;

			//http://stackoverflow.com/questions/15848781/constructor-for-nested-initializer-lists

			//Tdata(std::array<T,4*4>&& l) : data( l )
			//{}

			Tdata(std::array<std::array<T, 4>, 4>&& m) : map( m )
			{}
		};
    
	}//details
	
	template<size_t R,size_t C, typename T>
	struct TMatrix : public details::Tdata<R,C,T>
	{
		TMatrix() = default;

		using details::Tdata<R,C,T>::Tdata;//forward brace initializer
		
		using details::Tdata<R,C,T>::data;
		using details::Tdata<R,C,T>::map;
		
		std::array<T,4>& operator[](size_t index_row)
		{
			//out of range check DEBUG
			assert(index_row < R && "INDEX OUT OF RANGE");
			return map[index_row];
		}

		const std::array<T,4>& operator[](size_t index_row) const
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
	

	
	template<size_t R,size_t C, typename T>
	TMatrix<R,C,T> operator*(const TMatrix<R,C,T>& lhs, const typename std::enable_if<R==C, TMatrix<R,C,T> >::type& rhs)
	{
		TMatrix<R,C,T> z;
		
		  for (size_t r = 0; r < R; r++) {
			  for (size_t c = 0; c < C; c++) {
					z(r,c) = 0;
					  for (size_t i = 0; i < C; i++)
						  z(r,c) += lhs(r,i) * rhs(i,c);
                  }
          }
          
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
		
		//both of those work!! but i need 2x extra {{
		//return {{{{ 1.0 , 2.0, 3.0, 4.0},{  1.0 , 2.0, 3.0, 4.0},{  1.0 , 2.0, 3.0, 4.0},{  1.0 , 2.0, 3.0, 4.0}}}};
		//return {{{1.0 , 2.0, 3.0, 4.0,  1.0 , 2.0, 3.0, 4.0, 1.0 , 2.0, 3.0, 4.0,  1.0 , 2.0, 3.0, 4.0}}};
		
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
	
}
