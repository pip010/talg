#pragma once

#include "vector.hpp"

namespace talg
{
	typedef TVector<4, double, vtag_xyzw> Vec4d;
	typedef TVector<4, float, vtag_xyzw> Vec4f;
	typedef TVector<3, double, vtag_xyz> Vec3d;
	typedef TVector<3, float, vtag_xyz> Vec3f;
	//http://stackoverflow.com/questions/384502/what-is-the-bit-size-of-long-on-64-bit-windows
	typedef TVector<3, long long, vtag_ijk> Vec3l;
	typedef TVector<2, double, vtag_xy> Vec2d;
	typedef TVector<2, float, vtag_xy> Vec2f;

	typedef TVector<3, double, vtag_rgb> Color3d;
	typedef TVector<3, float, vtag_rgb> Color3f;
	typedef TVector<4, double, vtag_rgba> Color4d;
	typedef TVector<4, float, vtag_rgba> Color4f;

	static const Color3d BLACK = { 0.0, 0.0, 0.0 };
	static const Color3d RED = { 1.0, 0.0, 0.0 };
	static const Color3d GREEN = { 0.0, 1.0, 0.0 };
	static const Color3d BLUE = { 0.0, 0.0, 1.0 };
	static const Color3d YELLOW = { 1.0, 1.0, 0.0 };
	static const Color3d PURPLE = { 1.0, 0.0, 1.0 };
	static const Color3d GRAY = { 0.3, 0.3, 0.3 };
	static const Color3d LIGHTGRAY = { 0.8, 0.8, 0.8 };
	static const Color3d WHITE = { 1.0, 1.0, 1.0 };
}