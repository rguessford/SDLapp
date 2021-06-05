#!/usr/bin/env python3

# spritesheet manifest generator! for regular spritesheets. 
# x: sprite width
# y: sprite height
# w: spritesheet width
# h: spritesheet height
# f: frame names, as a text file, one line per frame
# example: python ssmfgen.py -x 128 -y 128 -w 4608 -h 1024 -f zombie_0.frames -u https://opengameart.org/content/zombie-sprites

import json
import sys, getopt

def main(argv):
	inputfile = ''
	_x = 0
	_y = 0
	_w = 0
	_h = 0
	url = ""
	try:
		opts, args = getopt.getopt(argv, "x:y:w:h:f:u:")
	except:
		print ("ssmfgen.py x y w h f")
	for opt, arg in opts:
		if opt == "-x":
			_x = int(arg)
		if opt == "-y":
			_y = int(arg)
		if opt == "-w":
			_w = int(arg)
		if opt == "-h":
			_h = int(arg)
		if opt == "-f":
			inputfile = arg
			outputfile = arg.split('.')[0]+".json"
		if opt == "-u":
			url = arg
	framesVal = []

	with open(inputfile) as f:
		frameNames = list(map(lambda s : s.rstrip(), f))

	numLabels = len(frameNames)
	if (numLabels != _w / _x * _h / _y):
		useIndex = True;
		print("numer of labels does not match number of frames. using index as frame name.")
	else: 
		useIndex = False;

	index = 0
	for y in range(0, _h, _y):
		for x in range (0, _w, _x):
			frameVal = {
			"x": x,
			"y": y,
			"w": _x,
			"h": _y
			}
			frameObj = {
			#index out of bounds ahoy
			"filename" : str(index if useIndex else frameNames[index]),
			"frame" : frameVal
			}
			index += 1
			framesVal.append(frameObj)
	metaVal = { "url" : url, 
		"imagepath" : "",
		"json-generator" : "ssmfgen.py" }
	root = {
	"frames" : framesVal,
	"meta" : metaVal
	}

	out = open(outputfile, "w")
	out.write(json.dumps(root, indent=4))

if __name__ == "__main__":
   main(sys.argv[1:])