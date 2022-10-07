estimatecron : estimatecron.o month-date-checks.o debug-prints.o file-reads.o processing.o
	cc -o estimatecron estimatecron.o month-date-checks.o debug-prints.o file-reads.o processing.o
estimatecron.o : estimatecron.c myh.h
	cc -c estimatecron.c
month-date-check.o : month-date-checks.c myh.h
	cc -c month-date-check.c
debug-prints.o : debug-prints.c myh.h
	cc -c debug-prints.c
file-reads.o : file-reads.c myh.h
	cc -c file-reads.c
processing.o : processing.c myh.h
	cc -c processing.c