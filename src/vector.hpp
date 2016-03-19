#pragma once

#include <initializer_list>


#include <array>

#include <iostream>

#include <cassert>

#include <cmath>

namespace talg
{
	/*
	typedef TVector<4, xyzw, double> Vec4d;
	typedef TVector<4, xyzw, float> Vec4f;

	typedef TVector<3, xyz, double> Vec3d;
	typedef TVector<3, xyz, float> Vec3f;

	typedef TVector<3, ijk, long long> Vec3l;//http://stackoverflow.com/questions/384502/what-is-the-bit-size-of-long-on-64-bit-windows

	typedef TVector<2, xy, double> Vec2d;
	typedef TVector<2, xy, float> Vec2f;

	typedef TVector<3, rgb, double> Color3d;
	typedef TVector<3, rgb, float> Color3f;
	//typedef TVector<3, rgb> Color3;

	typedef TVector<4, rgba, double> Color4d;
	typedef TVector<4, rgba, float> Color4f;

	static const Color3d RED = {1.0, 0.0, 0.0};
	static const Color3d GREEN = { 0.0, 1.0, 0.0 };
	static const Color3d BLUE = { 0.0, 0.0, 1.0 };
	*/

	class vtag {};
	class vtag_xyz {};
	class vtag_xyzw {};
	class vtag_ijk {};

	template<int N, typename T, typename Tcat>
	struct Tdata
	{
		std::array<T, N> data;
		//T data[N];

		Tdata() = default;

		//http://stackoverflow.com/questions/28866559/writing-variadic-template-constructor
		//template<struct Ts...>
		//Tdata(Ts&&... args) : Tdata( args... ) {}

		Tdata(const std::initializer_list<T>&& il)
		{
			std::copy(il.begin(), il.end(), data.begin());
		}
	};

	template<typename T>
	struct Tdata<3, T, vtag_ijk>
	{
		union {
			struct { T i; T j; T k; };
			std::array<T, 3> data;
		};

		Tdata() = default;

		Tdata(T t1, T t2, T t3) : 
			i(t1), j(t2), k(t3)
		{}
	};

	template<typename T>
	struct Tdata<3, T, vtag_xyz>
	{
		union {
			struct { T x; T y; T z; };
			std::array<T, 3> data;
			//T data[N];
		};

		Tdata() = default;

		Tdata(T t1, T t2, T t3) : 
			x(t1), y(t2), z(t3)
		{}
	};

	template<typename T>
	struct Tdata<4, T, vtag_xyzw>
	{
		union {
			struct { T x; T y; T z; T w; };
			std::array<T, 4> data;
		};

		Tdata() = default;

		Tdata(T t1, T t2, T t3, T t4) : x(t1), y(t2), z(t3), w(t4)
		{
		}
	};

	template<int N, typename T, typename Tcat = vtag>
	struct TVector : public Tdata<N, T, Tcat>
	{
		TVector() = default;

		using Tdata<N, T, Tcat>::Tdata;//forward brace initializer
		
		using Tdata<N, T, Tcat>::data;

		//http://en.cppreference.com/w/cpp/language/cast_operator

		operator const T*() const 
		{ 
			return data.data();
		}

		operator T*()
		{
			return data.data();
		}

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

		size_t size() const
		{
			return data.size();
		}


	};

	///////////////////////////////////////////////////////

	// http://en.cppreference.com/w/cpp/language/operators

	//inline bool operator< (const X& lhs, const X& rhs){ /* do actual comparison */ }
	//inline bool operator> (const X& lhs, const X& rhs){ return rhs < lhs; }
	//inline bool operator<=(const X& lhs, const X& rhs){ return !(lhs > rhs); }
	//inline bool operator>=(const X& lhs, const X& rhs){ return !(lhs < rhs); }

	//SFINAE
	//http://eli.thegreenplace.net/2014/sfinae-and-enable_if/
	//http://en.cppreference.com/w/cpp/types/enable_if
	//forbiden for reals
	//inline bool operator==(const X& lhs, const X& rhs){ /* do actual comparison */ }
	//inline bool operator!=(const X& lhs, const X& rhs){ return !(lhs == rhs); }
	
	// WOW it worked gcc error : note:   template argument deduction/substitution failed:
	template<int N, typename T, typename Tcat>
	bool operator==(const T& lhs, const typename std::enable_if<std::is_integral<T>::value, T>::type& rhs)
	{
		for (size_t i = 0; i < N; i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}

		return true;
	}

	template<int N, typename T, typename Tcat>
	bool operator!=(const T& lhs, const typename std::enable_if<std::is_integral<T>::value, T>::type& rhs)
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

		for (int i = 0; i < N; i++)
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

	/*
			template <int D, Tag Tag, typename T>
			TVector<D, Tag, T> operator * (const TVector<D, Tag, T> &lhs, const TVector<D, Tag, T> &rhs)
			{
				throw "Not Implemented";
				//http://www.answers.com/Q/Will_a_vector_multiplied_by_another_vector_result_in_another_vector
			}

			template <int D, Tag Tag, typename T>
			TVector<D, Tag, T> operator / (const TVector<D, Tag, T> &lhs, const TVector<D, Tag, T> &rhs)
			{
				throw "Not Implemented";
				//http://math.stackexchange.com/questions/246594/what-is-vector-division
			}
	*/

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

	template<int N, typename T, typename Tcat>
	T magnitude(const TVector<N, T, Tcat> &vec)
	{
		return sqrt(dot(vec, vec));
	}
}
