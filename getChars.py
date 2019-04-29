# -*- coding: UTF-8 -*-

import requests, os
from PIL import Image
from PIL import ImageFont, ImageDraw
import shutil

all = [[] for i in range(0,37)]

def draw(char, name):

    image=Image.new("RGB",[500,500],color=(255,255,255,255))
    draw = ImageDraw.Draw(image)
    a = char
    font=ImageFont.truetype("/Library/Fonts/Arial Unicode.ttf",404)
    draw.text((50, -20), a, font=font, fill=(0,0,0,255))
    """
    image=Image.new("RGB",[50,50],color=(255,255,255,255))
    draw = ImageDraw.Draw(image)
    a = char
    font=ImageFont.truetype("/Library/Fonts/Arial Unicode.ttf",34)
    draw.text((8, 2), a, font=font, fill=(0,0,0,255))
    """
    #print name+".png"
    all[int(name[-2:])-1].append(name+".png")
    image.save(name+".png")

def getChars(number):
    chars = []
    for i in range(1,(number/100)+1):
        #print chars
        print "Getting http://hanzidb.org/character-list/by-frequency?page={}".format(str(i))
        c = requests.get("http://hanzidb.org/character-list/by-frequency?page={}".format(str(i))).content
        all = c.split('<tr>')[2:]
        for x in range(0, len(all)):
            element = []
            element.append(all[x].split('href="/character/')[1][0:3])
            element.append(all[x].split("</td><td>")[-4][:2])
            chars.append(element)

    unicodes = [[i[0], i[0].decode("utf8"),i[1]] for i in chars]
    return unicodes


if __name__ == "__main__":
    if os.path.exists("charsX"):
        shutil.rmtree('charsX')
    os.mkdir("charsX")
    os.chdir("charsX")

    countDict = {}
    final = getChars(10000)

    for each in xrange(len(final)):
        char = final[each][1].encode('utf-8')
        bytes = "".join([hex(ord(c))[2:] for c in char])
        print "(" + repr(final[each][1])[4:-1] + ", " + bytes + ", " + final[each][1] + ", " + final[each][2] + ")"
        strokes = int(final[each][2])
        draw(final[each][1], bytes + "_" + str(strokes).zfill(2))
        if strokes in countDict:
            countDict[strokes] += 1
        else:
            countDict[strokes] = 1

    # sort the lists based on the hex number from small to big
    for i in xrange(len(all)):
        li = []
        for x in all[i]:
            li.append(int("0x" + str(x[:6]), 16))
        print [_ for _,x in sorted(zip(all[i],li))]

    print "Obtained {} characters".format(len(final))
    print "Data obtained:"
    print [x for i,x in countDict.iteritems()]

    for strokes, count in sorted(countDict.items()):
        print "{:02d} strokes: {}".format(int(strokes), count)
