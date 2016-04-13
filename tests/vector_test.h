#pragma once

#include <vector.hpp>

#include "helpers.h"


TEST_CASE( "Vector<N,T,Tag> Creation & Initialization", "[vector.hpp]" ) 
{
    
    using namespace talg;
    	    
    using Txyz = TVector<3, double, vtag_xyz>;
    using Txyzw = TVector<4, double, vtag_xyzw>;
    using Tijk = TVector<3, long long, vtag_ijk>;

	//4D vectors
	Txyzw xyzw_1234 { 1.1,2.2,3.3,4.4 };
	Txyzw xyzw_0 {};
	Txyzw xyzw_U;
	
	//3D vectors
	Txyz xyz_123 { 1.1,2.2,3.3 };
	Txyz xyz_0 {};
	Txyz xyz_U;
	
    Tijk ijk_123 { 1,2,3 };
    Tijk ijk_0 {};
    Tijk ijk_U;
    
    SECTION( "correct init & check access" ) 
    {
		
		//TVector<3, long long, vtag_ijk> ijk_U;
		//TVector<3, long long, vtag_ijk> ijk_0{};
		//TVector<3, long long, vtag_ijk> ijk_1{ 1,2,3 };
		REQUIRE(ijk_0.i == 0);
		REQUIRE(ijk_0.j == 0);
		REQUIRE(ijk_0.k == 0);
		REQUIRE(ijk_123.i == 1);
		REQUIRE(ijk_123.j == 2);
		REQUIRE(ijk_123.k == 3);
		CHECK(ijk_U.i == ijk_U.i);
		CHECK(ijk_U.j == ijk_U.j);
		CHECK(ijk_U.k == ijk_U.k);

		
		//TVector<3, double, vtag_xyz> xyz_U;
		//TVector<3, double, vtag_xyz> xyz_0{};
		//TVector<3, double, vtag_xyz> xyz_1{ 1.1,2.2,3.3 };
		REQUIRE(xyz_0.x == Approx(0));
		REQUIRE(xyz_0.y == Approx(0));
		REQUIRE(xyz_0.z == Approx(0));
		REQUIRE(xyz_123.x == Approx(1.1));
		REQUIRE(xyz_123.y == Approx(2.2));
		REQUIRE(xyz_123.z == Approx(3.3));
		CHECK(xyz_U.x == xyz_U.x);
		CHECK(xyz_U.y == xyz_U.y);
		CHECK(xyz_U.z == xyz_U.z);
		
		//TVector<4, double, vtag_xyzw> xyzw_U;
		//TVector<4, double, vtag_xyzw> xyzw_0{};
		//TVector<4, double, vtag_xyzw> xyzw_1{ 1.1,2.2,3.3,4.4 };
		REQUIRE(xyzw_0.x == Approx(0));
		REQUIRE(xyzw_0.y == Approx(0));
		REQUIRE(xyzw_0.z == Approx(0));
		REQUIRE(xyzw_0.w == Approx(0));
		
		REQUIRE(xyzw_1234.x == Approx(1.1));
		REQUIRE(xyzw_1234.y == Approx(2.2));
		REQUIRE(xyzw_1234.z == Approx(3.3));
		REQUIRE(xyzw_1234.w == Approx(4.4));
		
		CHECK(xyzw_U.x == xyzw_U.x);
		CHECK(xyzw_U.y == xyzw_U.y);
		CHECK(xyzw_U.z == xyzw_U.z);
		CHECK(xyzw_U.w == xyzw_U.w);
		
		CHECK(xyzw_U[0] == xyzw_U(0));
		CHECK(xyzw_U[1] == xyzw_U(1));
		CHECK(xyzw_U[2] == xyzw_U(2));
		CHECK(xyzw_U[3] == xyzw_U(3));

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
		
		CHECK(vec5_U[0] == vec5_U(0));
		CHECK(vec5_U[1] == vec5_U(1));
		CHECK(vec5_U[2] == vec5_U(2));
		CHECK(vec5_U[3] == vec5_U(3));
		CHECK(vec5_U[4] == vec5_U(4));
		


		
		//TVector<5, double> vec5_XXXX  { 1.1,2.2,3.3,4.4,5.5,6.6 }; // COMPILES :( runtime-err :(

		//if(vec4 == vec4_UND) // NOT COMPILE :) comparing non-integral is forbiden

		//PrintTypeTraits<TVector<5, double> >();
		
    }
    
    SECTION( "basic algebra ops" )
    {
		Txyzw xyzw_1234_x2 { 2.2,4.4,6.6,8.8 };
		
		SECTION( "test op+" )
		{
			auto vec4_2468 = xyzw_1234 + xyzw_1234;
			
			REQUIRE(eq(vec4_2468,xyzw_1234_x2));
		}
		
		SECTION( "test op*=" )
		{					
			xyzw_1234 *= 2.0;
			
			REQUIRE(eq(xyzw_1234,xyzw_1234_x2));
		}
		
		
		

		

		
	}

	SECTION( "advanced algebra ops" )
	{
		auto mag = magnitude(xyzw_1234);
		auto cvec = cross(xyzw_1234, xyzw_1234);
	}
	
	SECTION( "legacy C API" )
	{
		//test_func_modify_c(vec5_XXXX.data, vec5_XXXX.size());

		//test_func_print_c(vec5_XXXX.data, vec5_XXXX.size());
	}
}


