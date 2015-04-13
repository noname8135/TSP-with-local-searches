
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



before deciding the temperature function, I made a little observation about how many iteration sa will run. It turns out to be 
around 90~140.



my best =>
hill climbing => eil51.tsp
---------------------
Final distance: 453
Final distance: 437
Final distance: 435
Final distance: 464
Final distance: 468
Final distance: 444
Final distance: 449
Final distance: 451
Final distance: 467
Final distance: 443
Final distance: 438
Final distance: 443
Final distance: 443
Final distance: 448
Final distance: 440
Final distance: 453
Final distance: 468
Final distance: 432
Final distance: 433
Final distance: 439
min=432 avg=447.399994
total execution time: 0.006962


hill climbing => lin105.tsp
---------------------
Final distance: 14845
Final distance: 15112
Final distance: 14849
Final distance: 15702
Final distance: 16110
Final distance: 15003
Final distance: 15234
Final distance: 15874
Final distance: 15878
Final distance: 14917
Final distance: 14919
Final distance: 15873
Final distance: 15990
Final distance: 15661
Final distance: 15731
Final distance: 15166
Final distance: 16100
Final distance: 15324
Final distance: 15203
Final distance: 14467
min=14467 avg=15397.900391
total execution time: 0.073968

hill climbing => pcb442.tsp
---------------------
Final distance: 54804
Final distance: 54460
Final distance: 55256
Final distance: 53901
Final distance: 54952
Final distance: 54752
Final distance: 55957
Final distance: 55520
Final distance: 56147
Final distance: 53088
Final distance: 55147
Final distance: 55615
Final distance: 54908
Final distance: 56073
Final distance: 54759
Final distance: 54258
Final distance: 54102
Final distance: 54227
Final distance: 54841
Final distance: 53873
min=53088 avg=54832.000000
total execution time: 8.057427


simulated annealing => eil51.tsp
---------------------
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


simulated annealing => pcb442.tsp
---------------------
Final distance: 51284
Final distance: 51188
Final distance: 51398
Final distance: 52209
Final distance: 51285
Final distance: 51730
Final distance: 51639
Final distance: 51804
Final distance: 51650
Final distance: 51352
Final distance: 51544
Final distance: 51669
Final distance: 51600
Final distance: 51064
Final distance: 51811
Final distance: 52037
Final distance: 51753
Final distance: 51574
Final distance: 51196
Final distance: 51308
min=51064 avg=51554.750000
total execution time: 329.874630


tabu search => eil51.tsp with 500,000 run
---------------------
Final distance: 426
total execution time: 6.531686
Final distance: 426
total execution time: 6.158065
Final distance: 426
total execution time: 6.121706
Final distance: 426
total execution time: 6.135654
Final distance: 426
total execution time: 6.197501
Final distance: 426
total execution time: 6.293847
Final distance: 426
total execution time: 6.190251
Final distance: 426
total execution time: 6.084505
Final distance: 426
total execution time: 6.159879
Final distance: 426
total execution time: 6.118133
Final distance: 426
total execution time: 6.258205
Final distance: 426
total execution time: 6.140270
Final distance: 426
total execution time: 6.312473
Final distance: 426
total execution time: 6.109140
Final distance: 426
total execution time: 6.131806
Final distance: 426
total execution time: 6.354278
Final distance: 426
total execution time: 6.535149
Final distance: 426
total execution time: 6.271263
Final distance: 426
total execution time: 6.209526
Final distance: 426
total execution time: 6.155149


tabu search => lin105.tsp
---------------------------
