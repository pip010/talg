#include "catch/catch.hpp"

#include <transform.hpp>

#include "helpers.h"

using namespace talg;

TEST_CASE("Testing Transform<T> ", "[transform.hpp]")
{
	typedef Transform<double> HomoTransformDouble;

	typedef TMatrix<4, 4, double> Matrix44Double;

	SECTION(" Correct init & Check access ")
	{
		HomoTransformDouble t;		
		Matrix44Double m;
		m = t;

		REQUIRE( t(3, 3) == m(3, 3) );
		REQUIRE( t(3,3) == Approx(1.0) );

		HomoTransformDouble t2{ m };
		Matrix44Double m2{ t2 };

		REQUIRE( m2[3][3] == t2[3][3] );
		REQUIRE( m2[3][3] == Approx(1.0) );
	}

	SECTION(" Static helper functions ")
	{
		HomoTransformDouble::value_type angle = 0.5;

		auto rotmatx = HomoTransformDouble::RotationMatrixX(angle);
		auto rotmaty = HomoTransformDouble::RotationMatrixY(angle);
		auto rotmatz = HomoTransformDouble::RotationMatrixZ(angle);

		auto rotmatxx = HomoTransformDouble::RotationMatrix(0,angle);
		auto rotmatyy = HomoTransformDouble::RotationMatrix(1,angle);
		auto rotmatzz = HomoTransformDouble::RotationMatrix(2,angle);

		REQUIRE(rotmatx(1, 1) == rotmatxx(1, 1));
		REQUIRE(rotmaty(0, 0) == rotmatyy(0, 0));
		REQUIRE(rotmaty(0, 0) == rotmatyy(0, 0));
	}

	SECTION(" Chaining functions ")
	{
		HomoTransformDouble t;
		t.Translate(100.0, 0.0, 0.0)
			.Scale(1000.0)
			.RotateZ(3.14 / 2.0);

		Matrix44Double mI(Matrix44Double::IDENTITY());

		Matrix44Double mT{
			1, 0, 0, 100,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		Matrix44Double mS{
			1000, 0, 0, 0,
			0, 1000, 0, 0,
			0, 0, 1000, 0,
			0, 0, 0, 1
		};

		Matrix44Double mR = HomoTransformDouble::RotationMatrixZ(3.14 / 2.0);

		// this should be equivalent to the chain operation of a homo-transform
		Matrix44Double m = mI * mT * mS * mR;

		REQUIRE(eq(m, t));
	}
}