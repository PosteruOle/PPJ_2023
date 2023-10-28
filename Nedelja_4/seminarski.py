import sys
import re 
import os

if len(sys.argv)>=2:
	home_dir=sys.argv[1]
else:
	home_dir="."

re_student_dir=re.compile(r"(m[mnvrlia]|a[aif])([01][0-9]|2[0-3])(00[1-9]|0[1-9][0-9]|[1-5][0-9][0-9]|600)", re.S)

re_task=re.compile(r"[1-9]\.(pas|py|cpp|c|java)", re.S)

for f in os.listdir(home_dir):
	print(f)
	student_path=os.path.join(home_dir, f)
	match1=re_student_dir.match(f)
	if match1 is not None and os.path.isdir(student_path):
		count=0
		for task in os.listdir(student_path):
			match2=re_task.match(task)
			if match2 is not None:
				print("\t", match2.group())
				count+=1
		while count<4:
			print("\t -")
			count+=1				
