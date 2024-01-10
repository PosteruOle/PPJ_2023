import sys

s = input("Unesite brojeve\n"))

niz = map(int,s.split(" "))

for x in niz:
    if x % 2 == 0:
        print(x, " je paran")
        if x < 1000:
            print("\t < 1000")
        else:
            print("\t >= 1000")
    else:
        print(x, " je neparan")
        if x < 1000:
            print("\t < 1000")
        else:
            print("\t >= 1000")

print("Izvan petlje")
