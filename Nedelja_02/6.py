import sys

imenik = {"Pera" : 100, 'Mika' : 200, 'Zika' : 300}

print(imenik)

print(imenik.keys())
print(imenik.values())

if imenik.get('Laza') is None:
    print("Laza nije u imeniku")

if len(imenik) < 3:
    print(imenik)
else:
    imenik['Laza'] = 400

print(imenik)

print(imenik.get("Laza"))

parovi = zip(imenik.keys(), imenik.values())

for k,v in parovi:
    print(k,v)

for k,v in imenik.items():
    print(k,v)