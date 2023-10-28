import sys
import re
import os
# re.match re.search re.findall

message="Danas nam je divan dan"  
match=re.match(r"(\w+\s*)*", message, re.I)

if match is not None:
    #print(match)
    print(match.group())
    print(match.group(0))
    #print(match.groups())
else:
    print("Nemamo poklapanje!")

print("---------------------------------------") 
offset=0
match=re.search(r"\b(\w+)\b", message, re.I)
if match is not None:
    print(match.group())
    print(message[offset+match.start():offset+match.end()])
    print(match.start())
    print(match.end())
    offset+=match.end()
print("---------------------------------------")
match=re.search(r"\b(\w+)\b", message[offset:], re.I)
if match is not None:
    print(match.group())
    print(message[offset+match.start():offset+match.end()])
    print(match.start())
    print(match.end())
    offset+=match.end()
print("---------------------------------------")
match=re.findall(r"\b(\w+)\b", message, re.I)
for m in match:
    print(m)               