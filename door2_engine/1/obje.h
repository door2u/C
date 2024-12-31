
#include <vector>

float pi = acosf(-1.0);

class Came {
	public:
		Vec3Clas loca;
		Vec3Clas u, v, w;
		float rang = 1000.0;
		float clip = 0.1;
		Came() {
			u.x = 1.0;
			w.y = 1.0;
			v.z = 1.0;
		}
};

void Rota(Vec3Clas *poin, float angl, Vec3Clas axis) {
	float p = poin->x;
	float q = poin->y;
	float r = poin->z;
	float t = angl * pi / 180.0;
	t /= 2.0;
	float a = cosf(t);
	float b = sinf(t);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float i = r*(2*b*b*x*z+2*a*b*y)+b*b*p*x*x+2*b*b*q*x*y-b*b*p*y*y-b*b*p*z*z-2*a*b*q*z+a*a*p;
	float j = r*(2*b*b*y*z-2*a*b*x)-b*b*q*x*x+2*b*b*p*x*y+b*b*q*y*y-b*b*q*z*z+2*a*b*p*z+a*a*q;
	float k = r*(-b*b*x*x-b*b*y*y+b*b*z*z+a*a)+x*(2*b*b*p*z+2*a*b*q)+y*(2*b*b*q*z-2*a*b*p);
	poin->x = i;
	poin->y = j;
	poin->z = k;
}

class Int3 {
	public:
		int a = 0;
		int b = 0;
		int c = 0;
	// index
	int & operator [] (unsigned int righ) {
		if (righ == 0) {
			return this->a;
		}
		else if (righ == 1) {
			return this->b;
		}
		else if (righ == 2) {
			return this->c;
		}
		return this->a;
	}
	void operator = (int *righ) {
		a = righ[0];
		b = righ[1];
		c = righ[2];
	}
};

class Poly {
	public:
		// 3 vertex indices that make up a polygon
		Int3 inde;
		// x y z local location of polygon centers
		Vec3Clas cent;
		// x y z that points in the direction of the face angle
		Vec3Clas norm;
		// r g b
		Vec3Clas colo;
		// set to false to stop the polygon from being drawn
		bool draw = true;
	int & operator [] (unsigned int righ) {
		if (righ == 0) {
			return this->inde.a;
		}
		else if (righ == 1) {
			return this->inde.b;
		}
		else if (righ == 2) {
			return this->inde.c;
		}
		else {
			std::cout << "overflow" << std::endl;
		}
		return this->inde.a;
	}
};

class Vert {
	public:
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
		float u = 0.0;
		float v = 0.0;
		float w = 0.0;
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
		else if (righ == 3) {
			return this->u;
		}
		else if (righ == 4) {
			return this->v;
		}
		else if (righ == 5) {
			return this->w;
		}
		else {
			std::cout << "overflow" << std::endl;
		}
		return this->x;
	}
	Vert operator - (Vec3Clas righ) {
		Vert retu;
		retu.x = x - righ.x;
		retu.y = y - righ.y;
		retu.z = z - righ.z;
		return retu;
	}
	operator Vec3Clas() {
		Vec3Clas retu;
		retu.x = x;
		retu.y = y;
		retu.z = z;
		return retu;
	}
	// magnitude
	float Magn() {
		float retu = x * x + y * y + z * z;
		retu = sqrtf(retu);
		return retu;
	}
};

std::ostream & operator << (std::ostream & outp, Vert & righ) {
	outp << "(" << righ.x << ", " << righ.y << ", " << righ.z << ")";
	return outp;
}

void RotaVert(Vert *vert, float angl, Vec3Clas axis) {
	float p = vert->x;
	float q = vert->y;
	float r = vert->z;
	float t = angl * pi / 180.0;
	t /= 2.0;
	float a = cosf(t);
	float b = sinf(t);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float i = r*(2*b*b*x*z+2*a*b*y)+b*b*p*x*x+2*b*b*q*x*y-b*b*p*y*y-b*b*p*z*z-2*a*b*q*z+a*a*p;
	float j = r*(2*b*b*y*z-2*a*b*x)-b*b*q*x*x+2*b*b*p*x*y+b*b*q*y*y-b*b*q*z*z+2*a*b*p*z+a*a*q;
	float k = r*(-b*b*x*x-b*b*y*y+b*b*z*z+a*a)+x*(2*b*b*p*z+2*a*b*q)+y*(2*b*b*q*z-2*a*b*p);
	vert->x = i;
	vert->y = j;
	vert->z = k;
}

