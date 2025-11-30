#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
class Vector2d
{
public:
	float x;
	float y;
	
	Vector2d();
	Vector2d(float x, float y);
	Vector2d operator+(Vector2d other);
	Vector2d operator-(Vector2d other);
	Vector2d operator+=(Vector2d other);
	Vector2d operator-=(Vector2d other);
	Vector2d operator=(Vector2d other);
	bool operator==(Vector2d other);
	Vector2d operator*(float a);
	Vector2d operator*=(float a);
	friend Vector2d operator*(float a, Vector2d vector);
	friend Vector2d operator*=(float a, Vector2d vector);
	float Dot(Vector2d other);
	float getMagnitude();
	Vector2d getNormalized();
	void normalize();
	operator Vector2f();
	Vector2d getNormal();

	void print();
};

