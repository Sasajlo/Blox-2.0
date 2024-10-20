#include <Util/Types.hpp>

using namespace blox;

Color Color::WHITE = { 255, 255, 255, 255 };
Color Color::BLACK = { 0, 0, 0, 255 };
Color Color::RED = { 255, 0, 0, 255 };
Color Color::GREEN = { 0, 255, 0, 255 };
Color Color::BLUE = { 0, 0, 255, 255 };

bool Rect::CheckCollision(Rect rectA, Rect rectB)
{
	return (rectA.x < rectB.x + rectB.width) && (rectA.x + rectA.width > rectB.x) && (rectA.y < rectB.y + rectB.height) && (rectA.y + rectA.height > rectB.y);
}
