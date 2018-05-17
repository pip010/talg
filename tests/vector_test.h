#pragma once

#include <vector.hpp>

#include "helpers.h"


TEST_CASE("Testing Vector<N,T,Tag> ", "[vector.hpp]")
{

	using namespace talg;

	using Txyz = TVector<3, double, vtag_xyz>;
	using Txyzw = TVector<4, double, vtag_xyzw>;
	using Tijk = TVector<3, long long, vtag_ijk>;

	//4D vectors
	Txyzw xyzw_1234{ 1, 2, 3, 4 };
	Txyzw xyzw_0{};
	Txyzw xyzw_U;

	//3D vectors
	Txyz xyz_123{ 1, 2, 3 };
	Txyz xyz_0{};
	Txyz xyz_U;

	Tijk ijk_123{ 1, 2, 3 };
	Tijk ijk_0{};
	Tijk ijk_U;

	SECTION("Correct init & Check access")
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
		REQUIRE(xyz_123.x == Approx(1));
		REQUIRE(xyz_123.y == Approx(2));
		REQUIRE(xyz_123.z == Approx(3));
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

		REQUIRE(xyzw_1234.x == Approx(1));
		REQUIRE(xyzw_1234.y == Approx(2));
		REQUIRE(xyzw_1234.z == Approx(3));
		REQUIRE(xyzw_1234.w == Approx(4));

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
		TVector<5, double> vec5_1{ 1,2,3,4,5 };

		//REQUIRE(vec5_0[0] == Approx(0));
		//REQUIRE(vec5_0[1] == Approx(0));
		//REQUIRE(vec5_0[2] == Approx(0));
		//REQUIRE(vec5_0[3] == Approx(0));
		//REQUIRE(vec5_0[4] == Approx(0));
		REQUIRE(vec5_1[0] == Approx(1));
		REQUIRE(vec5_1[1] == Approx(2));
		REQUIRE(vec5_1[2] == Approx(3));
		REQUIRE(vec5_1[3] == Approx(4));
		REQUIRE(vec5_1[4] == Approx(5));

		//although UB this should hold
		CHECK(vec5_U[0] == vec5_U(0));
		CHECK(vec5_U[1] == vec5_U(1));
		CHECK(vec5_U[2] == vec5_U(2));
		CHECK(vec5_U[3] == vec5_U(3));
		CHECK(vec5_U[4] == vec5_U(4));


		size_t i=0;
		for(auto& a : xyzw_1234)
		{
			CHECK(a == Approx(++i));
		}


		//TVector<5, double> vec5_XXXX  { 1.1,2.2,3.3,4.4,5.5,6.6 }; // COMPILES :( runtime-err :(

		//if(vec4 == vec4_UND) // NOT COMPILE :) comparing non-integral is forbiden

		//PrintTypeTraits<TVector<5, double> >();

	}

	SECTION("Basic algebra ops:")
	{
		Txyzw xyzw_1234_x2{ 2.2, 4.4, 6.6, 8.8 };
		Txyz xyz_123_x2{ 2.2, 4.4, 6.6, };
		Tijk ijk_123_x2{ 2, 4, 6 };

		Txyzw xyzw_2345{ 2.1, 3.2, 4.3, 5.4 };
		Txyz xyz_234{ 2.1, 3.2, 4.3 };
		Tijk ijk_234{ 2, 3, 4 };

		SECTION("op (vector + vector)")
		{
			auto vec4_2468 = xyzw_1234 + xyzw_1234;
			REQUIRE(eq(vec4_2468, xyzw_1234_x2));

			auto vec3_246 = xyz_123 + xyz_123;
			REQUIRE(eq(vec3_246, xyz_123_x2));

			auto vec3i_246 = ijk_123 + ijk_123;
			REQUIRE(vec3i_246 == ijk_123_x2);
			REQUIRE(ijk_0 == ijk_0 + ijk_0);
		}

		SECTION("op (vector += vector)")
		{
			xyzw_1234 += xyzw_1234;
			REQUIRE(eq(xyzw_1234, xyzw_1234_x2));

			xyz_123 += xyz_123;
			REQUIRE(eq(xyz_123, xyz_123_x2));

			ijk_123 += ijk_123;
			REQUIRE(ijk_123 == ijk_123_x2);
			ijk_0 += ijk_0;
			REQUIRE(ijk_0 == ijk_0);
		}

		SECTION("op (vector - vector)")
		{
			auto vec4_1234= xyzw_1234_x2 - xyzw_1234;
			REQUIRE(eq(vec4_1234, xyzw_1234));

			auto vec3_123 = xyz_123_x2 - xyz_123;
			REQUIRE(eq(vec3_123, xyz_123));

			auto vec3i_123 = ijk_123_x2 - ijk_123;
			REQUIRE(vec3i_123 == ijk_123);
			REQUIRE(ijk_0 == ijk_0 - ijk_0);
		}

		SECTION("op (vector -= vector)")
		{
			xyzw_1234_x2 -= xyzw_1234;
			REQUIRE(eq(xyzw_1234, xyzw_1234_x2));

			xyz_123_x2 -= xyz_123;
			REQUIRE(eq(xyz_123, xyz_123_x2));

			ijk_123_x2 -= ijk_123;
			REQUIRE(ijk_123 == ijk_123_x2);

			ijk_0 -= ijk_0;
			REQUIRE(ijk_0 == ijk_0);
		}

		SECTION("op (vector * scalar)")
		{
			auto vec4_2468 = xyzw_1234 * 2.0;
			REQUIRE(eq(vec4_2468, xyzw_1234_x2));

			auto vec3_246 = xyz_123 * 2.0;
			REQUIRE(eq(vec3_246, xyz_123_x2));

			auto vec3i_246 = ijk_123 * 2LL;
			REQUIRE(vec3i_246 == ijk_123_x2);
			REQUIRE(ijk_0 == ijk_0 * 2LL);
		}

		SECTION("op (vector *= scalar)")
		{
			xyzw_1234 *= 2.0;
			REQUIRE(eq(xyzw_1234, xyzw_1234_x2));

			xyz_123 *= 2.0;
			REQUIRE(eq(xyz_123, xyz_123_x2));

			ijk_123 *= 2LL;
			REQUIRE(ijk_123 == ijk_123_x2);
		}

		SECTION("op (vector / scalar)")
		{
			auto vec4_1234 = xyzw_1234_x2 / 2.0;
			REQUIRE(eq(vec4_1234, xyzw_1234));

			auto vec3_123 = xyz_123_x2 / 2.0;
			REQUIRE(eq(vec3_123, xyz_123));

			auto vec3i_123 = ijk_123_x2 / 2LL;
			REQUIRE(vec3i_123 == ijk_123);
			REQUIRE(ijk_0 == ijk_0 / 2LL);
		}

		SECTION("op (vector /= scalar)")
		{
			xyzw_1234_x2 /= 2.0;
			REQUIRE(eq(xyzw_1234, xyzw_1234_x2));

			xyz_123_x2 /= 2.0;
			REQUIRE(eq(xyz_123, xyz_123_x2));

			ijk_123_x2 /= 2LL;
			REQUIRE(ijk_123 == ijk_123_x2);
		}

		SECTION("op (vector + scalar)")
		{
			auto vec4_2345 = xyzw_1234 + 1.0;
			REQUIRE(eq(vec4_2345, xyzw_2345));

			auto vec3_234 = xyz_123 + 1.0;
			REQUIRE(eq(vec3_234, xyz_234));

			auto vec3i_234 = ijk_123 + 1LL;
			REQUIRE(vec3i_234 == ijk_234);
			REQUIRE(ijk_0 == ijk_0 + 0LL);
		}

		SECTION("op (vector += scalar)")
		{
			xyzw_1234 += 1.0;
			REQUIRE(eq(xyzw_1234, xyzw_2345));

			xyz_123 += 1.0;
			REQUIRE(eq(xyz_123, xyz_234));

			ijk_123 += 1LL;
			REQUIRE(ijk_123 == ijk_234);

			ijk_0 += 0LL;
			REQUIRE(ijk_0 == ijk_0);
		}

		SECTION("op (vector - scalar)")
		{
			auto vec4_1234 = xyzw_2345 - 1.0;
			REQUIRE(eq(vec4_1234, xyzw_1234));

			auto vec3_123 = xyz_234 - 1.0;
			REQUIRE(eq(vec3_123, xyz_123));

			auto vec3i_123 = ijk_234 - 1LL;
			REQUIRE(vec3i_123 == ijk_123);
			REQUIRE(ijk_0 == ijk_0 - 0LL);
		}

		SECTION("op (vector -= scalar)")
		{
			xyzw_2345 -= 1.0;
			REQUIRE(eq(xyzw_1234, xyzw_2345));

			xyz_234 -= 1.0;
			REQUIRE(eq(xyz_123, xyz_234));

			ijk_234 -= 1LL;
			REQUIRE(ijk_123 == ijk_234);

			ijk_0 -= 0LL;
			REQUIRE(ijk_0 == ijk_0);
		}




	}

	SECTION("advanced algebra ops")
	{
		auto mag = magnitude(xyzw_1234);
		auto cvec = cross(xyzw_1234, xyzw_1234);
	}

	SECTION("legacy C API")
	{
		//test_func_modify_c(vec5_XXXX.data, vec5_XXXX.size());

		//test_func_print_c(vec5_XXXX.data, vec5_XXXX.size());
	}
}