class ObjeInit {
	public:
		// object id
		unsigned int iden = 0;
		std::string name = "";
		Vec3Clas loca;
		Vec3Clas scal;
		Vec3Clas rota;
		// is the object static or dynamic. static objects dont move. their global vertex locations are precomputed
		bool stat = false;
		std::vector<Vert> vertList;
		std::vector<Poly> polyList;
	void ApplRota() {
		Vec3Clas x, y, z;
		x.x = 1.0;
		y.y = 1.0;
		z.z = 1.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			RotaVert(&vertList[a], rota.x, x);
			RotaVert(&vertList[a], rota.y, y);
			RotaVert(&vertList[a], rota.z, z);
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			Rota(&polyList[a].cent, rota.x, x);
			Rota(&polyList[a].cent, rota.y, y);
			Rota(&polyList[a].cent, rota.z, z);
			Rota(&polyList[a].norm, rota.x, x);
			Rota(&polyList[a].norm, rota.y, y);
			Rota(&polyList[a].norm, rota.z, z);
		}
		rota = {0.0, 0.0, 0.0};
	}
	void ApplScal() {
		for (unsigned int a = 0; a < vertList.size(); a++) {
			vertList[a].x = vertList[a].x * scal.x;
			vertList[a].y = vertList[a].y * scal.y;
			vertList[a].z = vertList[a].z * scal.z;
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			polyList[a].cent.x = polyList[a].cent.x * scal.x;
			polyList[a].cent.y = polyList[a].cent.y * scal.y;
			polyList[a].cent.z = polyList[a].cent.z * scal.z;
		}
		scal = {0.0, 0.0, 0.0};
	}
	void ApplLoca() {
		for (unsigned int a = 0; a < vertList.size(); a++) {
			vertList[a].x = vertList[a].x + loca.x;
			vertList[a].y = vertList[a].y + loca.y;
			vertList[a].z = vertList[a].z + loca.z;
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			polyList[a].cent.x = polyList[a].cent.x + loca.x;
			polyList[a].cent.y = polyList[a].cent.y + loca.y;
			polyList[a].cent.z = polyList[a].cent.z + loca.z;
		}
		loca = {0.0, 0.0, 0.0};
	}
	void Appl() {
		ApplRota();
		ApplScal();
		ApplLoca();
	}
	void VertProc(Came came) {
		Vec3Clas vectVert;
		float w = 0.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			// get vector from subscreen center to vert
			vectVert = vertList[a] - came.loca;
			w = came.w * vectVert;
			vertList[a].w = w;
			if (w > came.clip && w < came.rang) {
				// get u and v components
				vertList[a].u = vectVert * came.u / w;
				vertList[a].v = vectVert * came.v / w;
			}
		}
	}
	void Init(Came came, bool stat = true, bool prin = true) {
		if (stat == true) {
			Appl();
			if (prin == true) std::cout << "applied transforms" << std::endl;
		}
		VertProc(came);
		if (prin == true) std::cout << "processed vertices" << std::endl;
	}
};

class ObjeDyna {
	public:
		// object id
		unsigned int iden = 0;
		std::string name = "";
		Vec3Clas loca;
		Vec3Clas scal;
		Vec3Clas rota;
		std::vector<Vert> vertList;
		std::vector<Poly> polyList;
	void ApplRota() {
		Vec3Clas x, y, z;
		x.x = 1.0;
		y.y = 1.0;
		z.z = 1.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			RotaVert(&vertList[a], rota.x, x);
			RotaVert(&vertList[a], rota.y, y);
			RotaVert(&vertList[a], rota.z, z);
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			Rota(&polyList[a].cent, rota.x, x);
			Rota(&polyList[a].cent, rota.y, y);
			Rota(&polyList[a].cent, rota.z, z);
			Rota(&polyList[a].norm, rota.x, x);
			Rota(&polyList[a].norm, rota.y, y);
			Rota(&polyList[a].norm, rota.z, z);
		}
		rota = {0.0, 0.0, 0.0};
	}
	void ApplScal() {
		for (unsigned int a = 0; a < vertList.size(); a++) {
			vertList[a].x *= scal.x;
			vertList[a].y *= scal.y;
			vertList[a].z *= scal.z;
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			polyList[a].cent.x *= scal.x;
			polyList[a].cent.y *= scal.y;
			polyList[a].cent.z *= scal.z;
		}
		scal = {0.0, 0.0, 0.0};
	}
	void ApplLoca() {
		for (unsigned int a = 0; a < vertList.size(); a++) {
			vertList[a].x += loca.x;
			vertList[a].y += loca.y;
			vertList[a].z += loca.z;
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			polyList[a].cent.x += loca.x;
			polyList[a].cent.y += loca.y;
			polyList[a].cent.z += loca.z;
		}
		loca = {0.0, 0.0, 0.0};
	}
	void Appl() {
		ApplRota();
		ApplScal();
		ApplLoca();
	}
	void VertProc(Came came) {
		Vec3Clas vectVert;
		float w = 0.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			// get vector from subscreen center to vert
			vectVert = vertList[a] - came.loca;
			w = came.w * vectVert;
			vertList[a].w = w;
			if (w > came.clip && w < came.rang) {
				// get u and v components
				vertList[a].u = vectVert * came.u / w;
				vertList[a].v = vectVert * came.v / w;
			}
		}
	}
	void PolyAppe(unsigned int inde, float clipStar, float clipEndi, unsigned int widt, unsigned int heig) {
		float scau = 1.0;
		float scav = 1.0;
		if (widt > heig) {
			scav = (float)widt / (float)heig;
		}
		else {
			scau = (float)heig / (float)widt;
		}
		if (polyList[inde].draw) {
			float r = polyList[inde].colo.x;
			float g = polyList[inde].colo.y;
			float b = polyList[inde].colo.z;
			float p1x = vertList[polyList[inde].inde.a].u * scau;
			float p2x = vertList[polyList[inde].inde.b].u * scau;
			float p3x = vertList[polyList[inde].inde.c].u * scau;
			float p1y = vertList[polyList[inde].inde.a].v * scav;
			float p2y = vertList[polyList[inde].inde.b].v * scav;
			float p3y = vertList[polyList[inde].inde.c].v * scav;
			float p1w = vertList[polyList[inde].inde.a].w;
			float p2w = vertList[polyList[inde].inde.b].w;
			float p3w = vertList[polyList[inde].inde.c].w;
			if (p1w < clipStar || p1w > clipEndi) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw && (p2w < clipStar || p2w > clipEndi)) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw && (p3w < clipStar || p3w > clipEndi)) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw) {
				glColor3f(r, g, b); glVertex3f(p1x, p1y, 0.0);
				glColor3f(r, g, b); glVertex3f(p2x, p2y, 0.0);
				glColor3f(r, g, b); glVertex3f(p3x, p3y, 0.0);
			}
		}
		polyList[inde].draw = true;
	}
	ObjeDyna operator = (ObjeInit righ) {
		ObjeDyna retu;
		name = righ.name;
		loca = righ.loca;
		scal = righ.scal;
		rota = righ.rota;
		vertList = righ.vertList;
		polyList = righ.polyList;
		return retu;
	}
};
	
