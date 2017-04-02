#ifndef CS101LoadWgtGraph
#define CS101LoadWgtGraph
#include "edgeVec.h"

//load and build graph
typedef struct {
	int from;                                                         
	int to;
	double weight;
} Edge;


FILE * open_file(char *);
EdgeVec * initEdges(int); 
int parseN(char *);
Edge parseEdges(char *, int);
void loadEdges(char *, EdgeVec[], int, int);
void printEdge(EdgeInfo);
void printGraph(EdgeVec[], int);
//IntList * transposeGraph(IntList[], int);
//int hasCycle(IntList[], int);
//int hasCycleLen(IntList[], int, int, IntList);


#endif