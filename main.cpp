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
	
	size_t size() const
	{
		return Tdata<N,T,Tcat>::data.size();
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

void test_func_print_c(double* array, size_t size)
{
	for(size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}
	
	std::cout << std::endl;
}

#include <type_traits>
#include <typeinfo>

template<typename T>
void PrintTypeTraits(void)
{
	using namespace std;
	
	cout << endl;
	cout << "Type: " << typeid(T).name() << endl;
	cout << endl;
	cout << "Type properties:" << endl;
	cout << "is_abstract: " << is_abstract<T>::value << endl;
	cout << "is_const: " << is_const<T>::value << endl;
	cout << "is_empty: " << is_empty<T>::value << endl;
	cout << "is_literal_type: " << is_literal_type<T>::value << endl;
	cout << "is_pod: " << is_pod<T>::value << endl;
	cout << "is_polymorphic: " << is_polymorphic<T>::value << endl;
	cout << "is_signed: " << is_signed<T>::value << endl;
	cout << "is_standard_layout: " << is_standard_layout<T>::value << endl;
	cout << "is_trivial: " << is_trivial<T>::value << endl;
	//cout << "is_trivially_copyable: " << is_trivially_copyable<T>::value << endl;
	cout << "is_unsigned: " << is_unsigned<T>::value << endl;
	cout << "is_volatile: " << is_volatile<T>::value << endl;
	cout << endl;
	cout << "Type features:" << endl;
	cout << "has_virtual_destructor: " << has_virtual_destructor<T>::value << endl;
	//cout << "is_assignable: " << is_assignable<T>::value << endl;
	cout << "is_constructible: " << is_constructible<T>::value << endl;
	cout << "is_copy_assignable: " << is_copy_assignable<T>::value << endl;
	cout << "is_copy_constructible: " << is_copy_constructible<T>::value << endl;
	cout << "is_destructible: " << is_destructible<T>::value << endl;
	cout << "is_default_constructible: " << is_default_constructible<T>::value << endl;
	cout << "is_move_assignable: " << is_move_assignable<T>::value << endl;
	cout << "is_move_constructible: " << is_move_constructible<T>::value << endl;
	
	/*
	cout << "is_trivially_assignable: " << is_trivially_assignable<T>::value << endl;
	cout << "is_trivially_constructible: " << is_trivially_constructible<T>::value << endl;
	cout << "is_trivially_copy_assignable: " << is_trivially_copy_assignable<T>::value << endl;
	cout << "is_trivially_copy_constructible: " << is_trivially_copy_constructible<T>::value << endl;
	cout << "is_trivially_destructible: " << is_trivially_destructible<T>::value << endl;
	cout << "is_trivially_default_constructible: " << is_trivially_default_constructible<T>::value << endl;
	cout << "is_trivially_move_assignable: " << is_trivially_move_assignable<T>::value << endl;
	cout << "is_trivially_move_constructible: " << is_trivially_move_constructible<T>::value << endl;
	*/
	
	/*
	cout << "is_nothrow_assignable: " << is_nothrow_assignable<T>::value << endl;
	cout << "is_nothrow_constructible: " << is_nothrow_constructible<T>::value << endl;
	cout << "is_nothrow_copy_assignable: " << is_nothrow_copy_assignable<T>::value << endl;
	cout << "is_nothrow_copy_constructible: " << is_nothrow_copy_constructible<T>::value << endl;
	cout << "is_nothrow_destructible: " << is_nothrow_destructible<T>::value << endl;
	cout << "is_nothrow_default_constructible: " << is_nothrow_default_constructible<T>::value << endl;
	cout << "is_nothrow_move_assignable: " << is_nothrow_move_assignable<T>::value << endl;
	cout << "is_nothrow_move_assignable: " << is_nothrow_move_assignable<T>::value << endl;
	cout << "is_nothrow_move_constructible: " << is_nothrow_move_constructible<T>::value << endl;
	*/



}

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
	
	test_func_print_c(vec5_XXXX.data.begin(), vec5_XXXX.size());
	
	PrintTypeTraits<TVector<3, double, vtag_xyz> >();

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