class ObjeStat {
	public:
		// object id
		unsigned int iden = 0;
		std::string name = "";
		std::vector<Vert> vertList;
		std::vector<Poly> polyList;
	void VertProc(Came came) {
		Vec3 vectVert;
		float w = 0.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			// get vector from subscreen center to vert
			vectVert.x = vertList[a].x - came.loca.x;
			vectVert.y = vertList[a].y - came.loca.y;
			vectVert.z = vertList[a].z - came.loca.z;
			w = came.w.x * vectVert.x + came.w.y * vectVert.y + came.w.z * vectVert.z;
			vertList[a].w = w;
			if (w > came.clip && w < came.rang) {
				// get u and v components
				vertList[a].u = (came.u.x * vectVert.x + came.u.y * vectVert.y + came.u.z * vectVert.z) / w;
				vertList[a].v = (came.v.x * vectVert.x + came.v.y * vectVert.y + came.v.z * vectVert.z) / w;
			}
		}
	}
	void PolyAppe(unsigned int inde, float clipStar, float clipEndi, unsigned int widt, unsigned int heig) {
		float scau = 1.0;
		float scav = 1.0;
		if (widt > heig) {
			scav = (float)widt / (float)heig;
		}
		else {
			scau = (float)heig / (float)widt;
		}
		if (polyList[inde].draw) {
			float r = polyList[inde].colo.x;
			float g = polyList[inde].colo.y;
			float b = polyList[inde].colo.z;
			float p1x = vertList[polyList[inde].inde.a].u * scau;
			float p2x = vertList[polyList[inde].inde.b].u * scau;
			float p3x = vertList[polyList[inde].inde.c].u * scau;
			float p1y = vertList[polyList[inde].inde.a].v * scav;
			float p2y = vertList[polyList[inde].inde.b].v * scav;
			float p3y = vertList[polyList[inde].inde.c].v * scav;
			float p1w = vertList[polyList[inde].inde.a].w;
			float p2w = vertList[polyList[inde].inde.b].w;
			float p3w = vertList[polyList[inde].inde.c].w;
			if (p1w < clipStar || p1w > clipEndi) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw && (p2w < clipStar || p2w > clipEndi)) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw && (p3w < clipStar || p3w > clipEndi)) {
				polyList[inde].draw = false;
			}
			if (polyList[inde].draw) {
				glColor3f(r, g, b); glVertex3f(p1x, p1y, 0.0);
				glColor3f(r, g, b); glVertex3f(p2x, p2y, 0.0);
				glColor3f(r, g, b); glVertex3f(p3x, p3y, 0.0);
			}
		}
		polyList[inde].draw = true;
	}
	ObjeStat operator = (ObjeInit righ) {
		ObjeStat retu;
		name = righ.name;
		vertList = righ.vertList;
		polyList = righ.polyList;
		return retu;
	}
};
