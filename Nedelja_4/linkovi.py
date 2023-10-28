import sys
import re 
import os


#if len(sys.argv)<2:
#	sys.exit("Nedvoljan broj argumenata!")
def obradi_stranice(dat):
	if dat in stranice:
		return
	
	stranice.append(dat)	
	
	try:
		f=open(dat, "r")
		data=f.read()
	except IOError: 	
		sys.exit("Greska pri open pozivu!")
	
	re_html=re.compile(r"<a\s+href\s*=\s*\"(.*?)\">.*?</a>", re.S)
	for match in re_html.finditer(data):
		#print(match.group(1))
		obradi_stranice(match.group(1))	

if len(sys.argv)>=2:
	pocetna=sys.argv[1]
else:
	pocetna="prva.html"


stranice=[]
obradi_stranice(pocetna)
print("---------------------------------------")
for data in stranice:
	print(data)		
