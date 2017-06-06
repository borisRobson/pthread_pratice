#include <stdio.h>
#include <stdlib.h>

/*
The following sturcture contains the necessary infromation
to allow the function dotprod to access its input data and
place its output so that it can be accessed later
*/

typedef struct{
    double *a;
    double *b;
    double sum;
    int veclen;
} DOTDATA;

#define VECLEN 10000000
DOTDATA dotstr;

/* 
We will use a fucntion (dotprod) to perform the scalar product
All input to this routine is obtained through a structure of
type DOTDATA and all outpyt from this function is written into 
this same structure. While this is unnecessarily restrictive
for a sequential program, it will turn out useful when modified
for parallel
*/
void dotprod()
{
    /* Define and use local variables for convenience */
    int start, end, i;
    double mysum, *x, *y;

    start = 0;
    end = dotstr.veclen;
    x = dotstr.a;
    y = dotstr.b;

/* 
Perform the dotrpod and assign result
to the appropriate variable in teh structure
*/
    mysum = 0;
    for(i=start; i < end; i++)
    {
        mysum += (x[i] * y[i]);
    }
    dotstr.sum = mysum;
}

/*
The main program initialises data and calls the dotprod() function
FInally, prints result
*/
int main(int argc, char* argv[])
{
    int i,len;
    double *a, *b;

    /* Assing storage and initialise values */
    len = VECLEN;
    a = (double*) malloc (len*sizeof(double));
    b = (double*) malloc (len*sizeof(double));

    for(i = 0; i < len; i++){
        a[i] = 1;
        b[i] = a[i];
    }

    dotstr.veclen = len;
    dotstr.a = a;
    dotstr.b = b;
    dotstr.sum = 0;

    /* Perform the dotprod */
    dotprod();

    /* Print result and release storage */
    printf("Sum= %f\n", dotstr.sum);
    free(a);
    free(b);
}

