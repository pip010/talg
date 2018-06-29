

#include "catch/catch.hpp"

#include <matrix.hpp>

#include <transform.hpp>

TEST_CASE( "Testing TMatrix<R,C,T>", "[matrix.hpp]" )
{

    using namespace talg;

	TMatrix<4, 4, double> mat4_I = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	TMatrix<4, 4, double> mat4_1to16 = {
		1.0,2.0,3.0,4.0,
		5.0,6.0,7.0,8.0,
		9.0,10.0,11.0,12.0,
		13.0,14.0,15.0,16.0
	};

    TMatrix<4, 4, double> mat4_1to16_x2 = {
        2.0,4.0,6.0,8.0,
        10.0,12.0,14.0,16.0,
        18.0,20.0,22.0,24.0,
        26.0,28.0,30.0,32.0
    };


	//TODO check for no-compile
	//auto aaaaaa = mat222 * mat222; // NO COMPILE :)

	//PrintTypeTraits< TMatrix<5,5,double> >();



	SECTION("Correct init & Check access")
	{
		std::array<std::array<double, 4>, 4> xxx = { {
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 }
			} };

		TMatrix<4, 4, double> mat1{};
		mat1.map[0][0] = 1.0;
		mat1.map[1][1] = 1.0;
		mat1.map[2][2] = 1.0;
		mat1(3, 3) = 1.0;
	}

    SECTION( "basic algebra ops" )
    {
		TVector<4, double, vtag_xyzw> vec4{ 1.1,2.2,3.3,4.4 };

		//PrintTypeTraits< TMatrix<5,5,double> >();

		auto vec44 = mat4_I * vec4;
		//std::cout << vec44<< std::endl;
		REQUIRE(vec4.x == Approx(vec4.x) );


		//auto mat44 = mat2 * mat4_I;
		//std::cout << mat44<< std::endl;

		TMatrix<5, 5, double> mat3{};
		auto mat55 = mat3 * mat3;
		//std::cout << mat55<< std::endl;

    }

    SECTION( "query ops" )
    {
        using namespace talg::query;

        TVector<4, double, vtag_xyzw> vec_row;
        TVector<4, double, vtag_xyzw> vec_col;

        SECTION( " query0 ")
        {
            TVector<4, double, vtag_xyzw> vec_row = mat4_I.query<vtag_xyzw>(0,{});
            TVector<4, double, vtag_xyzw> vec_col = mat4_I.query<vtag_xyzw>({},0);

            REQUIRE(vec_row.x == Approx(vec_col.x));
            REQUIRE(vec_row.y == Approx(vec_col.y));
            REQUIRE(vec_row.z == Approx(vec_col.z));
            REQUIRE(vec_row.w == Approx(vec_col.w));
        }

        SECTION( " query1 ")
        {
            TVector<4, double, vtag_xyzw> vec_row = mat4_I.query<vtag_xyzw>(1,{});
            TVector<4, double, vtag_xyzw> vec_col = mat4_I.query<vtag_xyzw>({},1);

            REQUIRE(vec_row.x == Approx(vec_col.x));
            REQUIRE(vec_row.y == Approx(vec_col.y));
            REQUIRE(vec_row.z == Approx(vec_col.z));
            REQUIRE(vec_row.w == Approx(vec_col.w));
        }

        SECTION( " query2 ")
        {
            TVector<4, double, vtag_xyzw> vec_row = mat4_I.query<vtag_xyzw>(2,{});
            TVector<4, double, vtag_xyzw> vec_col = mat4_I.query<vtag_xyzw>({},2);

            REQUIRE(vec_row.x == Approx(vec_col.x));
            REQUIRE(vec_row.y == Approx(vec_col.y));
            REQUIRE(vec_row.z == Approx(vec_col.z));
            REQUIRE(vec_row.w == Approx(vec_col.w));
        }

        SECTION( " query3 ")
        {
            TVector<4, double, vtag_xyzw> vec_row = mat4_I.query<vtag_xyzw>(3,{});
            TVector<4, double, vtag_xyzw> vec_col = mat4_I.query<vtag_xyzw>({},3);

            REQUIRE(vec_row.x == Approx(vec_col.x));
            REQUIRE(vec_row.y == Approx(vec_col.y));
            REQUIRE(vec_row.z == Approx(vec_col.z));
            REQUIRE(vec_row.w == Approx(vec_col.w));
        }

    }

    SECTION( "advanced algebra ops" )
    {
		//UGLYYYYY
		//but there is hope, see c++17
		//http://en.cppreference.com/w/cpp/language/aggregate_initialization
		TMatrix<4, 4, double> mat2({ {
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 },
			{ 1.1,2.2,3.3,4.4 }
			} });

		TMatrix<4, 4, double> mat22 = {
			1.1,2.2,3.3,4.4,
			5.1,6.2,7.3,8.4,
			9.1,10.2,11.3,12.4,
			13.1,14.15,16.3,1.0
		};


		TMatrix<2, 3, double> mat222 = {
			{ 1.1,2.2,3.3,
			1.1,2.2,3.3 }
		};

		auto tmat2 = transpose(mat2);
		auto det = determinant(mat22);
		auto imat2 = inverse(mat22);

    auto mat2_trace = trace(mat2);
    REQUIRE(mat2_trace == Approx(1.1+2.2+3.3+4.4));
	}


}//end TEST CASE
