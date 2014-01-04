import Image, ImageDraw, os

effects =["Ships/Frig","Ships/LightCarrier","Ships/AC","Ships/HAC","Ships/Freighter1","Ships/BattleShip2","Ships/BattleShip1","Ships/BattleCruiser","Ships/Station1","Asteroids/A1", "Asteroids/NephriteRoid", "Asteroids/CerussiteRoid", "Asteroids/NeptuniteRoid","Asteroids/HedenbergiteRoid","Ships/DD"]

f = open("../../../Server/database/objtexname.txt", 'w')

i = 0
for j in effects:
	if(not i):
		f.write("if (str.find(\"" + j + "\")!= string::npos)\n")
		f.write("return " + str(i+1) + ";\n")
	else:
		f.write("else if (str.find(\"" + j + "\")!= string::npos)\n")
		f.write("return " + str(i+1) + ";\n")
	i += 1


im = Image.open("0001.png")
im = im.resize((1024,1024))

imow = Image.open("0001.png")
imow = imow.resize((1024,1024))


hight = 0

f = open("cords.txt", 'w')

g = open("Owcords.txt", 'w')

i = -1
k = 0
idc = 0
for j in effects:
	i += 1
	idc += 1

	if (i == 5):
		i = 0
		k += 1

	s = "" + j + "/k0001.png"
	sov = ""
	if(not j.find("Ships")):
		sov = "" + j + "/Overview0001.png"
	
	pasteim = Image.open(s)
	size = pasteim.size
	pasteimow = Image.open(s)
	if(not j.find("Ships")):
		pasteimow = Image.open(sov)
	size = pasteimow.size
	


	im.paste(pasteim,(150*(i),(150*k)))
	if(not j.find("Ships")):
		imow.paste(pasteimow,(200*(i),(200*k)))
		

	f.write("case " + str(idc) + ":{\n")
	f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::ObjSheet]);\n")
	f.write("\tuvx1 = "+ str(150 * (i)) + ";\n")
	f.write("\tuvy1 = "+ str(150 * k) + ";\n")
	f.write("\tbreak;\n")
	f.write("}\n")

	g.write("case " + str(idc) + ":{\n")
	g.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::OwObjSheet]);\n")
	g.write("\tuvx1 = "+ str(200 * (i)) + ";\n")
	g.write("\tuvy1 = "+ str(200 * k) + ";\n")
	g.write("\tbreak;\n")
	g.write("}\n")



hight += size[1]

# write to stdout
im.save("objsheet.png", "PNG")
imow.save("owobjsheet.png","PNG")


