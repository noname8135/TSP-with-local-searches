# Hill climbing, simulated annealing and Tabu search practice
This is a homework of meta-heuristic course.
We practice to use Hill climbing, simulated annealing and Tabu search to solve the TSP problem.
The number in each testfile indicate the number of cities.

### Usage example
```sh
make
./sa testfile
```

### Result

(eil51: 426, lin105: 14379, pcb442: 50778) 
Average tour length, total runtime, best solution out of 20 run

my best =>
hill climbing => eil51.tsp
---------------------
min=432 avg=447.399994  
total execution time: 0.006962  
* Final distance: 453
* Final distance: 437
* Final distance: 435
* Final distance: 464
* Final distance: 468
* Final distance: 444
* Final distance: 449
* Final distance: 451
* Final distance: 467
* Final distance: 443
* Final distance: 438
* Final distance: 443
* Final distance: 443
* Final distance: 448
* Final distance: 440
* Final distance: 453
* Final distance: 468
* Final distance: 432
* Final distance: 433
* Final distance: 439


hill climbing => lin105.tsp
---------------------
min=14467 avg=15397.900391
total execution time: 0.073968
* Final distance: 14845
* Final distance: 15112
* Final distance: 14849
* Final distance: 15702
* Final distance: 16110
* Final distance: 15003
* Final distance: 15234
* Final distance: 15874
* Final distance: 15878
* Final distance: 14917
* Final distance: 14919
* Final distance: 15873
* Final distance: 15990
* Final distance: 15661
* Final distance: 15731
* Final distance: 15166
* Final distance: 16100
* Final distance: 15324
* Final distance: 15203
* Final distance: 14467

hill climbing => pcb442.tsp
---------------------
* Final distance: 54804
* Final distance: 54460
* Final distance: 55256
* Final distance: 53901
* Final distance: 54952
* Final distance: 54752
* Final distance: 55957
* Final distance: 55520
* Final distance: 56147
* Final distance: 53088
* Final distance: 55147
* Final distance: 55615
* Final distance: 54908
* Final distance: 56073
* Final distance: 54759
* Final distance: 54258
* Final distance: 54102
* Final distance: 54227
* Final distance: 54841
* Final distance: 53873  
min=53088 avg=54832.000000  
total execution time: 8.057427  


simulated annealing => eil51.tsp
---------------------
* Final distance: 426
* Final distance: 431
* Final distance: 435
* Final distance: 437
* Final distance: 435
* Final distance: 445
* Final distance: 434
* Final distance: 439
* Final distance: 437
* Final distance: 441
* Final distance: 433
* Final distance: 434
* Final distance: 459
* Final distance: 444
* Final distance: 431
* Final distance: 439
* Final distance: 431
* Final distance: 437
* Final distance: 431
* Final distance: 433  
min=426 avg=436.600006  
total execution time: 0.684922  

simulated annealing => lin105.tsp
---------------------
* Final distance: 14379
* Final distance: 14379
* Final distance: 14401
* Final distance: 14447
* Final distance: 14401
* Final distance: 14401
* Final distance: 14379
* Final distance: 14489
* Final distance: 14426
* Final distance: 14489
* Final distance: 14426
* Final distance: 14448
* Final distance: 14536
* Final distance: 14447
* Final distance: 14496
* Final distance: 14489
* Final distance: 14379
* Final distance: 14548
* Final distance: 14442
* Final distance: 14460  
min=14379 avg=14443.099609  
total execution time: 19.930910  


simulated annealing => pcb442.tsp
---------------------
* Final distance: 51284
* Final distance: 51188
* Final distance: 51398
* Final distance: 52209
* Final distance: 51285
* Final distance: 51730
* Final distance: 51639
* Final distance: 51804
* Final distance: 51650
* Final distance: 51352
* Final distance: 51544
* Final distance: 51669
* Final distance: 51600
* Final distance: 51064
* Final distance: 51811
* Final distance: 52037
* Final distance: 51753
* Final distance: 51574
* Final distance: 51196
* Final distance: 51308  
min=51064 avg=51554.750000  
total execution time: 329.874630  


tabu search => eil51.tsp with 500,000 run
---------------------
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426
* Final distance: 426  
min=426 avg=426.000000  
total execution time: 120.158065  

tabu search => lin105.tsp
---------------------------
* Final distance: 15082
* Final distance: 14533
* Final distance: 15223
* Final distance: 14701
* Final distance: 15173
* Final distance: 14379
* Final distance: 14456
* Final distance: 14511
* Final distance: 14504
* Final distance: 14999
* Final distance: 15087
* Final distance: 15124
* Final distance: 14379
* Final distance: 14613
* Final distance: 15234
* Final distance: 14869
* Final distance: 14860
* Final distance: 14910
* Final distance: 14928
* Final distance: 15286  
min=14379 avg=14842.550000  
total execution time: 4449.80  

tabu search => pcb442.tsp
* Final distance: 54737
* Final distance: 54278
* Final distance: 53637
* Final distance: 55573
* Final distance: 55624
* Final distance: 55609
* Final distance: 54134
* Final distance: 56270
* Final distance: 54376
* Final distance: 55803
* Final distance: 54750
* Final distance: 55064
* Final distance: 56130
* Final distance: 55514
* Final distance: 53642
* Final distance: 55058
* Final distance: 55853
* Final distance: 54994
* Final distance: 55749
* Final distance: 56047  
min=53637 avg=55142.100000  
total execution time: 13059.970000  
