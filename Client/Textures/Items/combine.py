import Image, ImageDraw, os

effects =["Weapons/IonGun","Weapons/GLaserI","Weapons/LaserI","Weapons/FusionCannon","Weapons/Missile1","Weapons/PlasmaGun","Weapons/RailGunI","Weapons/Torp1","Shields/DeflectorBoost1","Shields/Shield1","Ore/Veldspar","Minerals/Tritanium","Minerals/Pyrite","Minerals/Denite","Minerals/Andorite","Minerals/Morganite","Ships/HAC","Ships/AC", "Ships/BattleCruiser", "Ships/BattleShip1","Ships/BattleShip2","Ships/Freighter1","Ships/LightCarrier","Engines/Engine1","Electronic/HeatSink","Electronic/Scanner","Electronic/TargetComputer","Mechanical/Reactor","Armor/ArmorRep","Ships/DD"]

f = open("../../../Server/database/itemtexname.txt", 'w')

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
hight = 0

f = open("subcords.txt", 'w')

i = -1
k = 0
idc = 0
for j in effects:
	idc += 1

	if(os.path.exists("Items/" + j + "/Fititempic0001.png")):
		i += 1
		s = "Items/" + j + "/Fititempic0001.png"
		pasteim = Image.open(s)
		size = pasteim.size

		if (i == 20):
			i = 0
			k += 1


		im.paste(pasteim,(size[0]*(i),(size[1]*k)))

		f.write("case " + str(idc) + ":{\n")
		f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::SubItemSheet]);\n")
		f.write("\tuvx1 = "+ str(size[0] * (i)) + ";\n")
		f.write("\tuvy1 = "+ str(size[1] * k) + ";\n")
		f.write("\tbreak;\n")
		f.write("}\n")

hight += size[1]

# write to stdout
im.save("subitemsheet.png", "PNG")






im = Image.open("0001.png")

im = im.resize((1024,1024))
hight = 0

f = open("itemcords.txt", 'w')

i = -1
k = 0
idc = 0
for j in effects:
	i += 1
	idc += 1
	s = "Items/" + j + "/itempic0001.png"
	pasteim = Image.open(s)
	size = pasteim.size
	if (i == 20):
		i = 0
		k += 1

	im.paste(pasteim,(40*(i), (40*k)))


	f.write("case " + str(idc) + ":{\n")
	f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::ItemSheet]);\n")
	f.write("\tuvx1 = "+ str(40 * (i)) + ";\n")
	f.write("\tuvy1 = "+ str(40 * k) + ";\n")
	f.write("\tbreak;\n")
	f.write("}\n")



hight += size[1]

# write to stdout
im.save("itemsheet.png", "PNG")










