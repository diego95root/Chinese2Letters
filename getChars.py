# -*- coding: UTF-8 -*-

import requests, os
from PIL import Image
from PIL import ImageFont, ImageDraw
import shutil

def draw(char, name):
     image=Image.new("RGB",[50,50],color=(255,255,255,255))
     draw = ImageDraw.Draw(image)
     a = char
     font=ImageFont.truetype("/Library/Fonts/Arial Unicode.ttf",34)
     draw.text((8, 2), a, font=font, fill=(0,0,0,255))
     image.save(name+".png")

def getChars(number):
	chars = []

	for i in range(1,1+(number/100)):
		c = requests.get("http://hanzidb.org/character-list/by-frequency?page={}".format(str(i))).content
		all = c.split('href="/character/')
		for i in range(1, len(all)-1):
			element = []
			if i%2 == 1:
				element.append(all[i][0:3])
				element.append(all[i+1].split("</td><td>")[1][:2])
				chars.append(element)

	unicodes = [[i[0], i[0].decode("utf8"),i[1]] for i in chars]

	return unicodes


if __name__ == "__main__":
    if os.path.exists("chars"):
        shutil.rmtree('chars')
    os.mkdir("chars")
    os.chdir("chars")

    countDict = {}
    final = getChars(300)

    for each in xrange(len(final)):
        #print "(" + repr(final[each][1])[4:-1] + ", " + final[each][1] + ", " + final[each][2] + ")"
        strokes = int(final[each][2])
        draw(final[each][1], repr(final[each][1])[4:-1] + "_" + str(strokes).zfill(2))
        if strokes in countDict:
            countDict[strokes] += 1
        else:
            countDict[strokes] = 1

    print "Obtained {} characters".format(len(final))
    print "Data obtained:"
    print countDict

    for strokes, count in sorted(countDict.items()):
        print "{:02d} strokes: {}".format(int(strokes), count)
