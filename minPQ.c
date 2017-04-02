#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <float.h>  
#include "minPQ.h"

/*int main(void){
	int too = 0;
}
*/
struct MinPQNode {
	//instance fields
	int numVertices, numPQ; 
	int minVertex; 
	double oo; 
	int * status;
	int * parent;
	double * fringeWgt;
};
typedef struct MinPQNode * MinPQ;


int isEmptyPQ(MinPQ pq) {
	if(pq->numPQ == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int getMin(MinPQ pq) {
	if (pq->minVertex == -1) {
		int v;
		double minWgt;
		minWgt = pq->oo;
		for(v = 1; v <= pq->numVertices; ++v) {
			if (pq->status[v] == FRINGE){
				if (pq->fringeWgt[v] < minWgt) {
					pq->minVertex = v;
					minWgt = pq->fringeWgt[v];
				}
			}
		}
	}
	return pq->minVertex;
}

int getStatus(MinPQ pq, int id) {
	return pq->status[id];
}

int getParent(MinPQ pq, int id) {
	return pq->parent[id];
}

double getPriority(MinPQ pq, int id) {
	return pq->fringeWgt[id];
}

void delMin(MinPQ pq) {
	int oldMin = getMin(pq);
	pq->status[oldMin] = INTREE;
	pq->minVertex = -1;
	pq->numPQ--;

}

void insertPQ(MinPQ pq, int id, double priority, int par){//int newPar,double newW) {
	 pq->parent[id] = par;
	 pq->fringeWgt[id] = priority;
	 pq->status[id] = FRINGE;
	 pq->minVertex = -1;
	 pq->numPQ++;

 }

void decreaseKey(MinPQ pq, int id, double priority, int par){//int newPar, double newW) {
	pq->parent[id] = par;
	pq->fringeWgt[id] = priority;
	pq->minVertex = -1;
	//pq->numPQ--;

}

MinPQ createPQ(int n, int status[], double priority[], int parent[]){//int parent[], double fringeWgt[]) {
	int i;
	MinPQ pq = (MinPQ)malloc(sizeof(struct MinPQNode));
	pq->parent = parent;
	pq->fringeWgt = priority;
	pq->status = status;
	pq->oo = DBL_MAX;
	for(i = 1; i <= n; ++i) {
					pq->status[i] = UNSEEN;
					pq->fringeWgt[i] = pq->oo;
					pq->parent[i] = -1;
	}
	pq->numVertices = n;
	//pq->numPQ = 0;
	pq->minVertex = -1;
	
	return pq;
}









/*return fringe vertex with min wgt, return -1 is no fringe vertex remains*/



	


