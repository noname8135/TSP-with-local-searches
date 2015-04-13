
(eil51: 426, lin105: 14379, pcb442: 50778) best cases;

Average tour length, runtime, success rate out of 20 run

5 element OF ------Hill-climbing------------
representation of solution: Series of coordinate of cities according to traveling order

evaluation:
total distance

neighbourhood function: 
swap traveling order of two cities

neighbourhood search strategy: 
###find the two city that has the longest side

acceptance criterion: 
#When no neighbour has shorter distance




Reference:
http://en.wikipedia.org/wiki/Hill_climbing



before deciding the temperature function, I made a little observation about how many iteration sa will run. It turns out to be 
around 90~140.



my best =>


simulated annealing => eil51.tsp
---------------------
SCALE=1.487603
Final distance: 426
Final distance: 431
Final distance: 435
Final distance: 437
Final distance: 435
Final distance: 445
Final distance: 434
Final distance: 439
Final distance: 437
Final distance: 441
Final distance: 433
Final distance: 434
Final distance: 459
Final distance: 444
Final distance: 431
Final distance: 439
Final distance: 431
Final distance: 437
Final distance: 431
Final distance: 433
min=426 avg=436.600006
total execution time: 0.684922

simulated annealing => lin105.tsp
---------------------
Final distance: 14379
Final distance: 14379
Final distance: 14401
Final distance: 14447
Final distance: 14401
Final distance: 14401
Final distance: 14379
Final distance: 14489
Final distance: 14426
Final distance: 14489
Final distance: 14426
Final distance: 14448
Final distance: 14536
Final distance: 14447
Final distance: 14496
Final distance: 14489
Final distance: 14379
Final distance: 14548
Final distance: 14442
Final distance: 14460
min=14379 avg=14443.099609
total execution time: 19.930910

