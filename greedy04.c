#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "edgeVec.h"
#include "loadWgtGraph.h"
#include "minPQ.h"


int main(int argc, char* argv[]) {

void printOutput(int n, int * status, double * fringeWgt, int * parent) {
	printf("##################################################\n");
	printf("This is the sorted graph\n");
	printf("vertex\tstatus\tparent\tpriority\t\n");
	int i;
	for(i = 1; i <= n; ++i) {
		printf("%d\t  %c\t  %d\t   %.2f\n",\
		       i, status[i], parent[i], fringeWgt[i]);
	} 
}

double calcPriority(int task, MinPQ pq, int v, double wgt) {
	double distance;
	if (task == 'P') 
		return wgt;
	else{
		distance = getPriority(pq, v);
		return (distance + wgt);
	}
	
}


void updateFringe(int task, MinPQ pq, EdgeVec adjInfoOfV, int v) {
	int k;
	//int i = 1;
	double weight;
	double previous;
	EdgeVec remAdj;
	remAdj = adjInfoOfV;
	while(edgeSize(remAdj) > 0) {
		EdgeInfo zInfo = edgeTop(remAdj);
		k = zInfo.to;
		weight = zInfo.wgt;
		previous = calcPriority(task, pq, v, weight);
		if (getStatus(pq, k) == UNSEEN){
			insertPQ(pq, k, previous, v); 
		}
		else if (getStatus(pq, k) == FRINGE) {
			if (previous< getPriority(pq, k)){
			    decreaseKey(pq, k, previous, v);
			}
		}
		//remAdj = adjInfoOfV;
		//remAdj = edgeData(remAdj, i);
		//i++;
		edgeVecPop(remAdj);
	}

}


void greedyTree(EdgeVec * adjInfo, int n, int s, int * status, double * fringeWgt, int * parent, int task) {
	int v;
	MinPQ pq;
	pq = createPQ(n, status, fringeWgt, parent);
	insertPQ(pq, s,0.0, -1);
	while(isEmptyPQ(pq)==0) {
		v = getMin(pq);
		delMin(pq);
		updateFringe(task, pq, adjInfo[v], v);
	}
}

	int task;
	FILE * in;
	int beginVertex;
	int n;
	EdgeVec * adjInfos;
	EdgeVec * adjInfos2;

	//if program receives no command-line arguments, print usage and exit
	if (argc == 0 || argc < 3) {
		fprintf(stderr, "Usage: greedy04 task vertex input.data \n");
		exit(EXIT_FAILURE);
	}
	

	// depending on argument program sets a variable named task
	// passes task to other functions to vary their computations
	// set the value of task to P or D depending on user input
	
	if (strcmp(argv[1], "-P")==0) {
	    task = 'P';
	    printf("Running Prim.\n");
	}
	else if (strcmp(argv[1], "-D")==0) {
		task = 'D';
		printf("Running Dijkstra.\n");
	}
	else {
		fprintf(stderr, "No such task.(-P or -D)\n");
		exit(1);
	}
	//command line argument that is an integer that gives the start vertex for algorithm
	printf("Opened file for input\n");


	char line[1024]; //overestimate the amount of chars 
	char * fgetsRetn;
	//fgetsRetn = fgets(line, sizeof(line), in);
	
	if (strcmp(argv[3], "-") == 0){  //build graph from file
		in = stdin;
	
	}
	else{
	in = fopen(argv[3], "r");
	printf("Opened file for input\n");
	}
	
	fgetsRetn = fgets(line, 1024, in);
	
		
	   
	if (!fgetsRetn)
		fprintf(stderr, "empty file\n");
	
	n = parseN(line);
	
	beginVertex = atoi(argv[2]);
	

	adjInfos = initEdges(n);
	adjInfos2 = initEdges(n);

	while (fgets(line, sizeof(line), in)) {
		loadEdges(line, adjInfos, n, task);
		loadEdges(line, adjInfos2, n, task);
	}

	printf("Here is the original graph from the input file\n");
	printGraph(adjInfos, n);


	int * parent = (int *)malloc((n+1)*sizeof(int));
	double * wgt = (double *)malloc((n+1)*sizeof(double));
	int * status = (int *)malloc((n+1)*sizeof(int));
	
	greedyTree(adjInfos2, n, beginVertex, status, wgt, parent, task);

	printOutput(n, status, wgt, parent);
	
	//fclose(in);


	return 0;

}





	
