#include "catch/catch.hpp"

#include <scalar.hpp>




TEST_CASE("Testing TScalar<T>", "[scalar.hpp]")
{
  using namespace talg;

  using TScal = TScalar<double>;

  TScal scal_1{ 1 };
  TScal scal_2{ 2 };
  TScal scal_0{};
  TScal scal_UB;


  SECTION("Correct init & Check access")
  {
    TScal dist = 111.0_mm;

  }

}//end TEST CASE
