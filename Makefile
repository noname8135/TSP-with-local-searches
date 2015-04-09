all:
	gcc hill.c -O3 -o hill
	gcc sa.c -O3 -o sa
	gcc tabu.c -O3 -o tabu
clean:
	rm hill	sa tabu