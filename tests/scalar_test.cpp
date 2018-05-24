

#include "catch/catch.hpp"

#include <scalar.hpp>




TEST_CASE("Testing TScalar<T>", "[scalar.hpp]")
{
  using namespace talg;


  // using TScal = TScalar<double>;

  // TScal scal_1{ 1 };
  // TScal scal_2{ 2 };
  // TScal scal_0{};
  // TScal scal_UB;



  SECTION("Correct init & Check access")
  {
    // TScal dist = 111.0_mm;

    // TScalar2<double,SIUnit::m> scal2a{10};
    // TScalar2<double,SIUnit::mm> scal2b(scal2a);

    //CHECK(scal2b.val == Approx(10000.0));

  }

  SECTION(" Measurements Units Basic ")
  {
      using namespace talg::units;

      UDistance d(10.0);

      auto xxx = 100 * centimetre;
  }

}//end TEST CASE
