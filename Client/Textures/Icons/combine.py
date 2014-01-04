import Image, ImageDraw, os

effects =["cancel","Cargo","CreateLoadOut","ok"]

i = 0


im = Image.open("0001.png")
im = im.resize((1024,1024))



hight = 0

f = open("cords.txt", 'w')

i = 0
k = 0
idc = 0
for j in effects:
	i += 1
	idc += 1

	s = "" + j + ".png"
	sov = ""
	
	pasteim = Image.open(s)
	size = pasteim.size
	pasteimow = Image.open(s)
	if(not j.find("Ships")):
		pasteimow = Image.open(sov)
	size = pasteimow.size
	
	if (i == 7):
		i = 1
		k += 1

	im.paste(pasteim,(150*(i-1),hight + (150*k)))

	f.write("case Icontex::" + str(j) + ":{\n")
	f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::IconSheet]);\n")
	f.write("\tuvx1 = "+ str(150 * (i-1)) + ";\n")
	f.write("\tuvy1 = "+ str(150 * k) + ";\n")
	f.write("\twight = "+ str(size[0]) + ";\n")
	f.write("\thight = "+ str(size[1]) + ";\n")
	f.write("\tbreak;\n")
	f.write("}\n")


hight += size[1]

# write to stdout
im.save("iconsheet.png", "PNG")



