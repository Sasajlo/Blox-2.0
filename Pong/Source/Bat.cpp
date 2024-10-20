#include "Bat.hpp"

using namespace blox;

Bat::Bat()
{
	this->position = { 960, 45 };

	this->sprite.SetPosition(this->position);
	this->sprite.SetSize({ 100, 5 });

	this->speed = 650.0f;

	this->rect.x = this->position.x - 50;
	this->rect.y = this->position.y - 2.5f;
	this->rect.width = 100;
	this->rect.height = 5;
}

Vec2 Bat::GetPosition()
{
	return this->position;
}

Rect Bat::GetRect()
{
	return this->rect;
}

void Bat::MoveLeft()
{
	this->movingLeft = true;
}

void Bat::MoveRight()
{
	this->movingRight = true;
}

void Bat::StopLeft()
{
	this->movingLeft = false;
}

void Bat::StopRight()
{
	this->movingRight = false;
}

void Bat::SpeedUp()
{
	this->speed *= 1.02f;
}

void Bat::Reset()
{
	this->speed = 650.0f;
	this->position = { 960, 45 };
}

void Bat::Update()
{
	// Update position
	if (this->movingLeft)
		this->position.x -= this->speed * Time::GetDeltaTime();

	// Clamp position
	this->position.x = Math::Min(Math::Max(this->position.x, 50), 1870);

	if (this->movingRight)
		this->position.x += this->speed * Time::GetDeltaTime();

	// Update rect
	this->rect.x = this->position.x - 50;
	this->rect.y = this->position.y - 2.5f;

	this->sprite.SetPosition(this->position);
}

void Bat::Render()
{
	this->sprite.Render();
}
