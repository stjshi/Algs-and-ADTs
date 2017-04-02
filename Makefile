# Stephanie Shi
# stjshi
# Pa04 Makefile
# ===================================================================

CC     = gcc
CFLAGS = -g -Wall -O0 -std=c99 -D_SVID_SOURCE

greedy04:	greedy04.o loadWgtGraph.o minPQ.o edgeVec.o
	${CC} -o greedy04 greedy04.o loadWgtGraph.o minPQ.o edgeVec.o

edgeVec.o:	edgeVec.c  edgeVec.h
	${CC}  -c  ${CFLAGS}  edgeVec.c

loadWgtGraph.o: loadWgtGraph.c loadWgtGraph.h
	${CC}  -c  ${CFLAGS}  loadWgtGraph.c

minPQ.o: minPQ.c minPQ.h
	${CC}  -c  ${CFLAGS}  minPQ.c

greedy04.o:	greedy04.c loadWgtGraph.h minPQ.h edgeVec.h
	${CC}  -c  ${CFLAGS}  greedy04.c

	