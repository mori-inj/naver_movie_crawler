#-*- coding: utf-8 -*-
import sys
import re

f = open(sys.argv[1],'r')
lines = f.readlines()
for line in lines:
	s = line.find("출연 :")
	if s != -1:
		tmp = line[s+8:]
		print str(sys.argv[2]) + " : " + re.sub(r'\<.*?\>','',tmp)
		break
