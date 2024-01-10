import sys

# lista
a = [1,2,3,"ppj",{1 , 2, 3}, 4,5,6]
print(a)

print(a[-1])
print(a[2:4])
print(a[:4])
print(a[2:])

a[2] = "drvo"

print(a)

print(a+a)
print(a)
print(a*4)
print(4*a)

b = a[:]
print(b)
b[:0] = ['na', 'pocetak']
print(b)
print(a)

b.extend(a)
print(b)

b.append(a)
print(b)
l = b[-1]
print(l)

b.remove(2)
print(b)

print(b.index('drvo'))
print(b.count(6))

b.pop()
print(b)

b = [1,2,3,4,5,6]
b.sort(reverse=True)
print(b)

s = ["drvo", 'os', 'programiranje', 'prevodjenje', 'jezik']
s.sort()
print(s)

s.sort(key=len, reverse=True)
print(s)

# n-torke
# tupple
t = (1,2,3,4,5,6)
t[2] = 10
