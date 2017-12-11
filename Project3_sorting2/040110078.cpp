//Nurefsan Sertbas
//040110078


#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;




//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int partition(int* array,int first, int last)
{
    int pivot = array[last];

    while ( first  < last )
    {
        while ( array[first] < pivot )
            first ++;

        while ( array[last] > pivot )
            last--;

        if ( array[first] == array[last] )
            first ++;
        else if ( first  < last )
        {
            int tmp = array[first];
            array[first ] = array[last];
            array[last] = tmp;
        }
    }

    return last;
}


void quicksort(int * array, int first,int last){

	if(first<last){
	int q=partition(array,first,last);
	quicksort(array,first,(q-1));
	quicksort(array,q+1,last);}
}


//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
  
void countingsort(int arr[], int n, int max )
{
    int output[n];
    int k=max+1;
    int i;
    int count[k];

    for (i = 0; i < k; i++)
 	count[i] = 0;

    for (i = 0; i < n; i++)
        count[(arr[i] ) ]++;
    for (i = 1; i < k; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] )] - 1] = arr[i];
        count[(arr[i] ) ]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

int maximum(int array[], int n)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}


void countSortforradix(int arr[], int n, int exp)
{
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
void radixsort(int arr[], int n)
{
    int m = maximum(arr, n);
    //call countsort for each 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortforradix(arr, n, exp);
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

int writetofile(int * array,int size){
	FILE *ptr_file;
	ptr_file =fopen("sorted.txt","w");
	
	if (ptr_file==NULL)
		return 1;
		
	for(int i=0;i<size;i++){
	fprintf(ptr_file, "%d\n",array[i]);}
	

	fclose(ptr_file);
	cout<<("Write operation over file is succesfull. (sorted.txt)" )<<endl;
	return 0;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

int main(int argc,char * argv[])
{  	
	clock_t t;
	FILE *ptr_file;
	int num;


	//arguments from the command line
	char alg=*argv[1];
	char * filename=argv[2]; 
	//char  path[20]="data/";
   
 	//strcat(path,filename);
     
	printf("Path of the selected file: %s\n",filename);

   	 ptr_file =fopen(filename,"r");
	   if (ptr_file==NULL)
    		return 1;
	
   
	//find the number of elements in the file to create an array		
	int i=1;
	fscanf (ptr_file, "%d", &num); 
	while (fscanf (ptr_file, "%d\n", &num)!=EOF)
    	{ 		 
	  i++;	       
    	}

	//take cursor to the start of the file
   	fseek(ptr_file,0,SEEK_SET);
	
		
	int dizi[i];//create an array to hold numbers in the file
	
	//read the file	
	long ix=1;
	fscanf (ptr_file, "%d", &num); 
	dizi[0]=num;
	
    	while (fscanf (ptr_file, "%d\n", &num)!=EOF)
    	{ 	
	  dizi[ix]= num;
	  ix++;	       
    	}

	//at this line i holds the numbers of integers at array
	//now our data is ready in array named dizi and its size is held in i.


 	int size = sizeof(dizi)/sizeof(dizi[0]);
	//select an algorithm from according to the character to be entered from command line
	switch(alg){
	case 'q':  	cout<<"Quick Sort Algorithm is selected "<<endl;	
			t=clock();
			quicksort(dizi,0,size-1);
			t=clock()-t; 
			writetofile(dizi,i); 
			printf("It took %f seconds",(double)t/CLOCKS_PER_SEC);	
			break;


	case 'r':	cout<<"Radix Sort Algorithm is selected "<<endl;	
			t=clock();
			radixsort(dizi,size);
			t=clock()-t; 
			writetofile(dizi,i); 
			printf("It took %f seconds",(double)t/CLOCKS_PER_SEC);	
			break;

	case 'c':	cout<<"Counting Sort Algorithm is selected "<<endl;	
			t=clock();
			int max=maximum(dizi,size);
			countingsort(dizi,size,max);
			t=clock()-t; 
			writetofile(dizi,i); 
			printf("It took %f seconds",(double)t/CLOCKS_PER_SEC);	
			break;

	}

	
	//close the file and return
	fclose(ptr_file);
	return 0;

	}

