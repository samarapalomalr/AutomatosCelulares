all: tp.o automato.o
	@gcc tp.o automato.o -o exe
	@rm -r tp.o automato.o
tp.o: tp.c
	@gcc tp.c -c -Wall
automato.o: automato.c
	@gcc automato.c -c -Wall
run:
	@./exe
