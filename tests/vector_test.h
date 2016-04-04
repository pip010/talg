#pragma once

#include <vector.hpp>

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

TEST_CASE( "Vector<N,T,Tag> Creation & Initialization", "[vector.hpp]" ) 
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
	
	/*
	//TVector<5, double> vec5_XXXX  { 1.1,2.2,3.3,4.4,5.5,6.6 }; // COMPILES :( runtime-err :(
	
	TVector<5, double> vec5_XXXX{ 1.1,2.2,3.3,4.4,5.5 };

	std::cout << vec3.x << std::endl;
	
	std::cout << vec5_XXXX[0] << std::endl;
	
	const double& cdbl = vec5_XXXX[0]; 
	
	auto mag = magnitude(vec4);
	
	test_func_modify_c(vec5_XXXX.data, vec5_XXXX.size());

	test_func_print_c(vec5_XXXX.data, vec5_XXXX.size());
	
	PrintTypeTraits<TVector<3, double, vtag_xyz> >();
	//PrintTypeTraits<TVector<3, long long, vtag_ijk> >();
	
	//if(vec4 == vec4_UND) 
		// NOT COMPILE :) comparing non-integral is forbiden
	if (ijk1 == ijk2)
		std::cout << "Comparing integral types is fine..." << std::endl;
	*/
    
    
    SECTION( "check init correct" ) 
    {
		vec4_UND = vec4;
	
		vec4 = vec4 + vec4;
	
		//std::cout << vec4 << std::endl;
	
		vec4 *= 2.0;
	
		//std::cout << vec4 << std::endl;
		
		REQUIRE(vec4.x == Approx(4.4) );
		
    }
    
    SECTION( "basic algebra ops" )
    {
	}
}


