compile: scan.c
	@gcc -o out readmap.c driver.c
	@./out
	@echo "\nComplete"
