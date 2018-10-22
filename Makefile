compile: 
	@gcc -o out readmap.c driver.c ptrace.c
	@sudo ./out
