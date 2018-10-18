compile: 
	@gcc -o out readmap.c driver.c
	@./out
	@echo "\nComplete"
