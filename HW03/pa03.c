#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "pa03.h"
#define RANGE 10000

double dis(const double *, double *, int);
int checkstop(int *,int *,int);

void cleanup(FILE * fpin, FILE * fpout)
{
	fclose (fpin);
	fclose (fpout);
}

// allocate a two dimensional array of
double * * allocateMemory(int nrow, int ncol)
{
	double * * data = NULL;
	//TODO: allocate memory for the data and then return the data
	//It is this functions reponsibility to ensure that memory is allocated
	data = malloc(nrow * sizeof(double *));
	for (int i = 0;i < nrow;i++){
	  data[i] = malloc(ncol * sizeof(double));
	}
	return data;
}

void releaseMemory(double * * data, int nrow)
{
	//TODO: complete this function to release the memory of the data
	//not completing this function will lead to memory not getting free
        for (int i = 0;i < nrow;i++){
          free(data[i]);
        }
        free(data);
}

// read the data, return true if success, false if fail
bool readData(FILE * fpin, double * * data, int nval, int dim)
{
	int niter, diter;
	for (niter = 0; niter < nval; niter ++)
	{
		for (diter = 0; diter < dim; diter ++)
		{
			if (fscanf(fpin, "%lf", & data[niter][diter]) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

// write the output centroids to the file
// check for all the NULL before calling this function, it does not check
void writeCentroids(FILE * fpout, double * * centroid, int kval, int dim){
  int kiter,diter;
  for (kiter = 0; kiter < kval; kiter ++)
  {
    for (diter = 0; diter < dim; diter ++)
    {
      //write to the file
      fprintf(fpout, "%lf ", centroid[kiter][diter]);
    }
    fprintf(fpout, "\n");
  }
}

//initilize function is to initilize the values for centroid
void initialize(double * * centroid, int kval, int dim)
{
	int kiter, diter;
	for (kiter = 0; kiter < kval; kiter ++)
	{
		for (diter = 0; diter < dim; diter ++)
		{
			int randval = - RANGE + (rand() % (2 * RANGE));
			centroid[kiter][diter] = randval;
		}
	}
}

int main(int argc, char * * argv)
{
	// argv[1]: name of input file
	// argv[2]: value of k
	// argv[3]: name of output file
	// argv[4]: (optional) seed for random numbers, use time if absent

	if (argc < 4)
	{
		fprintf(stderr, "argc is %d, not 4\n", argc);
		return EXIT_FAILURE;
	}
	FILE * fpin = fopen(argv[1], "r");
	if (fpin == NULL)
	{
		fprintf(stderr, "fopen %s fail\n", argv[1]);
		return EXIT_FAILURE;
	}
	int kval = (int) strtol(argv[2], NULL, 10);
	// convert long to in
	if (kval <= 0)
	{
		fprintf(stderr, "kval is %d, must be positive\n", kval);
		return EXIT_FAILURE;
	}
	FILE * fpout = fopen(argv[3], "w");
	if (fpout == NULL)
	{
		fclose (fpin);
		// was open successfully and needs to be closed
		fprintf(stderr, "fopen %s fail\n", argv[3]);
		return EXIT_FAILURE;
	}

	if (argc == 5)
	{
		int randseed = (int) strtol(argv[4], NULL, 10);
		if (randseed == -1)
		{
			srand(time(NULL));
		}
		else
		{
			srand(randseed);
		}
	}

	int nval;
	fscanf(fpin, "%d", & nval);
	if (nval < kval)
	{
		fprintf(stderr, "nval= %d must be greater than kval = %d\n",
				nval, kval);
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
	int dim;
	fscanf(fpin, "%d", & dim);
	if (dim < 2)
	{
		fprintf(stderr, "nval= %d must be greater than kval = %d\n",
				nval, kval);
		cleanup(fpin, fpout);
		return EXIT_FAILURE;

	}

	// allocate memory for the data points
	double * * datapoint = allocateMemory(nval, dim);
	if (datapoint == NULL)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
	// allocate memory for the centroid
	double * * centroid = allocateMemory(kval, dim);
	if (centroid == NULL)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}

	// read the data from the file
	if (readData(fpin, datapoint, nval, dim) == false)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}

	// initialize centroids within [-RANGE, RANGE] of every dimension
	initialize(centroid, kval, dim);

  //allocate memory for cluster
  int * cluster;
  cluster = malloc(sizeof(*cluster)*nval);
  if(cluster == NULL)
  {
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
  // initilize cluster values
  for(int niter = 0; niter < nval; niter++)
  {
    cluster[niter] = -1;
  }

  //now we will run our kmean algorithm
  kmean(kval, nval, dim, datapoint, centroid, cluster);


  //print all the centroids into a file
  writeCentroids(fpout, centroid, kval, dim);

  //free all the allocated spaces
  releaseMemory(datapoint, nval);
  releaseMemory(centroid, kval);
  free(cluster);
  //close all the files
  cleanup(fpin, fpout);
	return EXIT_SUCCESS;
}


// The k-mean method to cluster data
// kval: the number of clusters
// nval: the number of data pointers
// dim: dimension of the data
// data: two-dimensional array of the data, nval rows, dim columns
// centroid: two-dimensional array of the data, kval rows, dim columns
// cluster: one-dimensional array of n elements, the assignments of
// data to the clusters. cluster[i] = j means the i-th data pointer is
// assigned to the j-th cluster. 0 <= i < nval; 0 <= j < kval

void kmean(int kval, int nval, int dim, double * * data, double * * centroid,
		int * cluster)
{

	//TODO: complete this function
	/*This assignment uses the *k-mean clustering* algorithm. This algorithm works in the following way:
	  1. Read the data and the given value k
	  2. Pick k points (called *centroids*) randomly as the initial centers
	  of the k group
	  3. For each data point, find the closet centroid. Assign this data point to the group represented by this centroid.
	  4. For each group, recompute the location of the centroid as the center of all data points belonging to this group.
	  5. Repeat steps 3 and 4 until the convergence condition is met.
	*/
          int mindex = 0;
	  double distance = 0;
	  double currdistance = 0;
	  int check = 0;
	  int * count = malloc(kval * sizeof(int));
	  int * precluster = malloc(nval * sizeof(int));
	  for (int n = 0; n < nval;n++){
		  precluster[n] = 0;
		  cluster[n] = -1;
	  }
	  check = checkstop(precluster,cluster,nval);
	  while (check == 0){
	    mindex = 0;
	    for (int b = 0; b < kval;b++){
	      count[b] = 0;
	    }
	    for (int c = 0;c < nval;c++){
	      precluster[c] = cluster[c];
	    } 
	    //classify the data points
	    for (int j = 0;j < nval;j++){
	      distance =  dis(data[j],centroid[0],dim);
	      mindex = 0;
	      for (int i = 1;i < kval;i++){
			currdistance = dis(data[j],centroid[i],dim);
			if (currdistance < distance){
		  		distance = currdistance;
		  		mindex = i;
			}
	      }
	      cluster[j] = mindex;
	      count[mindex]++;
	    }
	    for (int x = 0;x < kval;x++){
	      for (int y = 0;y < dim;y++){
	      	centroid[x][y] = 0;
	      }
	    }
	    //calculate the mean of each centroid
	    for (int k = 0;k < nval;k++){
	      for (int l = 0;l < dim;l++){
		 centroid[cluster[k]][l] = centroid[cluster[k]][l] + data[k][l];
	      }
	    }
	    for (int m = 0;m < kval;m++){
	      for (int n = 0;n < dim;n++){
	      		if(count[m] != 0){
			  centroid[m][n] = centroid[m][n] / count[m];
		       	}
	      }
	    }
	    check = checkstop(precluster,cluster,nval);
	  } 
	  free(count);
	  free(precluster);
}
	  
int checkstop(int * precluster,int * cluster,int nvals){
  int check = 1;
  for (int ct = 0; ct < nvals; ct++){
    if (cluster[ct] != precluster[ct]){
      check = 0;
    }
  }
  return check;
}


double dis(const double * datapoint, double * centroid, int dim)
{
  // since this is for comparison only, there is no need to call sqrt
  double sum = 0; // must initialize to zero
  //Please complete the 
  //Calculate the sum
  for (int i = 0; i < dim; i++){
    sum = sum + (datapoint[i]-centroid[i])*(datapoint[i]-centroid[i]);
  }
  return sum;
}
