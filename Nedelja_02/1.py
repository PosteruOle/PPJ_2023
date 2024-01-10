#!/usr/bin/python3

import sys

print("Hello world", end="\n")

x = 12
y = 3.5
print(x, y, sep=" -> ")

print(x+y)
print(x-y)
print(x*y)
print(x/y)

# x^y
print(x**y)
# kolicnik pri deljenju
print(x // y) 
# ostatak pri deljenju
print(x%y)

x = "neki string"
print(x)
print('-------------------------')
x = 2.5 + 3.5j
print(x)
print(x.real, x.imag)

y = -1 - 2j
print(y)

print(x + y)
print(x - y)
print(x * y)
print(x / y)
