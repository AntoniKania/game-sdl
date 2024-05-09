#include "vector2.h"

//CONSTRUCTORS
Vector2::Vector2(void) : x(0), y(0) { }
Vector2::Vector2(float32 xValue, float32 yValue) : x(xValue), y(yValue) { }
Vector2::Vector2(const Vector2 & v) : x(v.x), y(v.y) { }
Vector2::Vector2(const Vector2 * v) : x(v->x), y(v->y) { }

//DECONSTRUCTOR
Vector2::~Vector2(void) { }

//METHODS
void Vector2::Set(float32 xValue, float32 yValue) { x = xValue; y = yValue; }

float32 Vector2::Length() const { return sqrt(x * x + y * y); }
float32 Vector2::LengthSquared() const { return x * x + y * y; }
float32 Vector2::Distance(const Vector2 & v) const { return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y))); }
float32 Vector2::DistanceSquared(const Vector2 & v) const { return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)); }
float32 Vector2::Dot(const Vector2 & v) const { return x * v.x + y * v.y; }
float32 Vector2::Cross(const Vector2 & v) const { return x * v.y + y * v.x; }

Vector2 & Vector2::Normal() { Set(-y, x); return *this; }
Vector2 & Vector2::Normalize()
{
    if(Length() != 0)
    {
        float32 length = LengthSquared();
        x /= length; y /= length;
        return *this;
    }

    x = y = 0;
    return *this;
}
