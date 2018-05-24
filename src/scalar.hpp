#pragma once

#include <iostream>

#include <cassert>

#include <ratio>

namespace talg
{


  template<typename Mass, typename Length, typename Time, typename Angle>
  struct TScalar
  {
    constexpr TScalar() = default;
    constexpr TScalar(double v) : value(v) {}
    constexpr TScalar(long double v) : value(static_cast<double>(v)) {}

    // The intrinsic operations for a quantity with a unit is addition and subtraction
    constexpr TScalar const& operator+=(const TScalar& rhs)
    {
        value += rhs.value;
        return *this;
    }
    constexpr TScalar const& operator-=(const TScalar& rhs)
    {
        value -= rhs.value;
        return *this;
    }

    // Returns the value of the quantity in multiples of the specified unit
    constexpr double Convert(const TScalar& rhs) const
    {
        return value / rhs.value;
    }

    // returns the raw value of the quantity (should not be used)
    constexpr double getValue() const
    {
        return value;
    }

  private:
    double value;
  };

  // Predefined (physical unit) quantity types:
  // ------------------------------------------
  #define UNIT_TYPE(_Mdim, _Ldim, _Tdim, _Adim, name) \
      typedef TScalar< std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>, std::ratio<_Adim>> name;

  // Dummy unitless number
  UNIT_TYPE(0, 0, 0, 0, UNumber);
  // Physical unit types
  UNIT_TYPE(1, 0, 0, 0, UMass);
  UNIT_TYPE(0, 1, 0, 0, UDistance);
  UNIT_TYPE(0, 2, 0, 0, UArea);
  UNIT_TYPE(0, 3, 0, 0, UVolume);
  UNIT_TYPE(0, 0, 1, 0, UTime);
  UNIT_TYPE(0, 1, -1, 0, USpeed);
  UNIT_TYPE(0, 1, -2, 0, UAcceleration);
  UNIT_TYPE(0, 1, -3, 0, UJerk);
  UNIT_TYPE(0, 0, -1, 0, UFrequency);
  UNIT_TYPE(1, 1, -2, 0, UForce);
  UNIT_TYPE(1, -1, -2, 0, UPressure);
  // Angle type
  UNIT_TYPE(0, 0, 0, 1, UAngle);


  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<M, L, T, A>
      operator+ (const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return TScalar<M, L, T, A>(lhs.getValue() + rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<M, L, T, A>
      operator- (const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return TScalar<M, L, T, A>(lhs.getValue() - rhs.getValue());
  }

  template <typename M1, typename L1, typename T1, typename A1,
            typename M2, typename L2, typename T2, typename A2>
  constexpr TScalar<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
                      std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
      operator* (const TScalar<M1, L1, T1, A1>& lhs, const TScalar<M2, L2, T2, A2>& rhs)
  {
      return TScalar<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
                       std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
                      (lhs.getValue()*rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<M, L, T, A>
      operator* (const double& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return TScalar<M, L, T, A>(lhs*rhs.getValue());
  }

  template <typename M1, typename L1, typename T1, typename A1,
            typename M2, typename L2, typename T2, typename A2>
  constexpr TScalar<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
                      std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
      operator/ (const TScalar<M1, L1, T1, A1>& lhs, const TScalar<M2, L2, T2, A2>& rhs)
  {
      return TScalar<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
                       std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
                      (lhs.getValue() / rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>,
                      std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>>
      operator/ (double x, const TScalar<M, L, T, A>& rhs)
  {
      return TScalar<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>,
                       std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>>
                      (x / rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<M, L, T, A>
      operator/ (const TScalar<M, L, T, A>& rhs, double x)
  {
      return TScalar<M, L, T, A>(rhs.getValue() / x);
  }


  template <typename M, typename L, typename T, typename A>
  constexpr bool operator==(const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
    //TODO fix comparison of doubles
      return (lhs.getValue() == rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator!=(const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return (lhs.getValue() != rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator<=(const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return (lhs.getValue() <= rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator>=(const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return (lhs.getValue() >= rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator< (const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return (lhs.getValue()<rhs.getValue());
  }

  template <typename M, typename L, typename T, typename A>
  constexpr bool operator> (const TScalar<M, L, T, A>& lhs, const TScalar<M, L, T, A>& rhs)
  {
      return (lhs.getValue()>rhs.getValue());
  }




  namespace units
  {

    // Predefined mass units:
    constexpr UMass kg(1.0); // SI base unit
    constexpr UMass gramme = 0.001 * kg;
    constexpr UMass tonne = 1000 * kg;
    constexpr UMass ounce = 0.028349523125 * kg;
    constexpr UMass pound = 16 * ounce;
    constexpr UMass stone = 14 * pound;

    // Predefined distance-derived units
    constexpr UDistance metre(1.0); // SI base unit
    constexpr UDistance decimetre = metre / 10;
    constexpr UDistance centimetre = metre / 100;
    constexpr UDistance millimetre = metre / 1000;
    constexpr UDistance kilometre = 1000 * metre;
    constexpr UDistance inch = 2.54 * centimetre;
    constexpr UDistance foot = 12 * inch;
    constexpr UDistance yard = 3 * foot;
    constexpr UDistance mile = 5280 * foot;

    constexpr UArea kilometre2 = kilometre*kilometre;
    constexpr UArea metre2 = metre*metre;
    constexpr UArea decimetre2 = decimetre*decimetre;
    constexpr UArea centimetre2 = centimetre*centimetre;
    constexpr UArea millimetre2 = millimetre * millimetre;
    constexpr UArea inch2 = inch*inch;
    constexpr UArea foot2 = foot*foot;
    constexpr UArea mile2 = mile*mile;

    constexpr UVolume kilometre3 = kilometre2*kilometre;
    constexpr UVolume metre3 = metre2*metre;
    constexpr UVolume decimetre3 = decimetre2*decimetre;
    constexpr UVolume litre = decimetre3;
    constexpr UVolume centimetre3 = centimetre2*centimetre;
    constexpr UVolume millimetre3 = millimetre2 * millimetre;
    constexpr UVolume inch3 = inch2*inch;
    constexpr UVolume foot3 = foot2*foot;
    constexpr UVolume mile3 = mile2*mile;

    // Predefined time-derived units:
    constexpr UTime second(1.0); // SI base unit
    constexpr UTime minute = 60 * second;
    constexpr UTime hour = 60 * minute;
    constexpr UTime day = 24 * hour;

    constexpr UFrequency Hz(1.0);

    // Predefined mixed units:
    constexpr UAcceleration G = 9.80665 *  metre / (second*second);

    constexpr UForce newton(1.0);
    constexpr UForce poundforce = pound*G;
    constexpr UForce kilopond = kg*G;

    constexpr UPressure Pascal(1.0);
    constexpr UPressure bar = 100000 * Pascal;
    constexpr UPressure psi = pound*G / inch2;


    // literals for length units
    constexpr UDistance operator"" _mm(long double x) { return static_cast<double>(x)*millimetre; }
    constexpr UDistance operator"" _cm(long double x) { return static_cast<double>(x)*centimetre; }
    constexpr UDistance operator"" _m(long double x) { return static_cast<double>(x)*metre; }
    constexpr UDistance operator"" _km(long double x) { return static_cast<double>(x)*kilometre; }
    constexpr UDistance operator"" _mi(long double x) { return static_cast<double>(x)*mile; }
    constexpr UDistance operator"" _yd(long double x) { return static_cast<double>(x)*yard; }
    constexpr UDistance operator"" _ft(long double x) { return static_cast<double>(x)*foot; }
    constexpr UDistance operator"" _in(long double x) { return static_cast<double>(x)*inch; }
    constexpr UDistance operator"" _mm(unsigned long long int x) { return static_cast<double>(x)*millimetre; }
    constexpr UDistance operator"" _cm(unsigned long long int  x) { return static_cast<double>(x)*centimetre; }
    constexpr UDistance operator"" _m(unsigned long long int  x) { return static_cast<double>(x)*metre; }
    constexpr UDistance operator"" _km(unsigned long long int  x) { return static_cast<double>(x)*kilometre; }
    constexpr UDistance operator"" _mi(unsigned long long int  x) { return static_cast<double>(x)*mile; }
    constexpr UDistance operator"" _yd(unsigned long long int  x) { return static_cast<double>(x)*yard; }
    constexpr UDistance operator"" _ft(unsigned long long int  x) { return static_cast<double>(x)*foot; }
    constexpr UDistance operator"" _in(unsigned long long int  x) { return static_cast<double>(x)*inch; }

    // literals for speed units
    constexpr USpeed operator"" _mps(long double x) { return USpeed(x); };
    constexpr USpeed operator"" _miph(long double x) { return static_cast<double>(x)*mile / hour; };
    constexpr USpeed operator"" _kmph(long double x) { return static_cast<double>(x)*kilometre / hour; };
    constexpr USpeed operator"" _mps(unsigned long long int x) { return USpeed(static_cast<long double>(x)); };
    constexpr USpeed operator"" _miph(unsigned long long int x) { return static_cast<double>(x)*mile / hour; };
    constexpr USpeed operator"" _kmph(unsigned long long int x) { return static_cast<double>(x)*kilometre / hour; };

    // literal for frequency unit
    constexpr UFrequency operator"" _Hz(long double x) { return UFrequency(x); };
    constexpr UFrequency operator"" _Hz(unsigned long long int x) { return UFrequency(static_cast<long double>(x)); };

    // literals for time units
    constexpr UTime operator"" _s(long double x) { return UTime(x); };
    constexpr UTime operator"" _min(long double x) { return static_cast<double>(x)*minute; };
    constexpr UTime operator"" _h(long double x) { return static_cast<double>(x)*hour; };
    constexpr UTime operator"" _day(long double x) { return static_cast<double>(x)*day; };
    constexpr UTime operator"" _s(unsigned long long int x) { return UTime(static_cast<double>(x)); };
    constexpr UTime operator"" _min(unsigned long long int x) { return static_cast<double>(x)*minute; };
    constexpr UTime operator"" _h(unsigned long long int x) { return static_cast<double>(x)*hour; };
    constexpr UTime operator"" _day(unsigned long long int x) { return static_cast<double>(x)*day; };

    // literals for mass units
    constexpr UMass operator"" _kg(long double x) { return UMass(x); };
    constexpr UMass operator"" _g(long double x) { return static_cast<double>(x)*gramme; };
    constexpr UMass operator"" _t(long double x) { return static_cast<double>(x)*tonne; };
    constexpr UMass operator"" _oz(long double x) { return static_cast<double>(x)*ounce; };
    constexpr UMass operator"" _lb(long double x) { return static_cast<double>(x)*pound; };
    constexpr UMass operator"" _st(long double x) { return static_cast<double>(x)*stone; };
    constexpr UMass operator"" _kg(unsigned long long int x) { return UMass(static_cast<double>(x)); };
    constexpr UMass operator"" _g(unsigned long long int x) { return static_cast<double>(x)*gramme; };
    constexpr UMass operator"" _t(unsigned long long int x) { return static_cast<double>(x)*tonne; };
    constexpr UMass operator"" _oz(unsigned long long int x) { return static_cast<double>(x)*ounce; };
    constexpr UMass operator"" _lb(unsigned long long int x) { return static_cast<double>(x)*pound; };
    constexpr UMass operator"" _st(unsigned long long int x) { return static_cast<double>(x)*stone; };

    // literals for acceleration units
    constexpr UAcceleration operator"" _mps2(long double x) { return UAcceleration(x); };
    constexpr UAcceleration operator"" _mps2(unsigned long long int x)
                                            { return UAcceleration(static_cast<double>(x)); };
    constexpr UAcceleration operator"" _G(long double x) { return static_cast<double>(x)*G; };
    constexpr UAcceleration operator"" _G(unsigned long long int x) { return static_cast<double>(x)*G; }

    // literals for force units
    constexpr UForce operator"" _N(long double x) { return UForce(x); };
    constexpr UForce operator"" _N(unsigned long long int x) { return UForce(static_cast<double>(x)); };
    constexpr UForce operator"" _lbf(long double x) { return static_cast<double>(x)*poundforce; };
    constexpr UForce operator"" _lbf(unsigned long long int x) { return static_cast<double>(x)*poundforce; };
    constexpr UForce operator"" _kp(long double x) { return static_cast<double>(x)*kilopond; };
    constexpr UForce operator"" _kp(unsigned long long int x) { return static_cast<double>(x)*kilopond; };

    // literals for pressure units
    constexpr UPressure operator"" _Pa(long double x) { return UPressure(x); };
    constexpr UPressure operator"" _Pa(unsigned long long int x)
                                      { return UPressure(static_cast<double>(x)); };
    constexpr UPressure operator"" _bar(long double x) { return static_cast<double>(x)*bar; };
    constexpr UPressure operator"" _bar(unsigned long long int x) { return static_cast<double>(x)*bar; };
    constexpr UPressure operator"" _psi(long double x) { return static_cast<double>(x)*psi; };
    constexpr UPressure operator"" _psi(unsigned long long int x) { return static_cast<double>(x)*psi; };


    // Angular unit literals:
    // ----------------------
    constexpr long double operator"" _pi(long double x)
        { return static_cast<double>(x) * 3.1415926535897932384626433832795; }
    constexpr long double operator"" _pi(unsigned long long int x)
        { return static_cast<double>(x) * 3.1415926535897932384626433832795; }

    // Predefined angle units:
    constexpr UAngle radian(1.0);
    constexpr UAngle degree = static_cast<double>(2_pi / 360.0) * radian;

    // literals for angle units
    constexpr UAngle operator"" _rad(long double x) { return UAngle(x); };
    constexpr UAngle operator"" _rad(unsigned long long int x) { return UAngle(static_cast<double>(x)); };
    constexpr UAngle operator"" _deg(long double x) { return static_cast<double>(x)*degree; };
    constexpr UAngle operator"" _deg(unsigned long long int x) { return static_cast<double>(x)*degree; };

    // Conversion macro, which utilizes the string literals
    #define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)

  }// end namespace units



  // Typesafe mathematical operations:
  // ---------------------------------
  template <typename M, typename L, typename T, typename A>
  constexpr TScalar<std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
                      std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>
      Qsqrt(const TScalar<M, L, T, A>& num)
  {
      return TScalar<std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
                       std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>
                      (sqrt(num.getValue()));
  }

  // Typesafe trigonometric operations
  inline double sin(const UAngle &num)
  {
      return sin(num.getValue());
  }
  inline double cos(const UAngle &num)
  {
      return cos(num.getValue());
  }
  inline double tan(const UAngle &num)
  {
      return tan(num.getValue());
  }


  // TEMPLATED: https://stackoverflow.com/questions/39795893/when-and-how-to-use-a-template-literal-operator
  // template<typename T>
  // TScalar<T> operator""_mm ()
  // {
    // return TScalar<T>(static_cast<T>(v));
  // }




}//end namespace talg
