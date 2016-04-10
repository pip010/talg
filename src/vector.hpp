#pragma once

#include <initializer_list>


#include <array>

#include <iostream>

#include <cassert>

#include <cmath>

namespace talg
{
	/* Decoration for templated vectors */
	class vtag {};
	class vtag_xy {};
	class vtag_xyz {};
	class vtag_xyzw {};
	class vtag_ijk {};
	class vtag_rgb {};
	class vtag_rgba {};

	namespace details
	{

		template<int N, typename T, typename Tcat>
		struct TVdata
		{
			//std::array<T, N> data;
			T data[N];

			TVdata() = default;
			//TVdata(const T&) = default;
			//TVdata(T&&) = default;
			//T& operator=(const T&) = default;
			//T& operator=(T&&) = default;


			TVdata(const std::initializer_list<T>&& il)
			{
				std::copy(il.begin(), il.end(), data);
			}

			//
			//template <typename T, typename... Types>
			//TVdata(T t, Types... ts) : data{ { t, ts... } } 
			//{}
			//

			//template<typename ...T>
			//TVdata(T&&...t):data{ std::forward<T>(t)... }
			//{
			//}


			//template <class U, class... Ts>
			//X(U n, Ts... rest) : X(rest...) { ..the recursive work .. }
			

			//TODO consider to dife some og those
			//typedef array<_Ty, _Size> _Myt;
			//typedef _Ty value_type;
			//typedef size_t size_type;
			//typedef ptrdiff_t difference_type;
			//typedef _Ty *pointer;
			//typedef const _Ty *const_pointer;
			//typedef _Ty& reference;
			//typedef const _Ty& const_reference;
		};

		template<typename T>
		struct TVdata<3, T, vtag_ijk>
		{
			union {
				struct { T i; T j; T k; };
				//std::array<T, 3> data;
				T data[3];
			};

			TVdata() = default;

			TVdata(T t1, T t2, T t3) :
				i(t1), j(t2), k(t3)
			{}
		};

		template<typename T>
		struct TVdata<3, T, vtag_xyz>
		{
			union {
				struct { T x; T y; T z; };
				//std::array<T, 3> data;
				T data[3];
			};

			TVdata() = default;

			TVdata(T t1, T t2, T t3) :
				x(t1), y(t2), z(t3)
			{}
		};

		template<typename T>
		struct TVdata<4, T, vtag_xyzw>
		{
			union {
				struct { T x; T y; T z; T w; };
				//std::array<T, 4> data;
				T data[4];
			};

			TVdata() = default;

			TVdata(T t1, T t2, T t3, T t4) :
				x(t1), y(t2), z(t3), w(t4)
			{
			}
		};

	}

	template<int N, typename T, typename Tcat = vtag>
	struct TVector : public details::TVdata<N, T, Tcat>
	{
		TVector() = default;

		using details::TVdata<N, T, Tcat>::TVdata;//forward brace initializer
		
		using details::TVdata<N, T, Tcat>::data;

		//TODO most likely drop it, no colapse to pointer, use inner data member
		//http://en.cppreference.com/w/cpp/language/cast_operator
		//operator const T*() const 
		//{ 
		//	return data.data();
		//}
		//operator T*()
		//{
		//	return data.data();
		//}

		T& operator[](size_t index)
		{
			//out of range check DEBUG
			assert(index < N && "INDEX OUT OF RANGE");
			return data[index];
		}

		const T& operator[](size_t index) const
		{
			//out of range check DEBUG
			assert(index < N && "INDEX OUT OF RANGE");
			return data[index];
		}
		
		T& operator()(size_t index)
		{
			//out of range check DEBUG
			assert(index < N && "INDEX OUT OF RANGE");
			return data[index];
		}

		const T& operator()(size_t index) const
		{
			//out of range check DEBUG
			assert(index < N && "INDEX OUT OF RANGE");
			return data[index];
		}

		T& at(size_t index)
		{
			assert(index < N && "INDEX OUT OF RANGE");
			
			if (index < N)
				throw std::out_of_range();
			
			return data[index];
		}

		const T& at(size_t index) const
		{
			assert(index < N && "INDEX OUT OF RANGE");

			if (index < N)
				throw std::out_of_range();

			return data[index];
		}

		constexpr size_t size() const
		{
			return N;
		}

		/*
		inline bool operator< (const TVector& lhs, const TVector& rhs)
		{
			for (size_t i = 0; i < N; i++)
			{
				if (lhs[i] > rhs[i])
					return false;
			}

			return true;
		}
		inline bool operator> (const TVector& lhs, const TVector& rhs) { return rhs < lhs; }
		inline bool operator<=(const TVector& lhs, const TVector& rhs) { return !(lhs > rhs); }
		inline bool operator>=(const TVector& lhs, const TVector& rhs) { return !(lhs < rhs); }
		*/

	};



