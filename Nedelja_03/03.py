import sys, re, os

if len(sys.argv)<2:
    sys.exit("Argumenti!")

match=re.match(r"^.*?\.txt$", sys.argv[1], re.IGNORECASE)    

if match is None:
    sys.exit("Ekstenzija!")

try:
    f=open(sys.argv[1], "r")
except IOError:
    sys.exit("Grska pri open pozivu!")

print("------------------------------------------")
re_words=re.compile(r"(\b\w+\b)\s*\1", re.I)
for line in f:
    #match=re.match(r"\b(\w+)\b\s*\1", line, re.I)
    match=re_words.search(line)
    if match is not None:
        print(line)
        print("Poklapanje: ", match.group())
        print("Grupe: ", match.groups())
        print("Linija bez poklapanja izgleda ovako: \n\t", re_words.sub(match.group(1), line))
print("------------------------------------------")
                    