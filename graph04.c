#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "edgeVec.h"
#include "loadWgtGraph.h"
#include "minPQ.h"


int main(int argc, char* argv[]) {
double calcPriority(int task, MinPQ pq, int v, double wgt) {
	double distance;
	if (task == 'P') 
		return wgt;
	else if(task == 'D') {
		distance = getPriority(pq, v);
		return (distance + wgt);
	}
}

void printOutput(int n, int * status, double * fringeWgt, int * parent) {
	printf("vertex\tstatus\tpriority\tparent\t");
	int i;
	for(i = 1; i <= n; ++i) {
		printf("%d\t  %c\t  %d\t   %.2f\n",\
		       i, status[i], parent[i], fringeWgt[i]);
	} 
}



void updateFringe(int task, MinPQ pq, EdgeVec adjInfoOfV, int v) {
	int w;
	int i = 1;
	double weight;
	double previous;
	EdgeVec remAdj;
	remAdj = adjInfoOfV;
	while(remAdj != NULL) {
		EdgeInfo wInfo = edgeTop(remAdj);
		w = wInfo.to;
		weight = wInfo.wgt;
		previous = calcPriority(task, pq, v, weight);
		if (getStatus(pq, w) == UNSEEN){
			insertPQ(pq, w, weight, v);
		}
		else if (getStatus(pq, w) == FRINGE) {
			if (previous< getPriority(pq, w)){
			    decreaseKey(pq, w, weight, v);
			}
		}
		remAdj = adjInfoOfV;
		//remAdj = edgeData(remAdj, i);
		i++;
	}
	return;
}


void greedyTree(EdgeVec * adjInfo, int n, int s, int * status, double * fringeWgt, int * parent, int task) {
	int v;
	status = (int *)malloc((n+1)*sizeof(int));
	MinPQ pq = createPQ(n, status, fringeWgt, parent);
	insertPQ(pq, s,0, -1);
	while(!isEmptyPQ(pq)) {
		v = getMin(pq);
		delMin(pq);

		updateFringe(task, pq, adjInfo[v], v);
	}
}

	int task;
	FILE * in;
	int s;
	int n;


	//if program receives no command-line arguments, print usage and exit
	if (argc == 0 || argc < 3) {
		fprintf(stderr, "Usage: greedy04 task vertex input.data \n");
		exit(EXIT_FAILURE);
	}
	

	// depending on argument program sets a variable named task
	// passes task to other functions to vary their computations
	// set the value of task to P or D depending on user input
	
	if (!strcmp(argv[1], "-P")) {
	    task = 'P';
	    printf("Running Prim.\n");
	}
	else if (!strcmp(argv[1], "-D")) {
		task = 'D';
		printf("Running Dijkstra.\n");
	}
	else {
		fprintf(stderr, "No such task.(-P or -D)\n");
		exit(1);
	}
	//command line argument that is an integer that gives the start vertex for algorithm
	
	s = atoi(argv[2]); //convert string argument into integer
	if (s > n) {
		fprintf(stderr, "Vertex chosen greater than existing number of vertices.\n");
		exit(1);
	}
	else if(s <= 0){
		fprintf(stderr, "Vertex chosen less than 0. Input positive integer\n");
		exit(1);
	}
	/*finall cl argument name of input file containing the weighted graph, does not 
	begin with a '-' */
	
	if (strcmp(argv[3], "-"))  //build graph from file
		//in = open_file(argv[3]);
		in = fopen(argv[3], "r");
	if (in == !NULL) {
		printf("Opened %s for input\n", in);
	}   
	
		


	/*read and parse n*/
	char line[1024]; //overestimate the amount of chars 
	char * fgetsRetn;
	fgetsRetn = fgets(line, sizeof(line), in);
	if (!fgetsRetn)
		fprintf(stderr, "empty file\n");
	else{
	n = parseN(line);
	}

	EdgeVec * adjInfos;
	adjInfos = initEdges(n);


	/*read file to buffer and parse each line*/
	while (fgets(line, sizeof(line), in)) {
		loadEdges(line, adjInfos, n, task);
	}


	/*print the graph*/
	printf("=====================original graph================== ");
	printGraph(adjInfos, n);


	/*initialize arrays*/
	int * parent = (int *)malloc((n+1)*sizeof(int));
	double * wgt = (double *)malloc((n+1)*sizeof(double));
	int * status = initStatus(n);
	parent = initParent(n);
	wgt = initFringeWgt(n);


	/*implement Prim or Dijkstra algorithm depending on task*/
	greedyTree(adjInfos, n, s, status, wgt, parent, task);


	/*print the result*/
	printOutput(n, status, wgt, parent);
	
	fclose(in);


	return 0;

}





	
