#ifndef MUTALISK_DATA_TYPES_H_
#define MUTALISK_DATA_TYPES_H_

#include "cfg.h"
#include "array.h"

namespace mutalisk { namespace data
{
	typedef unsigned char byte;

	struct Color {
		float r, g, b, a;
	};
	struct Vec3 {
		float const& operator[](unsigned int index) const { return data[index]; }
		float & operator[](unsigned int index) { return data[index]; }
		float data[3];
	};
	struct Vec4 {
		float const& operator[](unsigned int index) const { return data[index]; }
		float & operator[](unsigned int index) { return data[index]; }
		float data[4];
	};
	struct Mat16 {
		float const& operator[](unsigned int index) const { return data[index]; }
		float & operator[](unsigned int index) { return data[index]; }
		float data[16];
	};

} // namespace data
} // namespace mutalisk

#endif // MUTALISK_DATA_TYPES_H_
