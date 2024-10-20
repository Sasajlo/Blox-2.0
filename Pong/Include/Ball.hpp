#pragma once

#include <Util/Common.hpp>
#include <Core/Sprite.hpp>
#include <Core/Sound.hpp>
#include <Bat.hpp>

namespace blox
{
	class Ball
	{
	private:
		Vec2 position;
		Sprite sprite;
		Rect rect;

		float speed;
		Vec2 direction;

		bool hitBat = false;
		bool hitBottom = false;

		Sound hitSound;

	public:
		Ball();

		Vec2 GetPosition();
		Vec2 GetDirection();
		bool HasHitBat();
		bool HasHitBottom();

		void Reset();

		void Update(Bat bat);
		void Render();
	};
}