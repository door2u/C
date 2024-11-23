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
	fold = "obje/"
	statList = ["cube"]
	writ = True
	#writ = False
	###############################################
	import bpy
	# check if object folder exists
	exis = os.path.exists(fold)
	if exis == False:
		os.makedirs(fold)
	# first object will be referred to as "0", second as "1", etc
	iden = 0
	a = 0
	while a < len(bpy.context.scene.objects):
		obje = bpy.context.scene.objects[a]
		if obje.type == 'MESH':
			name = obje.name
			dire = fold + str(iden) + "/"
			# make this object folder inside the main obje folder
			exis = os.path.exists(dire)
			if exis == False:
				os.makedirs(dire)
			Blen.Sele(name)
			rota = Blen.RotaRead()
			rota = Pyth.TuplListExpo([rota])
			rota = Stri(rota)
			rota = rota[0]
			scal = Blen.ScalRead()
			scal = Pyth.TuplListExpo([scal])
			scal = Stri(scal)
			scal = scal[0]
			loca = Blen.LocaRead()
			loca = Pyth.TuplListExpo([loca])
			loca = Stri(loca)
			loca = loca[0]
			fileList = []
			fileList.append(name)
			fileList.append(rota)
			fileList.append(scal)
			fileList.append(loca)
			stat = "false"
			for b in range(len(statList)):
				if name == statList[b]:
					stat = "true"
			fileList.append(stat)
			# triangulate the polygons of the object
			Blen.Tria()
			vertList = Blen.VertList()
			polyList = Blen.PolyList()
			normList = Blen.NormList()
			# color list
			coloList = []
			b = 0
			while b < len(obje.data.polygons):
				mate_inde = obje.data.polygons[b].material_index
				if len(obje.material_slots) > 0:
					coloList.append(tuple(obje.material_slots[mate_inde].material.diffuse_color))
				b += 1
			vertList = Pyth.TuplListExpo(vertList)
			polyList = Pyth.TuplListExpo(polyList)
			normList = Pyth.TuplListExpo(normList)
			coloList = Pyth.TuplListExpo(coloList)
			vertList = Stri(vertList)
			polyList = Stri(polyList)
			normList = Stri(normList)
			coloList = Stri(coloList)
			if writ == True:
				Pyth.LineTo__File(fileList, dire + "obje")
				Pyth.LineTo__File(vertList, dire + "vert")
				Pyth.LineTo__File(polyList, dire + "poly")
				Pyth.LineTo__File(normList, dire + "norm")
				Pyth.LineTo__File(coloList, dire + "colo")
				iden += 1
		a += 1

# strip. remove '(' ')' '[' ']' ','
def Stri(list):
	retu = []
	a = 0
	while a < len(list):
		stri = ""
		for b in range(len(list[a])):
			if list[a][b] != '(' and list[a][b] != ')' and list[a][b] != '[' and list[a][b] != ']' and list[a][b] != ',':
				stri += list[a][b]
		retu.append(stri)
		a += 1
	return retu					

main()
