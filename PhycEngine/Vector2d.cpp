#include"Vector2d.h"

Vector2d::Vector2d()
{
	x = 0;
	y = 0;
}
Vector2d::Vector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2d Vector2d::operator+(Vector2d other)
{
	return Vector2d(x + other.x, y + other.y);
}
Vector2d Vector2d::operator-(Vector2d other)
{
	return Vector2d(x - other.x, y - other.y);
}
Vector2d Vector2d::operator+=(Vector2d other)
{
	return Vector2d(x += other.x, y += other.y);
}
Vector2d Vector2d::operator-=(Vector2d other)
{
	return Vector2d(x -= other.x, y -= other.y);
}
Vector2d Vector2d::operator=(Vector2d other)
{
	return Vector2d(x = other.x, y = other.y);
}
bool Vector2d::operator==(Vector2d other)
{
	return bool(x == other.x&&y == other.y);
}
Vector2d Vector2d::operator*(float a)
{
	return Vector2d(x * a, y * a);
}
Vector2d Vector2d::operator*=(float a)
{
	return Vector2d(x *= a, y *= a);
}
Vector2d operator*(float a, Vector2d vector)
{
	return Vector2d(vector.x * a, vector.y * a);
}
Vector2d operator*=(float a, Vector2d vector)
{
	return Vector2d(vector.x *= a, vector.y *= a);
}
float Vector2d::Dot(Vector2d other)
{
	return x * other.x + y * other.y;
}
float Vector2d::getMagnitude()
{
	return sqrtf(x * x + y * y);
}
Vector2d Vector2d::getNormalized()
{
	float mag = getMagnitude();
	if(mag==0)
		return Vector2d(0, 0);
	return Vector2d(x / mag, y / mag);
}
void Vector2d::normalize()
{
	float mag = getMagnitude();
	x /= mag;
	y /= mag;
}
Vector2d::operator Vector2f()
{
	return Vector2f(x, y);
}
Vector2d Vector2d::getNormal()
{
	return Vector2d(-y, x);
}
void Vector2d::print()
{
	cout << "Vector2d(" << x << ", " << y << ")\n";
}