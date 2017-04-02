#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include "loadWgtGraph.h"
#include "edgeVec.h"

EdgeVec * initEdges(int n) {
	EdgeVec * adjInfos = (EdgeVec *)calloc(n + 1, sizeof(EdgeVec));
	int i;

	for (i = 1; i <= n; ++i) {
	  adjInfos[i] = edgeMakeEmptyVec();
}
	return adjInfos;
	}


int parseN(char * line) {
	static int position;
	char * temp;
	char * first;
	temp= strdup(line);
	first =  strtok(temp, " \t\n");
	position = atoi(first);


	return position;

}

Edge parseEdges(char * line, int position) {
	Edge newElt;
	char * temp;
	char * first;
	char * second;
	char * third;
	temp = strdup(line);
	first =  strtok(temp, " \t\n");
	second =  strtok(NULL, " \t\n");
	third =  strtok(NULL, " \t\n");

	newElt.from = atoi(first);	
	newElt.to   = atoi(second);	


	if (newElt.from <= 0 || newElt.from > position){
		fprintf(stderr, "Edge (%d, %d) is out of range\n", newElt.from,newElt.to);
		newElt.from = 0;
		newElt.to = 0;
	}  
	 else if (newElt.to <= 0 || newElt.to > position) {
		fprintf(stderr, "Edge (%d, %d) is out of range\n", newElt.from,newElt.to);
		newElt.from = 0;
		newElt.to = 0;
	}  
	if (third != NULL){
		newElt.weight = atof(third);
	}
	else{
		newElt.weight = 0;
	}
	return newElt;
}

void loadEdges(char * line, EdgeVec * adjInfos, int position, int task) {
	
	Edge edgeLoaded = parseEdges(line, position);
	if (edgeLoaded.from != 0 && edgeLoaded.to != 0) {
		EdgeInfo newElt;
		newElt.to = edgeLoaded.to;
		newElt.wgt = edgeLoaded.weight;
		edgeVecPush(adjInfos[edgeLoaded.from], newElt);
		if (task == 'P') {
			EdgeInfo newElt1;
			newElt1.to = edgeLoaded.from;
			newElt1.wgt = edgeLoaded.weight;
			
			edgeVecPush(adjInfos[edgeLoaded.to], newElt1);	
		}
	}
	
}

void printEdge(EdgeInfo Elt) {
	printf("(%d, %.2f)", Elt.to, Elt.wgt);
	return;
}

void printGraph(EdgeVec * adjInfos, int number) {
	int k;
	int first;

	printf("The loaded graph contains %d nodes (vertices).\n", number);
	for (k = 1; k <= number; k++) {
		EdgeVec pnode = adjInfos[k];
		first = 1;
		printf("%d\t", k);
		while (edgeSize(pnode) > 0)  {
		  if(first){
			printf("[");
		  }
		  else{
			printf(", ");
		  }
		printEdge(edgeTop(pnode));
		edgeVecPop(pnode);
		first = 0; 
		}
			if (first){           
			printf("Empty");
			}
			else{
			printf("]");
		}
		printf("\n");
	}
	printf(" ");
}

