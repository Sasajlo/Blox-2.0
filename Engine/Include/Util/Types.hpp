#pragma once

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long long ulong;

namespace blox
{
	struct Vec2
	{
		float x;
		float y;
	};

	struct Vec3
	{
		float x;
		float y;
		float z;
	};

	struct Vec2i
	{
		int x;
		int y;
	};

	struct Vec3i
	{
		int x;
		int y;
		int z;
	};

	struct Dimension
	{
		float width;
		float height;
	};

	struct Size
	{
		int width;
		int height;
	};

	struct Color
	{
		uchar r;
		uchar g;
		uchar b;
		uchar a = 255;

		static Color WHITE;
		static Color BLACK;
		static Color RED;
		static Color GREEN;
		static Color BLUE;
	};

	struct Rect
	{
		float x;
		float y;
		float width;
		float height;

		static bool CheckCollision(Rect rectA, Rect rectB);
	};
}