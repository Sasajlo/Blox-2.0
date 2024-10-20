#include "Ball.hpp"

using namespace blox;

Ball::Ball()
{
	this->speed = 400.0f;
	this->direction = { 1.0f, -1.0f };

	this->sprite.SetPosition(this->position);
	this->sprite.SetSize({ 10, 10 });

	this->rect.x = this->position.x - 5;
	this->rect.y = this->position.y - 5;
	this->rect.width = 10;
	this->rect.height = 10;

	// Hit sound
	Sound::Load(&hitSound, "Pong/Assets/Audio/hit.wav");
	this->hitSound.SetVolume(0.3f);

	Reset();
}

Vec2 Ball::GetPosition()
{
	return this->position;
}

Vec2 Ball::GetDirection()
{
	return this->direction;
}

bool Ball::HasHitBat()
{
	return this->hitBat;
}

bool Ball::HasHitBottom()
{
	return this->hitBottom;
}

void Ball::Reset()
{
	srand(Time::GetTime());
	this->position.x = rand() % 1800 + 60;
	this->position.y = 1075;
}

void Ball::Update(Bat bat)
{
	// Reset states
	this->hitBat = false;
	this->hitBottom = false;

	// Update position
	this->position.x += this->direction.x * this->speed * Time::GetDeltaTime();
	this->position.y += this->direction.y * this->speed * Time::GetDeltaTime();

	// Update rect
	this->rect.x = this->position.x - 5;
	this->rect.y = this->position.y - 5;

	if (this->direction.y < 0)
	{
		this->hitBat = Rect::CheckCollision(this->rect, bat.GetRect());
		if (this->hitBat)
		{
			this->direction.y *= -1;
			this->speed *= 1.02f;
			hitSound.Play();
		}
	}

	if (this->position.x > 1915) // Right wall hit
	{
		this->position.x = 1915;
		this->direction.x *= -1;
		hitSound.Play();
	}
	else if (this->position.x < 5) // Left wall hit
	{
		this->position.x = 5;
		this->direction.x *= -1;
		hitSound.Play();
	}

	if (this->position.y > 1075) // Top wall hit
	{
		this->position.y = 1075;
		this->direction.y *= -1;
		hitSound.Play();
	}
	else if (this->position.y < 5) // Bottom wall hit
	{
		this->position.y = 5;
		this->direction.y *= -1;

		this->hitBottom = true;
		hitSound.Play();
	}

	this->sprite.SetPosition(this->position);
}

void Ball::Render()
{
	this->sprite.Render();
}
