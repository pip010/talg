#include "catch/catch.hpp"

#include <quaternion.hpp>



TEST_CASE("Testing TQuaternion<N>", "[quaternion.hpp]")
{
  using namespace talg;

  using TQuat = TQuaternion<double>;

  TQuat quat_1234{ 1, 2, 3, 4 };
  TQuat quat_1111{ 1, 1, 1, 1 };
  TQuat quat_0{};
  TQuat quat_UB;


  SECTION("Correct init & Check access")
  {
    REQUIRE(quat_1234[0] == Approx(1.0));
    REQUIRE(quat_1234[1] == Approx(2.0));
    REQUIRE(quat_1234[2] == Approx(3.0));
    REQUIRE(quat_1234[3] == Approx(4.0));

    REQUIRE(quat_1234(0) == Approx(1.0));
    REQUIRE(quat_1234(1) == Approx(2.0));
    REQUIRE(quat_1234(2) == Approx(3.0));
    REQUIRE(quat_1234(3) == Approx(4.0));

    REQUIRE(quat_1234.x == Approx(1.0));
    REQUIRE(quat_1234.y == Approx(2.0));
    REQUIRE(quat_1234.z == Approx(3.0));
    REQUIRE(quat_1234.w == Approx(4.0));

    size_t i=0;
		for(const auto& a : quat_1234)
		{
			CHECK(a == Approx(++i));
		}

    REQUIRE( quat_1234.size() == 4 );

  }

  SECTION("Basic algebra ops")
  {
    auto quat_2468  = quat_1234 + quat_1234;
    auto quat2_1234 = quat_2468 - quat_1234;
    auto quat3_1234  = quat_1234 * 1.0;
  }

  SECTION("advanced algebra ops")
  {
    auto mag = magnitude(quat_1234);
    auto dscl = dot(quat_1234,quat_1234);
    auto cvec = cross(quat_1234, quat_1234);
  }

}//end TEST CASE
