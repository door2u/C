
void Load(std::string dire, std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false);

Load(dire, objeInitList, objeDynaList, objeStatList, came, prin);

void Load(std::string dire, std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false) {
	struct dirent *d;
	DIR *dir_;
	dir_ = opendir(dire.c_str());
	if (dir_ != NULL) {
		for (d = readdir(dir_); d != NULL; d = readdir(dir_)) {
			unsigned char type = d->d_type;
			std::string name = d->d_name;
			if (type == 4 && name != "." && name != "..") {
				ObjeInit temp;
				temp.iden = (unsigned int)std::stoi(name);
				objeInitList.push_back(temp);
			}
		}
	}
	closedir(dir_);
	std::stringstream conv;
	std::string iden;
	for (unsigned int a = 0; a < objeInitList.size(); a++)
	{
		conv << objeInitList[a].iden;
		conv >> iden;
		objeInitList[a].Load(dire + iden + "/");
		objeInitList[a].Init(came, true, prin);
		if (objeInitList[a].stat == false) {
			ObjeDyna objeDyna;
			objeDyna = objeInitList[a];
			objeDynaList.push_back(objeDyna);
		}
		else if (objeInitList[a].stat == true) {
			ObjeStat objeStat;
			objeStat = objeInitList[a];
			objeStatList.push_back(objeStat);
		}
	}
}
