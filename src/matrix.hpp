#pragma once


#include <initializer_list>
#include <array>
#include <iostream>
#include <cassert>
#include <cmath>

#include <vector.hpp>

namespace talg
{
	//http://christophercrouzet.com/blog/post/2015/01/12/Nested-Initializer-Lists-for-Multidimensional-Arrays
	/*
	if (values.size() > size()) {
	std::ostringstream message;
	message << "Elements in excess: "
	<< "expected " << size() << ", "
	<< "got " << values.size() << ".";

	throw std::invalid_argument(message.str());
	}
	*/

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
			}
		};
		
		template<typename T>
		struct Tdata<4,4,T>
		{	
			union{
				std::array<T, 4*4> data;
				std::array<std::array<T, 4>, 4> map;
			};
			
			Tdata() = default;
			
			//Tdata(T args[4*4]) 
			//{
			//}

			//http://stackoverflow.com/questions/15848781/constructor-for-nested-initializer-lists

			Tdata(std::array<std::array<T, 4>, 4>&& m) : map( m )
			{
			}
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
		
	};
	
    
    //TODO >>    
    template<size_t R,size_t C, typename T>
	std::ostream& operator << (std::ostream &o, const TMatrix<R,C,T>& m)
	{
		o << "mat(|";

		for (auto a : m.data)
			o << a << "|";

		o << ")";

		return o;
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
