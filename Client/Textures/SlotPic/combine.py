import Image, ImageDraw, os

effects =["Armo","Shie","Elec","Mech","MeEl","ShAr","MwSh","MwEl","ShEl","Engi","Figh","Lw","Mw","Hw","Lfac","Mfac","Hfac","Mini"]



im = Image.open("0001.png")

im = im.resize((256,256))
hight = 0

f = open("cords.txt", 'w')

i = 0
k = 0
idc = 0
for j in effects:
	i += 1
	idc += 1
	s = j + ".png"
	pasteim = Image.open(s)
	size = pasteim.size
	
	im.paste(pasteim,(size[0]*(i-1),hight + (size[1]*k)))


	f.write("case " + str(idc) + ":{\n")
	f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::SlotSheet]);\n")
	f.write("\tuvx1 = "+ str(size[0] * (i-1)) + ";\n")
	f.write("\tuvy1 = "+ str(size[1] * k) + ";\n")
	f.write("\tbreak;\n")
	f.write("}\n")

	if (i == 5):
		i = 0
		k += 1

hight += size[1]
f.close()
# write to stdout
im.save("slotsheet.png", "PNG")

















