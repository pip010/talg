//http://stackoverflow.com/questions/5549524/how-do-i-initialize-a-member-array-with-an-initializer-list
#include <initializer_list>
//http://www.informit.com/articles/article.aspx?p=1852519

#include <array>

#include <iostream>

#include <cassert>

#include <cmath>

using namespace std;

class vtag{};
class vtag_xyz{};
class vtag_xyzw{};

template<int N, typename T, typename Tcat>
struct Tdata
{
	
	std::array<T, N> data;
	//T data[N];

	Tdata() = default;
	
	//http://stackoverflow.com/questions/28866559/writing-variadic-template-constructor
	
	//template<struct Ts...>
	//Tdata(Ts&&... args) : Tdata( args... ) {}
	
	Tdata(const initializer_list<T>&& il)
	{
		std::copy(il.begin(), il.end(), data.begin());
	}
};

template<typename T>
struct Tdata<3,T,vtag_xyz>
{
	union {
		struct { T x; T y; T z; };

		std::array<T, 3> data;
		//T data[N];
	};

	Tdata() = default;

	Tdata(T t1, T t2, T t3) : x(t1), y(t2), z(t3)
	{
	}
};

template<typename T>
struct Tdata<4,T,vtag_xyzw>
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
struct TVector : public Tdata<N,T,Tcat>
{
	TVector() = default;

	using Tdata<N,T,Tcat>::Tdata;
	
	
	T& operator[](int index)
	{
	//out of range check DEBUG
	assert(index < N && "INDEX OUT OF RANGE");

	return Tdata<N,T,Tcat>::data[index];
	}
	
	const T& operator[](int index) const
	{
	//out of range check DEBUG
	assert(index < N && "INDEX OUT OF RANGE");

	return Tdata<N,T,Tcat>::data[index];
	}
};

///////////////////////////////////////////////////////

		template<int N, typename T, typename Tcat>
		TVector<N,T,Tcat> operator + (const TVector<N,T,Tcat> &lhs, const TVector<N,T,Tcat> &rhs)
		{
			TVector<N,T,Tcat> ret;

			for (int i = 0; i < N; i++)
			{
				ret.data[i] = lhs.data[i] + rhs.data[i];
			}

			return ret;
		}

		template<int N, typename T, typename Tcat>
		TVector<N,T,Tcat> operator - (const TVector<N,T,Tcat> &lhs, const TVector<N,T,Tcat> &rhs)
		{
			TVector<N,T,Tcat> ret;

			for (int i = 0; i < N; i++)
			{
				ret.data[i] = lhs.data[i] - rhs.data[i];
			}

			return ret;
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
		T dot (const TVector<N,T,Tcat> &lhs, const TVector<N,T,Tcat> &rhs)
		{
			T ret(0);

			for (int i = 0; i < N; i++)
			{
				ret += ( lhs.data[i] * rhs.data[i] );
			}

			return ret;
		}

		template<int N, typename T, typename Tcat>
		T magnitude(const TVector<N,T,Tcat> &vec)
		{
			return sqrt(dot(vec,vec));
		}

////////////////////////////////////////////////////////

int main()
{
	TVector<3, double, vtag_xyz> vec3{ 1.1,2.2,3.3};

	TVector<3, double, vtag_xyz> vec3_0{};

	TVector<3, double, vtag_xyz> vec3_UND;

	TVector<4, double> vec4{ 1.1,2.2,3.3,4.4 };

	TVector<4, double> vec4_0{};

	TVector<4, double> vec4_UND;

	TVector<5, double> vec5_XXXX  { 1.1,2.2,3.3,4.4,5.5,6.6 }; // COMPILES :(
	
	std::cout << vec3.x << std::endl;
	
	std::cout << vec5_XXXX[0] << std::endl;
	
	const double& cdbl = vec5_XXXX[0]; 
	
	auto mag = magnitude(vec4);

    return 0;
}

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
