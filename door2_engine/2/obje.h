
/*
 * structures for stationary game classes
 * object and camera classes
 * 
 */

#include <iostream>
#include <vector>
#include <GL/gl.h>

#ifndef MATH_H
#define MATH_H
#include "Math.h"
#endif
#ifndef GRAP_H
#define GRAP_H
#include "grap.h"
#endif

struct Vec3Stat {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
};

// TODO: does this do anything
std::ostream & operator << (std::ostream & outp, Vec3Stat & righ) {
	outp << "(" << righ.x << ", " << righ.y << ", " << righ.z << ")";
	return outp;
}

struct Int3Stat {
	int a = 0;
	int b = 0;
	int c = 0;
};

struct VertStat {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float u = 0.0;
	float v = 0.0;
	float w = 0.0;
};

struct PolyStat {
	// 3 vertex indices that make up a polygon
	Int3 inde;
	// x y z local location of polygon centers
	Vec3Stat cent;
	// x y z that points in the direction of the face angle
	Vec3Stat norm;
	// r g b
	Vec3Stat colo;
	// set to false to stop the polygon from being drawn
	bool draw = true;
};

class Came {
	public:
		Vec3 loca;
		Vec3 u, v, w;
		float rang = 1000.0;
		float clip = 0.1;
		Came() {
			u.x = 1.0;
			w.y = 1.0;
			v.z = 1.0;
		}
};

class ObjeInit {
	public:
		// object id
		unsigned int iden = 0;
		std::string name = "";
		Vec3 loca;
		Vec3 scal;
		Vec3 rota;
		// is the object static or dynamic. static objects dont move. their global vertex locations are precomputed
		bool stat = false;
		std::vector<Vert> vertList;
		std::vector<Poly> polyList;
	void ApplRota() {
		Vec3 x, y, z;
		x.x = 1.0;
		y.y = 1.0;
		z.z = 1.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			vertList[a].Quat(rota.x, x);
			vertList[a].Quat(rota.y, y);
			vertList[a].Quat(rota.z, z);
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			polyList[a].cent.Quat(rota.x, x);
			polyList[a].cent.Quat(rota.y, y);
			polyList[a].cent.Quat(rota.z, z);
			polyList[a].norm.Quat(rota.x, x);
			polyList[a].norm.Quat(rota.y, y);
			polyList[a].norm.Quat(rota.z, z);
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
		Vec3 vectVert;
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
		Vec3 loca;
		Vec3 scal;
		Vec3 rota;
		std::vector<Vert> vertList;
		std::vector<Poly> polyList;
	void ApplRota() {
		Vec3 x, y, z;
		x.x = 1.0;
		y.y = 1.0;
		z.z = 1.0;
		for (unsigned int a = 0; a < vertList.size(); a++) {
			// TODO
			vertList[a].Quat(rota.x, x);
			vertList[a].Quat(rota.y, y);
			vertList[a].Quat(rota.z, z);
		}
		for (unsigned int a = 0; a < polyList.size(); a++) {
			// TODO
			polyList[a].cent.Quat(rota.x, x);
			polyList[a].cent.Quat(rota.y, y);
			polyList[a].cent.Quat(rota.z, z);
			polyList[a].norm.Quat(rota.x, x);
			polyList[a].norm.Quat(rota.y, y);
			polyList[a].norm.Quat(rota.z, z);
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
		Vec3 vectVert;
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
	void operator = (ObjeInit righ) {
		iden = righ.iden;
		name = righ.name;
		loca = righ.loca;
		scal = righ.scal;
		rota = righ.rota;
		vertList = righ.vertList;
		polyList = righ.polyList;
	}
};
	
class ObjeStat {
	public:
		// object id
		unsigned int iden = 0;
		std::string name = "";
		std::vector<VertStat> vertList;
		std::vector<PolyStat> polyList;
	void VertProc(Came came) {
		Vec3Stat vectVert;
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
	void BackCull(Came came) {
		for (unsigned int a = 0; a < polyList.size(); a++) {
			Vec3Stat vec3Stat;
			int inde = polyList[a].inde.a;
			vec3Stat.x = came.loca.x - vertList[inde].x;
			vec3Stat.y = came.loca.y - vertList[inde].y;
			vec3Stat.z = came.loca.z - vertList[inde].z;
			float dot_ = vec3Stat.x * polyList[a].norm.x + vec3Stat.y * polyList[a].norm.y + vec3Stat.z * polyList[a].norm.z;
			if (dot_ < 0.0) {
				polyList[a].draw = false;
			}
			else {
				polyList[a].draw = true;
			}
		}
	}
	void operator = (ObjeInit righ) {
		iden = righ.iden;
		name = righ.name;
		VertStat vert;
		for (unsigned int a = 0; a < righ.vertList.size(); a++) {
			vert.x = righ.vertList[a][0];
			vert.y = righ.vertList[a][1];
			vert.z = righ.vertList[a][2];
			vert.u = righ.vertList[a][3];
			vert.v = righ.vertList[a][4];
			vert.w = righ.vertList[a][5];
			vertList.push_back(vert);
		}
		PolyStat poly;
		for (unsigned int a = 0; a < righ.polyList.size(); a++) {
			poly.inde.a = righ.polyList[a].inde[0];
			poly.inde.b = righ.polyList[a].inde[1];
			poly.inde.c = righ.polyList[a].inde[2];
			poly.cent.x = righ.polyList[a].cent[0];
			poly.cent.y = righ.polyList[a].cent[1];
			poly.cent.z = righ.polyList[a].cent[2];
			poly.norm.x = righ.polyList[a].norm[0];
			poly.norm.y = righ.polyList[a].norm[1];
			poly.norm.z = righ.polyList[a].norm[2];
			poly.colo.x = righ.polyList[a].colo[0];
			poly.colo.y = righ.polyList[a].colo[1];
			poly.colo.z = righ.polyList[a].colo[2];
			poly.draw = righ.polyList[a].draw;
			polyList.push_back(poly);
		}
	}
};
