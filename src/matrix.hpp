#include <initializer_list>


#include <array>

#include <iostream>

#include <cassert>

#include <cmath>

namespace talg
{
	namespace details
	{   
		template<size_t R,size_t C, typename T>
		struct Tdata
		{	
			std::array<T, R*C> data;

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
			
			Tdata(const std::initializer_list<T>&& il)
			{
				//std::copy(il.begin(), il.end(), data.begin());
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
