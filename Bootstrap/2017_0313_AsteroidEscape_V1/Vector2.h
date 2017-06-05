#pragma once

class Vector2
{
public:
	///Constructor
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& a_rhs);   //Copy/reference constructor
	~Vector2() = default;

	Vector2 operator + (const Vector2& a_rhs) const;						// V2 = V2 + V2 
	Vector2 operator - (const Vector2& a_rhs) const;						// V2 = V2 - V2 
	Vector2& operator += (const Vector2& a_rhs);							// V2 += V2 
	Vector2& operator -= (const Vector2& a_rhs);							// V2 -= V2
	Vector2& operator = (const Vector2& a_rhs);							// V2 = V2
	bool operator == (const Vector2& a_rhs);                            // V2 == V2
	bool operator != (const Vector2& a_rhs);                            // V2 != V2
	Vector2 operator * (float a_scalar) const;								// V2 * f
	friend Vector2 operator * (float a_scalar, const Vector2& a_rhs);		//  f * V2

	Vector2& operator *= (float a_scalar);									// V2 *= f
	Vector2& operator /= (float a_sclar);                                   // V2 /= f

	explicit operator float* () { return &x; }								// *

	float dot(const Vector2& a_rhs);										// dot product

	float magnitude();
	void normalise();
	Vector2 normal();
	float findDistance(const Vector2& a_rhs);

	float x;
	float y;
};

///Friends (related methods)
//If its not a friend, the left hand side will HAVE to be a Vector2 when that's not necessarily the case.
Vector2 operator * (float a_scalar, const Vector2& a_rhs);			//  f * V2

