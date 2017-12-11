//Nurefsan Sertbas
//040110078


#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int n=10; //number of candidates is set to 10
int bestofk=2;

int hiring(int* scores,int k){
	int i;
	
	//n=10 is fixed in our case

	for (i=0; i<k;i++){
		if (scores[i]>bestofk)
		bestofk=scores[i];}

	for (i=k; i<n;i++){
		if (scores[i]>bestofk)
		return i;}

	return n;

}

int writetofile(int best_index,int best_score, clock_t t){
	FILE *ptr_file;
	ptr_file =fopen("best_applicant.txt","w");
	
	if (ptr_file==NULL)
		return 1;
	
	float runningtime=(float)t/CLOCKS_PER_SEC;
	fprintf(ptr_file, "%d\n",best_index);
	fprintf(ptr_file, "%d\n",best_score);
	fprintf(ptr_file, "%f\n",runningtime);
	

	fclose(ptr_file);
	return 0;
}


int main(int argc,char * argv[])
{  	
	clock_t t;
	FILE *ptr_file;
	//arguments from the command line

	int linenum=atoi(argv[1]);	
	int k=atoi(argv[2]);

	
    ptr_file =fopen("data.txt","r");
	   if (ptr_file==NULL)
    return 1;

   int i=1;
   char line[256];
   char A[256],B[256],C[256]; // holds the related lines
   int arrayA[10],arrayB[10],arrayC[10]; //holds the tokenized values of related line
										 //10 numbers read from file will be stored at there

   //reading line by line from file
	fgets(A, sizeof(line), ptr_file);
	fgets(B, sizeof(line), ptr_file);
	fgets(C, sizeof(line), ptr_file);

	//save the values as integer at user selected line 
	int index=0;
	switch(linenum){
	case 1:
		{
		 char * pch = strtok (A,", ");
		 while (pch != NULL)
		{   arrayA[index]=atoi(pch);
			pch = strtok (NULL, ", ");
		    index++;}
		 break;}
	case 2:
		{
		 char * pch = strtok (	B,", ");
		 while (pch != NULL)
		{   arrayB[index]=atoi(pch);
			pch = strtok (NULL, ", ");
		    index++;}
		 break;
		}
	case 3:
		{
		 char * pch = strtok (C,", ");
		 while (pch != NULL)
		{   arrayC[index]=atoi(pch);
			pch = strtok (NULL, ", ");
		    index++;}
		  break;
		}}
			
	
			
	//our data is ready for the algorithm
	int best_index;
	int best_score;

	switch(linenum){
	case 1: 	t=clock();
				best_index=hiring(arrayA,k);
				t=clock()-t;
				if(best_index==10) //we should take nth candidate
				best_index=9;
		
				best_score=arrayA[best_index];
				break;
	
	case 2:		t=clock();
				best_index=hiring(arrayB,k);
				t=clock()-t;	
				if(best_index==10) //we should take nth candidate
				best_index=9;
	
				best_score=arrayB[best_index];
				break;
	
	case 3:		t=clock();
				best_index=hiring(arrayC,k);
				t=clock()-t;	
				if(best_index==10) //we should take nth candidate
				best_index=9;
	
				best_score=arrayC[best_index];
				break;
	}

	
	// Results to output
	cout<<k<<" person are rejected"<<endl;
	cout<<"Note that indexes are started from 0"<<endl;
	
	cout<<"Best score of first k interviewer is "<<bestofk<<endl;
	
	writetofile(best_index, best_score,t);
	fclose(ptr_file);
	return 0;

	}

