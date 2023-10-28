import sys
import re

o_autor=False
o_naslov=False
o_izdavac=False
o_knjiga=None

if len(sys.argv)<2:
    sys.exit("Nedovoljan broj argumenata!")
 
for arg in sys.argv:
     if arg[0]=='-':
         if arg[1]=='a':
             o_autor=True
         elif arg[1]=='n':
             o_naslov=True
         elif arg[1]=='i':
             o_izdavac=True        
 
match=re.match(r"^.*?\.xml$", sys.argv[1], re.I)

if match is None:
    sys.exit("Ekstenzija nije odgovarajuca!")

try:
    f=open(sys.argv[1], "r")
    data=f.read()
    f.close()
except IOError:
    sys.exit("Greska pri open pozivu!")
print("----------------------------------------")
re_books=re.compile(r"<knjiga\s+rbr=\"(?P<redni_broj>[0-9]+)\">"
+r"(?=.*?<cena valuta=\"(?P<valuta>.*?)\">\s*(?P<cena>.*?)\s*</cena>)"
+r"(?=.*?<naslov>\s*(?P<naslov>.*?)\s*</naslov>)" 
+r"(?=.*?<autor>\s*(?P<autor>.*?)\s*</autor>)"  
+r"(?=.*?<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>)"
+r"(?=.*?<godina_izdanja>\s*(?P<izdanje>.*?)\s*</godina_izdanja>)"                  
+r".*?"
+r"</knjiga>", re.S)

library={}

for match in re_books.finditer(data):
    print("-----------------------------")
    print(match.group())
    print(match.group("redni_broj")) 
    print(match.group("naslov"))
    print(match.group("autor"))
    print(match.group("izdavac"))
    print(match.group("izdanje"))
    print(match.group("cena"))
    print(match.group("valuta"))
    rbr=int(match.group("redni_broj")) 
    naslov=match.group("naslov")
    autor=match.group("autor") 
    izdavac=match.group("izdavac")
    izdanje=int(match.group("izdanje"))
    valuta=match.group("valuta")
    cena=int(match.group("cena"))
    library[rbr]=[naslov, autor, izdavac, izdanje, cena, valuta]
    print("-----------------------------")
print("----------------------------------------")
for k, v in library.items():
    print(k, "\n\t", v)
print("----------------------------------------")
for k, values in library.items():
    print(k)
    if o_autor:
        print("\t", values[1])
    if o_naslov:
        print("\t", values[0])
    if o_izdavac:
        print("\t", values[2])                
                