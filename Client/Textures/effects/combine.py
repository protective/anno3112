import Image, ImageDraw, os, math

effects =["eks1","eks2","eks3","eks4","eks5","eks6","eks4l","eks5l","eks6l","eks7l","eksshc1","eksshc2","eksshc3","eksshc4","eksshc5","eksshc6","eksshc7","eksshc4l","eksshc5l","eksshc6l","eksshc7l","LaserTail1","MissileTail1","eksship1","plasma1"]

maxline = 0
maxhigth = 0
im = Image.open("0001.png")
im2 = Image.open("0001.png")
f = open("cords.txt", 'w')
g = open("tick.txt", 'w')

im = im.resize((1024,1024))
im2 = im2.resize((1024,1024))
hight = 0
hight2 = 0
for ef in effects:
	filelist = os.listdir("./"+ef)
	i = 1
	while (True):
		s = "%04d" % i  + ".png"
		if not (s in filelist):
			break
		i += 1


	for j in range(1,i):
		s = "%04d" % j  + ".png"
		pasteim = Image.open(ef + "/" + s)
		size = pasteim.size
		if(size[1] > 50):
			maxline = int(round(math.floor(1024/size[1]),0))
			maxhight = int(math.ceil(i / maxline))
		
		if(size[1] > 50):
			im2.paste(pasteim,(size[0]*(j%(maxline+1)-1),size[1]*(int(math.floor(j/(maxline+1))))))
		else:
			im.paste(pasteim,(size[0]*(j-1),hight))

	f.write("case ParticalTex::" + ef + ":{\n")
	if(size[1] > 50):
		f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::EffectSheet2]);\n")
	else:
		f.write("\tglBindTexture( GL_TEXTURE_2D, textures[Textures::EffectSheet]);\n")
	
	
	if (size[1] > 50):
		for tempi in range(0,maxhight):
			f.write("\tif(this->_tick<" + str(maxline*(tempi+1)) + "){\n")
			f.write("\t\tuvx1 = "+ str(size[0]) +" * (this->_tick - "+ str(maxline*tempi)+ ");\n")
			f.write("\t\tuvy1 = "+ str(hight2) +";\n")
			f.write("\t\tsize2 = "+ str(size[1]) + ";\n")
			f.write("\t\tbreak;\n")
			f.write("\t}\n")
			hight2 += size[1]
	else:
		f.write("\tuvx1 = "+ str(size[0]) +" * this->_tick;\n")
		f.write("\tuvy1 = "+ str(hight) +";\n")
		f.write("\tsize2 = "+ str(size[1]) + ";\n")
		f.write("\tbreak;\n")

	
	f.write("}\n")
	
	g.write("\t\tcase ParticalTex::" + ef + ":{\n")
	g.write("\t\t\tthis->_tickmin = 0;")
	g.write("this->_tickmax = "+ str(i-1) +";")
	g.write("break;")
	g.write("}\n")
	if(size[1] <= 50):
		hight += size[1]

		

# write to stdout
im.save("effectssheet.png", "PNG")
im2.save("effectssheet2.png", "PNG")

















