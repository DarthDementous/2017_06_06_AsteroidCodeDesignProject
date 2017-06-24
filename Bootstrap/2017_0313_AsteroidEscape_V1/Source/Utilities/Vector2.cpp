#include "Vector2.h"
#include "Utility.h"
#include <math.h> 

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float a_x, float a_y) : x(a_x), y(a_y)
{
}

Vector2::Vector2(const Vector2 & a_rhs) : x(a_rhs.x), y(a_rhs.y)
{
}

Vector2 Vector2::operator + (const Vector2& a_rhs) const  //Don't change the value of x or y
{
	return Vector2(x + a_rhs.x, y + a_rhs.y);           //x, y = referring to left hand side
}

Vector2 Vector2::operator - (const Vector2& a_rhs) const
{
	return Vector2(x - a_rhs.x, y - a_rhs.y);
}

Vector2& Vector2::operator += (const Vector2& a_rhs)
{
	x += a_rhs.x, y += a_rhs.y;                        //We need to change the left hand side this time
	return *this;										   //Return de-referenced lhs
}

Vector2& Vector2::operator -= (const Vector2& a_rhs)
{
	x -= a_rhs.x, y -= a_rhs.y;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& a_rhs)
{
	x = a_rhs.x, y = a_rhs.y;
	return *this;
}

bool Vector2::operator == (const Vector2& a_rhs) {
	if (x == a_rhs.x && y == a_rhs.y) return true;
	return false;
}

bool Vector2::operator != (const Vector2& a_rhs) {
	if (x != a_rhs.x && y != a_rhs.y) return true;
	return false;
}

Vector2 Vector2::operator * (float a_scalar) const
{
	return Vector2(x * a_scalar, y * a_scalar);         
}

Vector2 operator * (float a_scalar, const Vector2& a_rhs)
{
	return Vector2(a_scalar * a_rhs.x, a_scalar * a_rhs.y);
}

Vector2& Vector2::operator *= (float a_scalar)
{
	x *= a_scalar, y *= a_scalar;
	return *this;
}

Vector2& Vector2::operator /= (float a_scalar)
{
	x /= a_scalar, y /= a_scalar;
	return *this;
}

float Vector2::magnitude()
{
	return (float)((sqrt14)(x * x + y * y));  //Avoid doing intensive square root calculation as much as possible
}

void Vector2::normalise()
{
	float m = magnitude();              //Do intensive calculation once
	x /= m, y /= m;              //calling a method will enact it on the lhs
}

Vector2 Vector2::normal()
{
	float m = magnitude();
	return Vector2(x /= m, y /= m);
}

float Vector2::dot(const Vector2& a_rhs)
{
	return (x * a_rhs.x + y * a_rhs.y);          //Return evaluates whole line before returning it
}

float Vector2::findDistance(const Vector2& a_rhs) {
	return float(sqrt14((x - a_rhs.x)*(x - a_rhs.x) + (y - a_rhs.y)*(y - a_rhs.y)));
}
