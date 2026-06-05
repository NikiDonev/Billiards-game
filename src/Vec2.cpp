#include "Vec2.h"






std::ostream& operator<<(std::ostream& stream, const Vec2& vector)
{
	stream << vector.x << ", " << vector.y << std::endl;
	return stream;
}