	//SFINAE
	//http://eli.thegreenplace.net/2014/sfinae-and-enable_if/
	//http://en.cppreference.com/w/cpp/types/enable_if
	//forbiden for reals
	//inline bool operator==(const X& lhs, const X& rhs){ /* do actual comparison */ }
	//inline bool operator!=(const X& lhs, const X& rhs){ return !(lhs == rhs); }
	
	// WOW it worked gcc error : note:   template argument deduction/substitution failed:
	template<int N, typename T, typename Tcat>
	bool operator==(const TVector<N, T, Tcat>& lhs, const typename std::enable_if<std::is_integral<T>::value, TVector<N, T, Tcat> >::type& rhs)
	{
		for (size_t i = 0; i < N; i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}

		return true;
	}

	template<int N, typename T, typename Tcat>
	bool operator!=(const TVector<N, T, Tcat>& lhs, const TVector<N, T, Tcat>& rhs)
	{
		return !(lhs == rhs);
	}

	template<int N, typename T, typename Tcat>
	std::ostream& operator << (std::ostream &o, const TVector<N, T, Tcat> &v)
	{
		o << "vec(|";

		for (auto a : v.data)
			o << a << "|";

		o << ")";

		return o;
	}

	//TODO
	//template<int N, typename T, typename Tcat>
	//std::istream& operator>>(std::istream& is, const TVector<N,T,Tcat>& v)
	//{
	//	// read obj from stream
	//	if( /* T could not be constructed */ )
	//		is.setstate(std::ios::failbit);
	//	return is;
	//}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat> operator + (const TVector<N, T, Tcat> &lhs, const TVector<N, T, Tcat> &rhs)
	{
		TVector<N, T, Tcat> ret;

		for (int i = 0; i < N; i++)
		{
			ret.data[i] = lhs.data[i] + rhs.data[i];
		}

		return ret;
	}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat> operator - (const TVector<N, T, Tcat> &lhs, const TVector<N, T, Tcat> &rhs)
	{
		TVector<N, T, Tcat> ret;

		for (int i = 0; i < N; i++)
		{
			ret.data[i] = lhs.data[i] - rhs.data[i];
		}

		return ret;
	}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat>& operator*=(TVector<N, T, Tcat> &lhs, const T& rhs)
	{

		for (size_t i = 0; i < N; i++)
		{
			lhs[i] = lhs[i] * rhs;
		}

		return lhs;
	}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat> operator*(TVector<N, T, Tcat> lhs, const T& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat>& operator/=(TVector<N, T, Tcat> &lhs, const T& rhs)
	{
		assert(rhs!=0 && "DIV BY 0")

		for (size_t i = 0; i < N; i++)
		{
			lhs[i] = lhs[i] / rhs;
		}

		return lhs;
	}

	template<int N, typename T, typename Tcat>
	TVector<N, T, Tcat> operator/(TVector<N, T, Tcat> lhs, const T& rhs)
	{
		lhs /= rhs;
		return lhs;
	}


	template<int N, typename T, typename Tcat>
	T dot(const TVector<N, T, Tcat> &lhs, const TVector<N, T, Tcat> &rhs)
	{
		T ret{};

		for (int i = 0; i < N; i++)
		{
			ret += (lhs.data[i] * rhs.data[i]);
		}

		return ret;
	}

	
	template<typename T, typename Tcat>
	TVector<3, T, Tcat> cross(const TVector<3, T, Tcat> &lhs, const TVector<3, T, Tcat> &rhs)
	{
		//return{ lhs.y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x, 1.0 };
		return{ 
			lhs[1]*rhs[2] - lhs[2]*rhs[1], 
			lhs[2]*rhs[0] - lhs[0]*rhs[2], 
			lhs[0]*rhs[1] - lhs[1]*rhs[0] 
		};
	}
	
	//This is not really a 4D vector cross ( it assumes 4D as homogenious x,y,z,w)
	//http://math.stackexchange.com/questions/720813/do-four-dimensional-vectors-have-a-cross-product-property
	//http://math.stackexchange.com/questions/185991/is-the-vector-cross-product-only-defined-for-3d
	template<typename T, typename Tcat>
	TVector<4, T, Tcat> cross(const TVector<4, T, Tcat> &lhs, const TVector<4, T, Tcat> &rhs)
	{
		//return{ lhs.y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x, 1.0 };
		return { 
			lhs[1] * rhs[2] - lhs[2] * rhs[1], 
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0], 
			1.0 
		};
	}

	template<int N, typename T, typename Tcat>
	T magnitude(const TVector<N, T, Tcat> &vec)
	{
		return sqrt(dot(vec, vec));
	}

	template<int N, typename T, typename Tcat>
	void normalize(const TVector<N, T, Tcat> &vec)
	{
		T mag = magnitude(vec);
		assert(mag != 0.0);
		T fac = 1.0 / mag;
		vec *= fac;
	}


}
