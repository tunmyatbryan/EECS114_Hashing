Script started on Sun 03 Mar 2019 07:11:56 PM PST
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ls
dense_100000.txt   hashlinear.c        prims.cc           timer.c
hashchain.c        hashlineardriver.c  primsdriver.cc     timer.h
hashchaindriver.c  Makefile            sparse_100000.txt  typescript
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ make
==================================================
To build your code, use:
  make hashlinear	# For Hash table with linear probing
  make hashchain	# For Hash table with chaining
  make prims		# For Prim’s algorithm for MST

To clean this subdirectory (remove object files
and other junk), use:
  make clean
==================================================
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ make hashlinear
g++    -c -o hashlineardriver.o hashlineardriver.c
g++ -O3 -g -o hashlinear hashlineardriver.o
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ./hashlinear 100000
the average number of reprobes for inserting 50 percentage load = 0.599300
the average number of reprobes for inserting 90 percentage load = 4.782100

the average number of reprobes for searching 50 percentage load = 19961.331300
the average number of reprobes for searching 90 percentage load = 35929.331300

]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ make hashchain
g++    -c -o hashchaindriver.o hashchaindriver.c
g++ -O3 -g -o hashchain hashchaindriver.o
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ./hashchain 10000
the average number of reprobes for inserting 50 percentage load = 0.000000
the average number of reprobes for inserting 90 percentage load = 0.000000

There is no reprobing in chaining during insertion. So it is zero. The new key will always be inserted to the chain of the hash table index link list.

the average number of reprobes for searching 50 percentage load = 0.773900
the average number of reprobes for searching 90 percentage load = 0.773900

]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ make prims
g++  -O3 -g -o primsdriver.o -c primsdriver.cc
g++ -O3 -g -o prims primsdriver.o
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ./prims
Timer: gettimeofday
Timer resolution: ~ 1 us (?)
Total time for dense.txt: 0 seconds

Timer: gettimeofday
Timer resolution: ~ 1 us (?)
Total time for sparse.txt: 0 seconds

]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ls
dense_100000.txt     hashchaindriver.o   Makefile        spareMST_output.txt
denseMST_output.txt  [0m[01;32mhashlinear[0m          [01;32mprims[0m           sparse_100000.txt
[01;32mhashchain[0m            hashlinear.c        prims.cc        timer.c
hashchain.c          hashlineardriver.c  primsdriver.cc  timer.h
hashchaindriver.c    hashlineardriver.o  primsdriver.o   typescript
[m]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ k[Kmake
==================================================
To build your code, use:
  make hashlinear	# For Hash table with linear probing
  make hashchain	# For Hash table with chaining
  make prims		# For Prim’s algorithm for MST

To clean this subdirectory (remove object files
and other junk), use:
  make clean
==================================================
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ make clean
rm -f core *.o *~ hashlinear hashchain prims denseMST_output.txt spareMST_output.txt
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ ls
dense_100000.txt   hashlinear.c        prims.cc           timer.c
hashchain.c        hashlineardriver.c  primsdriver.cc     timer.h
hashchaindriver.c  Makefile            sparse_100000.txt  typescript
]0;tmyat@bondi:hw3[tmyat@bondi hw3]$ exit
exit

Script done on Sun 03 Mar 2019 07:12:56 PM PST
