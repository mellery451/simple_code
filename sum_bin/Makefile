CC=g++
CFLAGS=-I. -c -Wall -Wextra
LDFLAGS=

run_tests: test_driver
	@echo "++++++++++++++++++++++++++++"
	@echo "  RUNNING TESTS.."
	@echo "++++++++++++++++++++++++++++"
	./test_driver

test_driver: test_main.o sum_bin.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o test_driver

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
