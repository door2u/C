class ObjeInit {
	void Load(std::string dire = "obje/") {
		std::ifstream file;
		std::string var1;
		std::string var2;
		std::string var3;
		std::string buff;
		file.open(dire + "obje");
		if (file.is_open()) {
			unsigned int list = 0;
			file >> name;
			list++;
			while (list < 4) {
				file >> var1; file >> var2; file >> var3;
				Vec3Clas floa;
				floa = {std::stof(var1), std::stof(var2), std::stof(var3)};
				if (list == 1) {
					rota = {floa[0], floa[1], floa[2]};
				}
				else if (list == 2) {
					scal = {floa[0], floa[1], floa[2]};
				}
				else if (list == 3) {
					loca = {floa[0], floa[1], floa[2]};
				}
				list++;
			}
			file >> var1;
			if (var1 == "true") {
				stat = true;
			}
			else if (var1 == "false") {
				stat = false;
			}
			file.close();
		}
		file.open(dire + "vert");
		if (file.is_open()) {
			while (!file.eof()) {
				file >> var1; file >> var2; file >> var3;
				Vert floa = {std::stof(var1), std::stof(var2), std::stof(var3)};
				vertList.push_back(floa);
			}
			// pop end
			vertList.pop_back();
			file.close();
		}
		// load norms
		file.open(dire + "norm");
		if (file.is_open()) {
			while (!file.eof()) {
				file >> var1; file >> var2; file >> var3;
				Vec3Clas vari;
				vari = {std::stof(var1), std::stof(var2), std::stof(var3)};
				Poly norm;
				norm.norm = vari;
				polyList.push_back(norm);
			}
			polyList.pop_back();
			file.close();
		}
		file.open(dire + "poly");
		if (file.is_open()) {
			unsigned int line = 0;
			while (!file.eof()) {
				file >> var1; file >> var2; file >> var3;
				Int3 vari;
				vari = {std::stoi(var1), std::stoi(var2), std::stoi(var3)};
				if (line <= polyList.size() - 1) {
					polyList[line].inde = vari;
				}
				line++;
			}
			file.close();
		}
		file.open(dire + "colo");
		if (file.is_open()) {
			unsigned int line = 0;
			while (!file.eof()) {
				file >> var1; file >> var2; file >> var3;
				Vec3Clas vari;
				vari = {std::stof(var1), std::stof(var2), std::stof(var3)};
				if (line <= polyList.size() - 1) {
					polyList[line].colo = vari;
				}
				line++;
			}
			file.close();
		}
	}
}
