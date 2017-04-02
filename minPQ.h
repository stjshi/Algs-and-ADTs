/* minPQ.h (what is the purpose of this file? Replace this question with your comment.)
*/

#ifndef C101MinPQ
#define C101MinPQ
/* Multiple typedefs for the same type are an error in C. */

typedef struct MinPQNode * MinPQ;

#define UNSEEN ('u')
#define FRINGE ('f')
#define INTREE ('t')

/* ***************** Access functions */

/** (what are the preconditions, if any? Replace this question with your comments, where applicable.)
*/

/** isEmpty
*/
int isEmptyPQ(MinPQ pq);

/** getMin
*/
int getMin(MinPQ pq);

/** getStatus
*/
int getStatus(MinPQ pq, int id);

/** getParent
*/
int getParent(MinPQ pq, int id);

/** getPriority
*/
double getPriority(MinPQ pq, int id);


/* ***************** Manipulation procedures */

/** delMin (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void delMin(MinPQ pq);

/** insertPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void insertPQ(MinPQ pq, int id, double priority, int par);

/** decreaseKey (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
void decreaseKey(MinPQ pq, int id, double priority, int par);


/* ***************** Constructors */

/** createPQ (what are the preconditions and/or postconditions? Replace this question with your comment.)
*/
MinPQ createPQ(int n, int status[], double priority[], int parent[]);


#endif

