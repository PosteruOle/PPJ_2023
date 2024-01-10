import sys, re, os

if len(sys.argv)<2:
    sys.exit("Argumenti!")

match=re.match(r"^.*?\.html$", sys.argv[1], re.I)
if match is None:
    sys.exit("Ekstenxija!")

try:
    f=open(sys.argv[1], "r")
    data=f.read()
except IOError:
    sys.exit("Greska pri open pozivu!") 
print("-------------------------------------------") 
re_students=re.compile(r"<tr>"
+r"\s*<td>\s*(?P<ime_prezime>.+?)\s*</td>\s*"
+r"\s*<td>\s*(?P<prakticni>[0-9]|[1-9][0-9]|100)\s*</td>\s*"
+r"\s*<td>\s*(?P<teorija>[0-9]|[1-9][0-9]|100)\s*</td>\s*"
+r"</tr>", re.S)

students={}

for match in re_students.finditer(data):
    print("--------------------------------") 
    print(match.group())
    print(match.group("ime_prezime"))
    print(match.group("prakticni"))
    print(match.group("teorija"))
    prakticni=float(match.group("prakticni"))
    teorija=float(match.group("teorija"))
    students[match.group("ime_prezime")]=(prakticni+teorija)/2
    print("--------------------------------")
print("-------------------------------------------") 
#sorted(students)
for k, v in students.items():
    print(k, ": ", v)                  