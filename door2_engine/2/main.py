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

	import bpy

	print()

	objeList = True
	#objeList = False
	if objeList:

		statList = []
		for obje in bpy.context.scene.objects:
			if obje.type == 'MESH':
				statList.append(obje.name)

		dynaList = []
		for obje in bpy.context.scene.objects:
			if obje.type == 'MESH':
				if (obje.name in statList) == False:
					dynaList.append(obje.name)

	expo = True
	#expo = False
	if expo:

		Expo(statList, dynaList, readOrde = False)

	init = True
	#init = False
	if init:

		os.system("make -B init; ./init")

	expo = True
	#expo = False
	if expo:

		Expo(statList, dynaList)


def Expo(statList, dynaList, readOrde = True):

	import bpy

	writ = True
	#writ = False

	objeList = []
	for obje in statList:
		objeList.append(obje)
	for obje in dynaList:
		objeList.append(obje)

	#print("o", objeList)

	fileList = []
	# TODO
	fileList.append("#include \"../obje.h\"")
	fileList.append("")
	fileList.append("void Load(std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false) {")
	fileList.append("")
	fileList.append("\tObjeInit objeInit;")
	fileList.append("\tVert vert;")
	fileList.append("\tPoly poly;")
	fileList.append("\tunsigned int o = 0;")
	fileList.append("")

	coun = 0

	for obje in objeList:

		name = obje
		Blen.Sele(name)
		obje = bpy.context.object
		rota = Blen.RotaRead()
		scal = Blen.ScalRead()
		loca = Blen.LocaRead()
		stat = "false"
		if (name in statList):
			stat = "true"
		Blen.Tria()
		vertList = Blen.VertList()
		pol_List = Blen.PolyList()
		nor_List = Blen.NormList()
		col_List = []
		for poly in obje.data.polygons:
			mate_inde = poly.material_index
			if mate_inde >= 0 and len(obje.material_slots) > mate_inde:
				col_List.append(tuple(obje.material_slots[mate_inde].material.diffuse_color))

		if readOrde:

			line = Pyth.FileTo__Line("obje/orde")
			line = line[coun]
			line = line.split(" ")
			polyList = []
			normList = []
			coloList = []
			for a in range(len(line)):
				polyList.append(pol_List[int(line[a])])
				normList.append(nor_List[int(line[a])])
				coloList.append(col_List[int(line[a])])
		else:
			polyList = pol_List
			normList = nor_List
			coloList = col_List

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
			fileList.append("\tobjeInit.polyList.push_back(poly);")
		# ***
		for b in range(len(coloList)):
		# ***
			fileList.append("\tobjeInit.polyList[" + str(b) + "].colo.x = " + str(coloList[b][0]) + ";")
			fileList.append("\tobjeInit.polyList[" + str(b) + "].colo.y = " + str(coloList[b][1]) + ";")
			fileList.append("\tobjeInit.polyList[" + str(b) + "].colo.z = " + str(coloList[b][2]) + ";")
		fileList.append("\tobjeInitList.push_back(objeInit);")
		fileList.append("\to++;")
		fileList.append("")

		coun += 1

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

	if writ == True:
		Pyth.LineTo__File(fileList, "obje/obje_data.h")

main()
