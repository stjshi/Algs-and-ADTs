
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "edgeVec.h"


typedef struct EdgeVecNode{
	EdgeInfo* data; 
	int size;
	int capacity; 
} EdgeVecNode;
	
typedef EdgeVecNode * EdgeVec;
//typedef EdgeVecNode * EdgeVec;

//static const int edgeInitCap = 4;


EdgeInfo edgeTop(EdgeVec myVec){
	int returnFirst;
	returnFirst = (myVec->size)-1;
	return(myVec->data[returnFirst]);
}


EdgeInfo edgeData(EdgeVec myVec, int i){
	//int size1;
	//size1 = myVec-> size;
	return myVec-> data[i];
}


int edgeSize(EdgeVec myVec){
  return(myVec->size);
}

int edgeCapacity(EdgeVec myVec){
	return(myVec-> capacity);
}

EdgeVec edgeMakeEmptyVec(void){

	EdgeVec vec2;
	vec2 = calloc(4000, sizeof(EdgeVecNode));
	vec2-> capacity = 4000;
	vec2-> data = calloc(4000, sizeof(EdgeVecNode));
	vec2-> size = 0;
	return vec2;
}



void edgeVecPush(EdgeVec myVec, EdgeInfo newE){
	EdgeInfo* data2;
	int cap2;
	int newSize;
	newSize = myVec->size;
	
	if (newSize>=(myVec->capacity)){
		cap2 = 1000 * myVec->capacity;
		data2 = realloc(myVec->data, cap2 * sizeof(int));
		if (data2 != (myVec->data)) {
		  myVec->data = data2;
		}
		else{
		myVec->capacity = cap2;
		}
	}

	myVec->data[newSize] = newE; 
	myVec->size++;

}

void edgeVecPop(EdgeVec myVec){
	//int size2;
	//size2 = myVec->size;
	myVec->size--; 
	
	
}
