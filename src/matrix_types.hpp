#pragma once

#include "matrix.hpp"

namespace talg
{
	typedef TMatrix<4,4, double> Mat4d;
	typedef TMatrix<4,4, float> Mat4f;

	typedef TMatrix<3,3, double> Mat3d;
	typedef TMatrix<3,3, float> Mat3f;
	
	static const Mat4d ZERO = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	static const Mat4d IDENTITY = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	static const Mat4d HOMO = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1
	};

	Mat4d RotationMatrixAroundAxisX(double angle)
	{
		return Mat4d{
			1, 0, 0, 0,
			0, cos(angle), -sin(angle), 0,
			0, sin(angle), cos(angle), 0,
			0, 0, 0, 1 };
	}
	Mat4d RotationMatrixAroundAxisY(double angle)
	{
		return Mat4d{
			cos(angle), 0, sin(angle), 0,
			0, 1, 0, 0,
			-sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1 };
	}
	Mat4d RotationMatrixAroundAxisZ(double angle)
	{
		return Mat4d{
			cos(angle), -sin(angle), 0, 0,
			sin(angle), cos(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
	}
}