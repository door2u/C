#include <cmath>

class Vec3Clas {
	public:
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
	// index
	float & operator [] (unsigned int righ) {
		if (righ == 0) {
			return this->x;
		}
		else if (righ == 1) {
			return this->y;
		}
		else if (righ == 2) {
			return this->z;
		}
		return this->x;
	}
	// add
	Vec3Clas operator + (Vec3Clas righ) {
		Vec3Clas retu;
		retu.x = x + righ.x;
		retu.y = y + righ.y;
		retu.z = z + righ.z;
		return retu;
	}
	// subtract
	Vec3Clas operator - (Vec3Clas righ) {
		Vec3Clas retu;
		retu.x = x - righ.x;
		retu.y = y - righ.y;
		retu.z = z - righ.z;
		return retu;
	}
	// dot
	float operator * (Vec3Clas righ) {
		float retu;
		retu = x * righ.x + y * righ.y + z * righ.z;
		return retu;
	}
	// scale (Vec3Clas * float)
	Vec3Clas operator * (float righ) {
		Vec3Clas retu;
		retu.x = x * righ;
		retu.y = y * righ;
		retu.z = z * righ;
		return retu;
	}
	// magnitude
	float Magn() {
		float retu = x * x + y * y + z * z;
		retu = sqrtf(retu);
		return retu;
	}
	// cross
	Vec3Clas Cros(Vec3Clas righ) {
		float a = y * righ.z - z * righ.y;
		float b = x * righ.z - z * righ.x;
		float c = x * righ.y - y * righ.x;
		Vec3Clas retu;
		retu.x = a;
		retu.y = -b;
		retu.z = c;
		return retu;
	}
};
	
// scale (float * Vec3Clas)
Vec3Clas operator * (float left, Vec3Clas righ) {
	Vec3Clas retu;
	retu.x = left * righ.x;
	retu.y = left * righ.y;
	retu.z = left * righ.z;
	return retu;
}

std::ostream & operator << (std::ostream & outp, Vec3Clas & righ) {
	outp << "(" << righ.x << ", " << righ.y << ", " << righ.z << ")";
	return outp;
}

struct Vec3 {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
};

std::ostream & operator << (std::ostream & outp, Vec3 & righ) {
	outp << "(" << righ.x << ", " << righ.y << ", " << righ.z << ")";
	return outp;
}
