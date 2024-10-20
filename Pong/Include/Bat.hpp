#pragma once

#include <Util/Common.hpp>
#include <Core/Sprite.hpp>

namespace blox
{
	class Bat
	{
	private:
		Vec2 position;
		Sprite sprite;
		Rect rect;

		float speed;
		bool movingLeft = false;
		bool movingRight = false;

	public:
		Bat();

		Vec2 GetPosition();
		Rect GetRect();

		void MoveLeft();
		void MoveRight();
		void StopLeft();
		void StopRight();
		void SpeedUp();
		void Reset();

		void Update();
		void Render();
	};
}