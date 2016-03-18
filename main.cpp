



#include <iostream>
#include <cassert>

#include <vector.hpp>
#include <matrix.hpp>


using namespace std;

/*
ClassName ClassName::operator symbol(const ClassName& rhs) const
   {
   ClassName result = *this;     // Declare a temporary object to hold the result and
                                 // initialize it with the left operand

   // Perform arithmetic with result and rhs, storing result in result

   // Return the temporary result

   return result;
   }
*/



////////////////////////////////////////////////////////



#include <type_traits>
#include <typeinfo>

template<typename T>
void PrintTypeTraits(void)
{
	using namespace std;
	
	cout << endl;
	cout << "Type: " << typeid(T).name() << endl;
	cout << "Size: " << sizeof(T) << endl;
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

void test_func_print_c(const double* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}

	std::cout << std::endl;
}

void test_func_modify_c(double* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		array[i] = (double)i;
	}
}

int main()
{
	using namespace talg;

	TVector<3, long long, vtag_ijk> ijk1;
	TVector<3, long long, vtag_ijk> ijk2{1,2,3};

	
	TVector<3, double, vtag_xyz> vec3{ 1.1,2.2,3.3};

	TVector<3, double, vtag_xyz> vec3_0{};

	TVector<3, double, vtag_xyz> vec3_UND;

	TVector<4, double, vtag_xyzw> vec4{ 1.1,2.2,3.3,4.4 };

	TVector<4, double, vtag_xyzw> vec4_0{};
	
	TVector<4, double, vtag_xyzw> vec4_UND;
	
	vec4_UND = vec4;
	
	vec4 = vec4 + vec4;
	
	std::cout << vec4 << std::endl;
	
	vec4 *= 0.5;
	
	std::cout << vec4 << std::endl;

	
	
	

	//TVector<5, double> vec5_XXXX  { 1.1,2.2,3.3,4.4,5.5,6.6 }; // COMPILES :(
	
	TVector<5, double> vec5_XXXX{ 1.1,2.2,3.3,4.4,5.5 };

	std::cout << vec3.x << std::endl;
	
	std::cout << vec5_XXXX[0] << std::endl;
	
	const double& cdbl = vec5_XXXX[0]; 
	
	auto mag = magnitude(vec4);
	
	test_func_modify_c(vec5_XXXX, vec5_XXXX.size());

	test_func_print_c(vec5_XXXX, vec5_XXXX.size());
	
	PrintTypeTraits<TVector<3, double, vtag_xyz> >();
	
	
	//if(vec4 == vec4_UND) 
		// NOT COMPILE :) comparing non-integral is forbiden

	if (ijk1 == ijk2)
		std::cout << "Comparing integral types is fine..." << std::endl;

	TMatrix<4,4,double> mat1;


	//UGLYYYYY
	TMatrix<4, 4, double> mat2{ {{
		{1.1,2.2,3.3,4.4},
		{ 1.1,2.2,3.3,4.4 },
		{ 1.1,2.2,3.3,4.4 },
		{ 1.1,2.2,3.3,4.4 }
	}} };

	//std::array<std::array<double, 4>, 4> m{ {
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 }
	//} };

    return 0;
}


