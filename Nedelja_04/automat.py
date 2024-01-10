import sys

# regex: (ab|c)*b
prelazi = {("ADE","a") : "B", ("ADE","b") : "C", ("ADE", "c") : "ADE", 
            ("B", "b") : "ADE"
        }
    
pocetno = "ADE"
zavrsna = ["C"]

print("-----------------------------------------")
stanje=pocetno


while True:
	try:
		c=input("Unesite slovo a, b ili c:")
		
		if c!='a' and c!='b' and c!='c':
			sys.exit("Nepodrzano slovo!")
		
		#if prelazi[(stanje, c)] is None:
		#	raise ValueError
		
		if prelazi.get((stanje, c)) is None:
			raise ValueError
		
		stanje=prelazi[(stanje, c)]	
			
	
	except EOFError:
		break
	except ValueError:
		sys.exit("Prelaz u nepostojece stanje!")

			
if stanje in zavrsna:
	print("Automat prepoznaje unetu rec!")
else:
	print("Automat ne prepoznaje unetu rec!")				
