#pragma once

#include <iostream>

#include <cassert>


namespace talg
{
  namespace details
  {

    struct TSdata
    {

    };
  }

	//this one gonna be exciting
	//to design TScalar with units in mind

  template<typename T>
  struct TScalar
  {
    TScalar() = default;

    T val;


  };




  TScalar<double> operator""_mm(long double v){
    return {v};
  }

  // template<typename T>
  // TScalar<T> operator""_mm ()
  // {
    // return TScalar<T>(static_cast<T>(v));
  // }

  // used as conversion
// constexpr long double operator"" _deg ( long double deg )
// {
//     return deg*3.141592/180;
// }



}//end namespace
