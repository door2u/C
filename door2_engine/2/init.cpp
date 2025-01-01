#include <iostream>
#include <fstream>

#include "obje/obje_data.h"

#ifndef GRAP_H
#define GRAP_H
#include "grap.h"
#endif

bool Fron(std::vector<VertStat> vertLis1, std::vector<VertStat> vertLis2) {
	std::vector<float> VectAver(std::vector<std::vector<float>> vectList);
	int PlanInte(Plan *pla1, Plan *pla2);
	std::vector<float> Vect(std::vector<float> vec1, std::vector<float> vec2);
	std::vector<float> VectCros3d__(std::vector<float> vec1, std::vector<float> vec2);
	bool retu = true;
	Plan pla1;
	Plan pla2;
	std::vector<std::vector<float>> vertList;
	std::vector<float> cent;
	Vec3 norm;
	std::vector<float> nor_;
	std::vector<float> vect;
	float dot_ = 0.0;
	// get infinite planes
	vertList.push_back({vertLis1[0].x, vertLis1[0].y, vertLis1[0].z});
	vertList.push_back({vertLis1[1].x, vertLis1[1].y, vertLis1[1].z});
	vertList.push_back({vertLis1[2].x, vertLis1[2].y, vertLis1[2].z});
	
	cent = VectAver(vertList);
	// TODO: maybe make a vector vect class. or a function
	pla1.cent = {cent[0], cent[1], cent[2]};
	vertList[0] = Vect(cent, vertList[0]);
	vertList[1] = Vect(cent, vertList[1]);
	nor_ = VectCros3d__(vertList[0], vertList[1]);
	nor_ = VectNorm(nor_);
	pla1.norm = {nor_[0], nor_[1], nor_[2]};
	
	vertList.clear();
	vertList.push_back({vertLis2[0].x, vertLis2[0].y, vertLis2[0].z});
	vertList.push_back({vertLis2[1].x, vertLis2[1].y, vertLis2[1].z});
	vertList.push_back({vertLis2[2].x, vertLis2[2].y, vertLis2[2].z});
	
	cent = VectAver(vertList);
	pla2.cent = {cent[0], cent[1], cent[2]};
	vertList[0] = Vect(cent, vertList[0]);
	vertList[1] = Vect(cent, vertList[1]);
	nor_ = VectCros3d__(vertList[0], vertList[1]);
	nor_ = VectNorm(nor_);
	pla2.norm = {nor_[0], nor_[1], nor_[2]};
	
	// TODO: consider transforms
	
	// get infinite intersection
	Plan inte = pla1;
	Plan edge = pla2;
	int planInte = PlanInte(&inte, &edge);
	
	if (planInte == 0) {
		// get the side of intersection
		bool same = true;
		// !!! note: edge.cent is actually a normal
		if (edge.cent * edge.norm < 0.0) {
			same = false;
		}
		// if the polys are on the same side, get the front
		if (same) {
			// draw a vector from one triangle to the other, then dot it with the normal
			VertStat ver1;
			VertStat ver2;
			std::vector<float> vec1;
			std::vector<float> vec2;
			for (unsigned int a = 0; a < 3; a++) {
				ver1 = vertLis1[a];
				vec1 = Vect(inte.cent.List(), {ver1.x, ver1.y, ver1.z});
				if (vec1 * edge.cent > 0.0) {
					break;
				}
			}
			for (unsigned int a = 0; a < 3; a++) {
				ver2 = vertLis2[a];
				vec2 = Vect(inte.cent.List(), {ver2.x, ver2.y, ver2.z});
				if (vec2 * edge.norm > 0.0) {
					break;
				}
			}
			vect = Vect({ver1.x, ver1.y, ver1.z}, {ver2.x, ver2.y, ver2.z});
			dot_ = vect * pla1.norm;
			if (dot_ > 0.0) {
				retu = false;
			}
		}
	}
	return retu;
}

int main(int argc, char **argv) {

	// function declarations
		
	void Load(std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false);
	bool Fron(std::vector<VertStat> vertLis1, std::vector<VertStat> vertLis2);

	Came came;
	bool prin = true;
	prin = false;
	std::vector<ObjeInit> objeInitList;
	std::vector<ObjeDyna> objeDynaList;
	std::vector<ObjeStat> objeStatList;
	Load(objeInitList, objeDynaList, objeStatList, came, prin);
	objeInitList.clear();

	std::vector<VertStat> vertLis1;
	std::vector<VertStat> vertLis2;
	bool fron = false;
	long int diff = 0;
	unsigned int temp = 0;
	long int b = 0;
	long int c = 0;

	std::ofstream ord_("obje/orde", std::ios_base::out);

	for (unsigned int a = 0; a < objeStatList.size(); a++) {
		
		std::vector<unsigned int> orde;
		for (unsigned int b = 0; b < objeStatList[a].polyList.size(); b++) {
			orde.push_back(b);
		}

		std::cout << objeStatList[a].polyList.size() << std::endl;
		
		b = 0;
		while ((unsigned int)b < objeStatList[a].polyList.size() - 1) {
			c = b + 1;
			while ((unsigned int)c < objeStatList[a].polyList.size()) {
				
				vertLis1.clear();
				vertLis2.clear();
				
				vertLis1.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[b]].inde.a]);
				vertLis1.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[b]].inde.b]);
				vertLis1.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[b]].inde.c]);
				vertLis2.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[c]].inde.a]);
				vertLis2.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[c]].inde.b]);
				vertLis2.push_back(objeStatList[a].vertList[objeStatList[a].polyList[orde[c]].inde.c]);

				fron = Fron(vertLis1, vertLis2);
								
				if (fron == false) {
					// move c up the poly list until it's in front of b
					diff = c - b;
					for (unsigned int d = 0; d < (unsigned int)diff; d++) {
						temp = orde[b + diff - d];
						orde[b + diff - d] = orde[b + diff - d - 1];
						orde[b + diff - d - 1] = temp;
					}
					std::cout << "b " << b << std::endl;
					b = -1;
					c = -1;
					break;
				}
				c += 1;
			}
			b += 1;
		}
		
		// write the polygon order of this object to the "orde" file
		for (unsigned int d = 0; d < orde.size(); d++) {
			ord_ << orde[d];
			if (d < orde.size() - 1) {
				ord_ << " ";
			}
		}
		ord_ << std::endl;
	
	}
	
	ord_.close();
	
	return 0;

}
