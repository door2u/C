import importlib.util
import os

spec = importlib.util.spec_from_file_location("Modu", os.path.expanduser("~") + os.sep + "Documents" + os.sep + "prog" + os.sep + "Modu" + os.sep + "Modu.py")
Modu = importlib.util.module_from_spec(spec)
spec.loader.exec_module(Modu)

Pyth = Modu.Pyth
Math = Modu.Math
Blen = Modu.Blen
BlenGame = Modu.BlenGame
Gene = Modu.Gene

def main():
	statList = ["cube"]
	writ = True
	#writ = False
	###############################################
	import bpy
	fileList = []
	fileList.append("#include \"obje.h\"")
	fileList.append("")
	fileList.append("void Load(std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false) {")
	fileList.append("")
	fileList.append("\tObjeInit objeInit;")
	fileList.append("\tVert vert;")
	fileList.append("\tPoly poly;")
	fileList.append("\tunsigned int o = 0;")
	fileList.append("")
	for obje in bpy.context.scene.objects:
		if obje.type == 'MESH':
			name = obje.name
			Blen.Sele(name)
			rota = Blen.RotaRead()
			scal = Blen.ScalRead()
			loca = Blen.LocaRead()
			stat = "false"
			if (name in statList):
				stat = "true"
			Blen.Tria()
			vertList = Blen.VertList()
			polyList = Blen.PolyList()
			normList = Blen.NormList()
			coloList = []
			for poly in obje.data.polygons:
				mate_inde = poly.material_index
				if mate_inde >= 0 and len(obje.material_slots) > mate_inde:
					coloList.append(tuple(obje.material_slots[mate_inde].material.diffuse_color))
			fileList.append("\tobjeInit.iden = o;")
			fileList.append("\tobjeInit.name = \"" + name + "\";")
			fileList.append("\tobjeInit.rota.x = " + str(rota[0]) + ";")
			fileList.append("\tobjeInit.rota.y = " + str(rota[1]) + ";")
			fileList.append("\tobjeInit.rota.z = " + str(rota[2]) + ";")
			fileList.append("\tobjeInit.scal.x = " + str(scal[0]) + ";")
			fileList.append("\tobjeInit.scal.y = " + str(scal[1]) + ";")
			fileList.append("\tobjeInit.scal.z = " + str(scal[2]) + ";")
			fileList.append("\tobjeInit.loca.x = " + str(loca[0]) + ";")
			fileList.append("\tobjeInit.loca.y = " + str(loca[1]) + ";")
			fileList.append("\tobjeInit.loca.z = " + str(loca[2]) + ";")
			fileList.append("\tobjeInit.stat = " + stat + ";")
			for b in range(len(vertList)):
				fileList.append("\tvert.x = " + str(vertList[b][0]) + ";")
				fileList.append("\tvert.y = " + str(vertList[b][1]) + ";")
				fileList.append("\tvert.z = " + str(vertList[b][2]) + ";")
				fileList.append("\tobjeInit.vertList.push_back(vert);")
			for b in range(len(polyList)):
				fileList.append("\tpoly.inde.a = " + str(polyList[b][0]) + ";")
				fileList.append("\tpoly.inde.b = " + str(polyList[b][1]) + ";")
				fileList.append("\tpoly.inde.c = " + str(polyList[b][2]) + ";")
				fileList.append("\tpoly.norm.x = " + str(normList[b][0]) + ";")
				fileList.append("\tpoly.norm.y = " + str(normList[b][1]) + ";")
				fileList.append("\tpoly.norm.z = " + str(normList[b][2]) + ";")
				fileList.append("\tpoly.colo.x = " + str(coloList[b][0]) + ";")
				fileList.append("\tpoly.colo.y = " + str(coloList[b][1]) + ";")
				fileList.append("\tpoly.colo.z = " + str(coloList[b][2]) + ";")
				fileList.append("\tobjeInit.polyList.push_back(poly);")
			fileList.append("\tobjeInitList.push_back(objeInit);")
			fileList.append("\to++;")
			fileList.append("")
	fileList.append("\tfor (unsigned int a = 0; a < objeInitList.size(); a++) {")
	fileList.append("\t\tobjeInitList[a].Init(came, true, prin);")
	fileList.append("\t\tif (objeInitList[a].stat == false) {")
	fileList.append("\t\t\tObjeDyna objeDyna;")
	fileList.append("\t\t\tobjeDyna = objeInitList[a];")
	fileList.append("\t\t\tobjeDynaList.push_back(objeDyna);")
	fileList.append("\t\t}")
	fileList.append("\t\telse if (objeInitList[a].stat == true) {")
	fileList.append("\t\t\tObjeStat objeStat;")
	fileList.append("\t\t\tobjeStat = objeInitList[a];")
	fileList.append("\t\t\tobjeStatList.push_back(objeStat);")
	fileList.append("\t\t}")
	fileList.append("\t}")
	fileList.append("")
	fileList.append("}")
	#for line in fileList:
	#	print(line)
	if writ == True:
		Pyth.LineTo__File(fileList, "obje_data.h")

main()
