import sys

s = "Hel'l'o world"
print(s)

#   H   e  l  l  o     w  o  r  l  d 
#   0   1  2  3  4  5  6  7  8  9 10
# -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1

print(s[2])
print(s[2:9])
print(s[-1:-7]) # ne moze <=> s[10:4]
print(s[-7:-1]) # moze <=> s[4:10]
print(s[2:-1])
print(s[:4])

s1 = s[0:2] + '"c"' + s[3:]

print(s1)

print(len(s))

s = """   ldfl;kdsjf
    ovo je neki tekst
 s  skdfjklsdkfj
 """

print(s)
