all:
	gcc hill.c -O3 -o hill -lm
	gcc sa.c -O3 -o sa -lm
	gcc tabu.c -O3 -o tabu -lm
clean:
	rm hill	sa tabu
