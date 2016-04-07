#pragma once

#include <vector.hpp>

#include "helpers.h"


TEST_CASE( "Vector<N,T,Tag> Creation & Initialization", "[vector.hpp]" ) 
{
    
    using namespace talg;
    
	TVector<4, double, vtag_xyzw> vec4_1234{ 1.1,2.2,3.3,4.4 };
    

    
    SECTION( "check init correct" ) 
    {
		//Hint: U stands fo undefined below

		TVector<3, long long, vtag_ijk> ijk_U;
		TVector<3, long long, vtag_ijk> ijk_0{};
		TVector<3, long long, vtag_ijk> ijk_1{ 1,2,3 };
		REQUIRE(ijk_0.i == 0);
		REQUIRE(ijk_0.j == 0);
		REQUIRE(ijk_0.k == 0);
		REQUIRE(ijk_1.i == 1);
		REQUIRE(ijk_1.j == 2);
		REQUIRE(ijk_1.k == 3);
		//CHECK(ijk_U.i == ijk_U.j);
		//CHECK(ijk_U.j == ijk_U.k);

		
		TVector<3, double, vtag_xyz> xyz_U;
		TVector<3, double, vtag_xyz> xyz_0{};
		TVector<3, double, vtag_xyz> xyz_1{ 1.1,2.2,3.3 };
		REQUIRE(xyz_0.x == Approx(0));
		REQUIRE(xyz_0.y == Approx(0));
		REQUIRE(xyz_0.z == Approx(0));
		REQUIRE(xyz_1.x == Approx(1.1));
		REQUIRE(xyz_1.y == Approx(2.2));
		REQUIRE(xyz_1.z == Approx(3.3));
		//CHECK(xyz_U.x == Approx(xyz_U.y));
		//CHECK(xyz_U.y == Approx(xyz_U.z));
		
		
		TVector<4, double, vtag_xyzw> xyzw_U;
		TVector<4, double, vtag_xyzw> xyzw_0{};
		TVector<4, double, vtag_xyzw> xyzw_1{ 1.1,2.2,3.3,4.4 };
		REQUIRE(xyzw_0.x == Approx(0));
		REQUIRE(xyzw_0.y == Approx(0));
		REQUIRE(xyzw_0.z == Approx(0));
		REQUIRE(xyzw_0.w == Approx(0));
		REQUIRE(xyzw_1.x == Approx(1.1));
		REQUIRE(xyzw_1.y == Approx(2.2));
		REQUIRE(xyzw_1.z == Approx(3.3));
		REQUIRE(xyzw_1.w == Approx(4.4));
		//CHECK(xyzw_U.x == Approx(xyzw_U.y));
		//CHECK(xyzw_U.y == Approx(xyzw_U.z));
		//CHECK(xyzw_U.z == Approx(xyzw_U.w));
		

		TVector<5, double> vec5_U;
		TVector<5, double> vec5_0{};
		TVector<5, double> vec5_1{ 1.1,2.2,3.3,4.4,5.5 };
		REQUIRE(vec5_0[0] == Approx(0));
		REQUIRE(vec5_0[1] == Approx(0));
		REQUIRE(vec5_0[2] == Approx(0));
		REQUIRE(vec5_0[3] == Approx(0));
		REQUIRE(vec5_0[4] == Approx(0));
		REQUIRE(vec5_1[0] == Approx(1.1));
		REQUIRE(vec5_1[1] == Approx(2.2));
		REQUIRE(vec5_1[2] == Approx(3.3));
		REQUIRE(vec5_1[3] == Approx(4.4));
		REQUIRE(vec5_1[4] == Approx(5.5));
		//CHECK(vec5_U[0] == Approx(vec5_U[1]));
		//CHECK(vec5_U[1] == Approx(vec5_U[2]));
		//CHECK(vec5_U[2] == Approx(vec5_U[3]));
		//CHECK(vec5_U[3] == Approx(vec5_U[4]));


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

		//PrintTypeTraits<TVector<5, double> >();
		
    }
    
    SECTION( "basic algebra ops" )
    {
		auto vec4_2468 = vec4_1234 + vec4_1234;

		vec4_2468 *= 2.0;

		REQUIRE(vec4_2468.x == Approx(4.4));
	}

	SECTION( "linear algebra ops" )
	{
		auto cvec = cross(vec4_1234, vec4_1234);
	}
}


