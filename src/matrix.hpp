

#include <initializer_list>

#include <array>

#include <iostream>

#include <cassert>

#include <cmath>

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
				//std::copy(il.begin(), il.end(), data.begin());
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

			Tdata(std::array<std::array<T, 4>, 4>&& m) : map{ m }
			{
			}
		};
    
	}
	
	template<size_t R,size_t C, typename T>
	struct TMatrix : public details::Tdata<R,C,T>
	{
		TMatrix() = default;

		using details::Tdata<R,C,T>::Tdata;//forward brace initializer
		
		//using details::Tdata<R,C,T>::data;
	};
}
