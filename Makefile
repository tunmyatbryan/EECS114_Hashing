CC = g++
CFLAGS =
COPTFLAGS = -O3 -g
LDFLAGS =

default:
	@echo "=================================================="
	@echo "To build your code, use:"
	@echo "  make hashlinear	# For Hash table with linear probing"
	@echo "  make hashchain	# For Hash table with chaining"
	@echo "  make prims		# For Prim’s algorithm for MST"
	@echo ""
	@echo "To clean this subdirectory (remove object files"
	@echo "and other junk), use:"
	@echo "  make clean"
	@echo "=================================================="

# Hash table with linear probing driver
hashlinear: hashlineardriver.o
	$(CC) $(COPTFLAGS) -o $@ $^

# Hash table with chaining
hashchain: hashchaindriver.o
	$(CC) $(COPTFLAGS) -o $@ $^

# Prim’s algorithm for MST
prims: primsdriver.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ hashlinear hashchain prims denseMST_output.txt spareMST_output.txt

# eof
