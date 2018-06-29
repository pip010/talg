#pragma once

#include "matrix.hpp"

#include <cassert>

namespace talg
{

  	template<typename T>
  	struct Transform : public TMatrix<4,4,T>
  	{
  		using TMat4 = TMatrix<4,4,T>;
  		using TMat3 = TMatrix<3,3,T>;
  		using TVec4 = TVector<4,T,vtag_xyzw>;
  		using TVec3 = TVector<3,T,vtag_xyz>;

  		using TMat4::map;
  		using TMat4::data;

		Transform()
  		: 
			TMat4(TMat4::IDENTITY())
  		{}

		Transform(TMat4 m)
			:
			TMat4(m)
		{
			assert(map[3][3] == 1.0 && "Not homogenious matrix set");
		}

		/////------------------------------------------------------
		/// Convinient Getters
		/////------------------------------------------------------


  		TVec3 GetTrans3x1() const
  		{
  			return 
			{ 
				map[0][3], map[1][3], map[2][3] 
			};
  		}

  		TVec3 GetScale3x1() const
  		{
  			return 
			{
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}),
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}),
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]})
  			};
  		}

  		TMat3 GetScale3x3() const
  		{
  			return 
			{
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}), 0.0, 0.0,
  				0.0, magnitude(TVec3{map[0][0], map[1][0], map[2][0]}), 0.0,
  				0.0, 0.0, magnitude(TVec3{map[0][0], map[1][0], map[2][0]})
  			};
  		}

  		TMat3 GetRotate3x3() const
  		{
  			//TODO numerical safe DIV by 0
  			//TODO turn divisions into multi

  			//auto s = Scale3x1() + std::numeric_limits<T>::min();
  			auto s = Scale3x1();

  			return 
			{
  				map[0][0] / s.x , map[0][1] / s.y, map[0][2] / s.z ,
  				map[1][0] / s.x , map[1][1] / s.y, map[1][2] / s.z ,
  				map[2][0] / s.x , map[2][1] / s.y, map[2][2] / s.z
  			};
  		}


		/////------------------------------------------------------
		/// static helper functions
		/////------------------------------------------------------

		static constexpr TMat4 RotationMatrixX(T angle)
  		{
  			return 
			{
  				1, 0, 0, 0,
  				0, cos(angle), -sin(angle), 0,
  				0, sin(angle), cos(angle), 0,
  				0, 0, 0, 1 
			};
  		}

		static constexpr TMat4 RotationMatrixY(T angle)
  		{
  			return 
			{
  				cos(angle), 0, sin(angle), 0,
  				0, 1, 0, 0,
  				-sin(angle), 0, cos(angle), 0,
  				0, 0, 0, 1 
			};
  		}

		static constexpr TMat4 RotationMatrixZ(T angle)
  		{
  			return 
			{
  				cos(angle), -sin(angle), 0, 0,
  				sin(angle), cos(angle), 0, 0,
  				0, 0, 1, 0,
  				0, 0, 0, 1 
			};
  		}

		static constexpr TMat4 RotationMatrix(int axis, T angle)
		{
			assert(axis >= 0 && axis <= 2 && "axis out of range [0-2]");

			switch (axis)
			{
				case 0: return RotationMatrixX(angle);
				case 1: return RotationMatrixY(angle);
				case 2: return RotationMatrixZ(angle);
				default: return RotationMatrixX(angle);
			}

		}

		static constexpr TMat4 ScaleMatrix(T factor)
		{
			return 
			{
				factor, 0, 0, 0,
				0, factor, 0, 0,
				0, 0, factor, 0,
				0, 0, 0, 1
			};
		}

		static constexpr TMat4 TranslationMatrix(T x, T y, T z)
		{
			return 
			{
				0, 0, 0, x,
				0, 0, 0, y,
				0, 0, 0, z,
				0, 0, 0, 1
			};
		}

		static constexpr TMat4 TranslationMatrixX(T offset)
		{
			return TranslationMatrix(offset, 0, 0);
		}

		static constexpr TMat4 TranslationMatrixY(T offset)
		{
			return TranslationMatrix(0, offset, 0);
		}

		static constexpr TMat4 TranslationMatrixZ(T offset)
		{
			return TranslationMatrix(0, 0, offset);
		}

		static constexpr TMat4 TranslationMatrix(TVec4 t)
		{
			return TranslationMatrix(t(0), t(1), t(2));
		}

		static constexpr TMat4 TranslationMatrix(TVec3 t)
		{
			return TranslationMatrix(t(0), t(1), t(2));
		}

		/////------------------------------------------------------
		/// functions chaining for building a final tranform
		/////------------------------------------------------------

		Transform<T>& RotateX(T angle)
		{
			*this = RotationMatrixX(angle);
			return *this;
		}

		Transform<T>& RotateY( T angle)
		{
			*this = RotationMatrixY(angle);
			return *this;
		}

		Transform<T>& RotateZ(T angle)
		{
			*this = RotationMatrixZ(angle);
			return *this;
		}

		Transform<T>& Rotate(int axis, T angle)
		{
			*this = RotationMatrix(angle);
			return *this;
		}

		Transform<T>& Scale(T factor)
		{
			*this = ScaleMatrix(factor);
			return *this;
		}

		Transform<T>& Translate(T x, T y, T z)
		{
			*this = TranslationMatrix(x,y,z);
			return *this;
		}

		Transform<T>& Translate(TVec4 t)
		{
			*this = TranslationMatrix(t);
			return *this;
		}

		Transform<T>& Translate(TVec3 t)
		{
			*this = TranslationMatrix(t);
			return *this;
		}

  	};

}//end namespace
