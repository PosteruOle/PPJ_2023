import sys, re

if len(sys.argv)<2:
    sys.exit("Argumenti!")

match=re.match(r"^.*?\.stn$", sys.argv[1], re.I)
if match is None:
    sys.exit("Ekstenzija!")  

try:
    f=open(sys.argv[1], "r")
    data=f.read()
except IOError:
    sys.exit("Greska pri open pozivu!")

re_xml=re.compile(r"{(.*?),\.NE\+(\w+):[1-9][a-z]}", re.S)  
data=re_xml.sub(r"<\2> \1 </\2>", data) 
print("---------------------------------------")
print(data)
print("---------------------------------------")
try:
    file_name=sys.argv[1][:-3]+"xml"
    print(file_name)
    f=open(file_name, "w")
    f.write("<xml>\n")
    f.write(data)
    f.write("\n</xml>\n")
except IOError:
    sys.exit("Greska pri open pozivu!")                       