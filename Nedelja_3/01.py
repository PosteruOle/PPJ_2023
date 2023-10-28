import sys
import re
import os
#import sys, re, os

#print(sys.argv)
if len(sys.argv)<2:
    sys.exit("Nedovoljan broj argumenata!")

#match=re.match(regex, string, rezim)
match=re.match(r"^.*?\.txt$", sys.argv[1], re.I) 
if match is None:
    sys.exit("Ekstenzija nije odgovarajuca!")
   
#print(sys.argv)
for arg in sys.argv:
    print(arg)

print("----------------------------------------")
try:
    f=open(sys.argv[1], "r")
except IOError:
    sys.exit("Greska pri open pozivu!")
#data=f.read()
for line in f:
    print(line, end="")

f.close()            