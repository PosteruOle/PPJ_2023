import sys

s = set('abrakadabra')

print(s)

b = ['abrakadabra', 'primer', 'primer']
print(set(b))

if 'f' not in s:
    s.add('f')
    print("dodao sam f")
elif:
    print('Hi there!')
else:
    s.remove('f')
    print("uklonio sam f")

print(s)

c = set('primer1234')
print(c)

print(s & c)
print(s.intersection(c))

print(s | c)
print(s.union(c))

print(s - c)
print(s.difference(c))

print(s ^ c)
print(s.symmetric_difference(c))
