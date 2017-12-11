//============================================================================
// Name        : parta.cpp
// Author      : Nurefsan Sertbas
// Version     : 1.0
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <list>

using namespace std;
int shortestpathlength=100;//like infinite
int pcounter=0;
int mypaths[10][10]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
					 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
					 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
					 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
					 {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1} };

struct graphpat{
	public:
	int pno;
	int nodes[20];
    int length;
	void addNode(int pno,int node);
	int findlength(int pno);
};

struct graphpat allpaths[50]; 
void addNode(int pno,int node){
	int l=allpaths[pno].length;
	allpaths[pno].nodes[l]=node;
	allpaths[pno].length++;
}
int findlength(int pno){
	return allpaths[pno].length;
}

class graph
{   int nodecounter;    // Num of nodes in graph
    list<int> *adjacency; // Pointer to an array containing adjacency lists
 public:
    graph(int nodecounter);  
    void addEdge(int u, int v); //edge between u and v 
	void deleteEdge(int u, int v);
	void printpath(int , int , bool [], int [], int &);

};
 
graph::graph(int nodecounter)
{   this->nodecounter = nodecounter;
    adjacency = new list<int>[nodecounter];
}
 
void graph::addEdge(int u, int v)
{   adjacency[u].push_back(v); // Add v to u’s list.
}
 
 void graph::deleteEdge(int u, int v)
{   int i;
	int size=adjacency[u].size();

        for (i =0;i<size; ++i)
            if(i==v)
			{adjacency[u].remove(v);
			adjacency[v].remove(u);
			}
}
void  graph::printpath(int u, int d, bool visited[],int path[], int &pi)
{  
	visited[u] = true;
    path[pi] = u;
    pi++;
	
    // If we reach the termination nodecounter
	int length=0;	

    if (u == d)
    {   cout << "Path " << pcounter+1 <<": ";
		for (int i = 0; i<pi; i++){
		int tmp=path[i];
				char  c;
				switch(tmp){
					case 0:c='A'; break;
					case 1:c='B'; break;
					case 2:c='C'; break;
					case 3:c='D'; break;
					case 4:c='E'; break;
					case 5:c='F'; break;
					case 6:c='G'; break;
					case 7:c='H'; break;
				}
            if(i!=pi-1)
			{ cout << c << "->";
				length++;
				mypaths[pcounter][length-1]=tmp;
				}
            else
			{	int i=length;
				mypaths[pcounter][i]=tmp;
				cout << c << "\t\t"<<"Path Length:"<<length<<endl;
				 pcounter++;
			 if(length<shortestpathlength)
				 shortestpathlength=length;
			 length=0;
			}	 
											}			
    }
    else // If it is not termination
    {   list<int>::iterator i;
        for (i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
            if (!visited[*i]){
                printpath(*i, d, visited, path, pi);				
			}
    } 
    pi--;
    visited[u] = false;
}

 int main() {
	 
/*FILE OPERATIONS*/
	FILE *ptr_file;
	int linenum=0;

	//open file
	 ptr_file =fopen("input1.txt","r");
	 if (ptr_file==NULL)
	 	 return 1;

	//find the number of lines by reaching EOF
	    char line[256];
	    while (fgets(line, sizeof(line), ptr_file)) {
	   		linenum++;    }

	//take cursor to the start of the file
	   	fseek(ptr_file,0,SEEK_SET);
	  	int adjmat[linenum][linenum];
						
	//read the file and tokenize each line
		int i=0,k=0,counter=0;
		while (counter<linenum) {
			fgets(line, sizeof(line), ptr_file);
			char *token = strtok(line, " ");
			adjmat[counter][0]=atoi(token);	
			k=1;
			while (k<linenum) {
			token = strtok(NULL, " ");
			adjmat[counter][k]=atoi(token);
			k++;    		}
		
		counter++;
	    }

	cout<<"Adjacency Matrix of the Graph:"<<endl;
		 for(i=0;i<linenum;i++)
			  for(k=0;k<linenum;k++){
			  cout<<adjmat[i][k];
			  if(k==linenum-1)
				  cout<<endl;
			}
			
/*Part a*/		
    //construct graph from the adjacency matrix that read from file
	graph g(linenum);
		 for(i=0;i<linenum;i++){
			  for(k=0;k<linenum;k++){
				  if(adjmat[i][k]==1)//edge varsa
				  g.addEdge(i,k);}
				}
	
	char sourcenodecounter='A';
	char terminatenodecounter='G';
	
	
    int s = sourcenodecounter-65, d = terminatenodecounter-65;
    cout << "All possible paths from " << sourcenodecounter << " to " << terminatenodecounter << endl;
    
		
	bool *visited = new bool[linenum];
    int *path = new int[linenum]; //holds all nds
    int pi = 0; 
 
    for (int i = 0; i < linenum; i++)
        visited[i] = false;
	
	g.printpath(s, d, visited, path, pi);
	
	
	int m=pcounter;
	while(m--){
		int i=0,j=0;
		struct graphpat tmppath;
		tmppath.pno=m;
		while(mypaths[m][j]!=-1){
			tmppath.nodes[j]=mypaths[m][j];
			addNode(m,mypaths[m][j]);
			j++;
		}
		tmppath.length=j-1;
		allpaths[m]=tmppath;		
	}

	m=pcounter;
	int t;
	//RESULTS//
	cout<<"*** *** *** *** ***"<<endl;
	
	cout<<"Shortest Path length:"<<shortestpathlength<<endl;
	cout<<"Shortest Path(s):"<<endl;
	
	while(m--){
		if((t=findlength(m))==shortestpathlength)
			 cout<<"Path "<<m+1<<endl;
	 }
	
	cout<<"*** *** *** *** ***"<<endl;
		
	return 0;
}
