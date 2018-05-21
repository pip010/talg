#pragma once

#include <matrix.hpp>

namespace talg
{

  	template<typename T>
  	struct MatrixTransform : public TMatrix<4,4,T>
  	{
  		using TMat4 = TMatrix<4,4,T>;
  		using TMat3 = TMatrix<3,3,T>;
  		using TVec4 = TVector<4,T,vtag_xyzw>;
  		using TVec3 = TVector<3,T,vtag_xyz>;

  		using TMat4::map;
  		using TMat4::data;

  		MatrixTransform()
  		//: TMat4(TMat4::IDENTITY)
  		: TMat4{
  			1,0,0,0,
  			0,1,0,0,
  			0,0,1,0,
  			0,0,0,1
  			}
  		{
  		}

  		TVec3 Trans3x1() const
  		{
  			return { map[0][3], map[1][3], map[2][3] };
  		}

  		TVec3 Scale3x1() const
  		{
  			return {
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}),
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}),
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]})
  			};
  		}

  		TMat3 Scale3x3() const
  		{
  			return {
  				magnitude(TVec3{map[0][0], map[1][0], map[2][0]}), 0.0, 0.0,
  				0.0, magnitude(TVec3{map[0][0], map[1][0], map[2][0]}), 0.0,
  				0.0, 0.0, magnitude(TVec3{map[0][0], map[1][0], map[2][0]})
  			};
  		}

  		TMat3 Rotate3x3() const
  		{
  			//TODO numerical safe DIV by 0
  			//TODO turn divisions into multi

  			//auto s = Scale3x1() + std::numeric_limits<T>::min();
  			auto s = Scale3x1();

  			return {
  				map[0][0] / s.x , map[0][1] / s.y, map[0][2] / s.z ,
  				map[1][0] / s.x , map[1][1] / s.y, map[1][2] / s.z ,
  				map[2][0] / s.x , map[2][1] / s.y, map[2][2] / s.z
  			};
  		}

  		// TMatrix<3,3> Scale3x3() const
  		// {
  		// 	return {
  		// 		magnitude({map[0][0], map[1][0], map[2][]}),
  		// 	};
  		// }

  		TMat4 RotationMatrixArounAxisX(double angle)
  		{
  			return {
  				1, 0, 0, 0,
  				0, cos(angle), -sin(angle), 0,
  				0, sin(angle), cos(angle), 0,
  				0, 0, 0, 1 };
  		}
  		TMat4 RotationMatrixAroundAxisY(double angle)
  		{
  			return {
  				cos(angle), 0, sin(angle), 0,
  				0, 1, 0, 0,
  				-sin(angle), 0, cos(angle), 0,
  				0, 0, 0, 1 };
  		}
  		TMat4 RotationMatrixAroundAxisZ(double angle)
  		{
  			return {
  				cos(angle), -sin(angle), 0, 0,
  				sin(angle), cos(angle), 0, 0,
  				0, 0, 1, 0,
  				0, 0, 0, 1 };
  		}

  	};

}//end namespace
