//Nurefsan Sertbas
//040110078


#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
void merge(int *array,int *L,int leftCount,int *R,int rightCount) ;

int * mergesort(int * array,int len){
	int ort,i, *L, *R;
	if(len < 2) return NULL; //base for recursion
    //it means algorithm ends the last step for dividing inti groups
	ort = len/2;  // find the mid index. 
	
	// create left and right subarrays
	L = (int*)malloc(ort*sizeof(int)); 
	R = (int*)malloc((len-ort)*sizeof(int)); 
	
	//create subarrays(left and right)
	for(i = 0;i<ort;i++) 
	L[i] = array[i];
	for(i = ort;i<len;i++) 
	R[i-ort] = array[i]; 

	//recursive structure(calls itself)
	mergesort(L,ort);  //Left
	mergesort(R,len-ort);  // Right
	merge(array,L,ort,R,len-ort);  
	// Merging L and R, build sorted A
	
	//give the fields back
	free(L);
    free(R);
		
	return array;
}
	
void merge(int *array,int *L,int leftCount,int *R,int rightCount) {
	int i=0,j=0,k=0;

	//compare the elements to sort
	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) array[k++] = L[i++];
		else array[k++] = R[j++];
	}
	//combine
	while(i < leftCount) 
	array[k++] = L[i++];
	while(j < rightCount) 
	array[k++] = R[j++];
}
	
	
int * bublesort(int * array,int len){
	int temp;
	
	for(int i=1;i<len;i++){
      for(int j=0;j<=len-1;j++){
           if(array[j]>array[j+1]){
               temp=array[j];
              array[j]=array[j+1];
              array[j+1]=temp;     }
	  }}
	  
	return array;
}

int writetofile(int *array,int len){
	FILE *ptr_file;
	ptr_file =fopen("sorted.txt","w");
	
	if (ptr_file==NULL)
		return 1;
	 
	for (int i = 0; i < len; i++)
     fprintf(ptr_file, "%d\n", array[i]);
	

	fclose(ptr_file);
	cout<<"Dosyaya yazma islemi basarili"<<endl;
	return 0;

}

int main(int argc,char * argv[])
{  	clock_t t;
	FILE *ptr_file;
	int j=0;
	//arguments from the command line
	int N=atoi(argv[2]);	
	char m=*argv[1];

    ptr_file =fopen("data.txt","r");
	   if (ptr_file==NULL)
    return 1;

    int  dizi[N];
	
	//read the file
	int num;
	int i=1;
	fscanf (ptr_file, "%d", &num); 
	dizi[0]=num;
	
    while (i<N)
    { fscanf (ptr_file, "%d", &num); 
	  dizi[i]= num;
	  i++;	       
    }

	//our array is ready for sorting

	switch(m){
	case 'b':	cout<<"Buble Sort Algorithm"<<endl; t=clock();bublesort(dizi,N); t=clock()-t; writetofile(dizi,N); printf("It took %f seconds",(float)t/CLOCKS_PER_SEC);	break;
	case 'm':	cout<<"Merge Sort Algorithm"<<endl;  t=clock();mergesort(dizi,N);  t=clock()-t;	writetofile(dizi,N); printf("It took %f seconds",(float)t/CLOCKS_PER_SEC);	break;
	default:	cout<<"Algoritma turunu yanlis girdiniz!"<<endl;
	}
	

	fclose(ptr_file);
	return 0;

	}

