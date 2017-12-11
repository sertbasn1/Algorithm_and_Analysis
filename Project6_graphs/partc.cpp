//============================================================================
// Name        : partc.cpp
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

struct edge{
    public:
	int node1;
    int node2;
    int degr;
	bool isexist(int n1,int n2);
};

class graph
{   int nodecounter;    // Num. of nodecounters in graph
 public:
    list<int> *adjacency; // Pointer to an alledges containing adjacency lists
    graph(int nodecounter);  
    void addEdge(int u, int v); //edge between u and v
	void deleteEdge(int u, int v);
	void printpath(int , int , bool [], int [], int &);
	int BFS(int start); 
};
 
graph::graph(int nodecounter)
{   this->nodecounter = nodecounter;
    adjacency = new list<int>[nodecounter];
}
 
void graph::addEdge(int u, int v) //(u,v)
{   adjacency[u].push_back(v); // Add v to u’s list.
}

 void graph::deleteEdge(int u, int v)
{   int i;
	int size=adjacency[u].size();

        for (i =0;i<size; ++i)
            if(i==v)
			{adjacency[u].remove(v);
			adjacency[v].remove(u);
			cout<<"silind";}
}

void graph::printpath(int u, int d, bool visited[],int path[], int &path_index)
{   visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    // If we reach the termination nodecounter
	int length=0;
    if (u == d)
    {   for (int i = 0; i<path_index; i++){
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
            if(i!=path_index-1)
			{ cout << c << "->";
			  length++;}
            else
			cout << c << "\t\t"<<"Path Length:"<<length<<endl;
				 											}			
    }
    else // If it is not termination
    {   list<int>::iterator i;
        for (i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
            if (!visited[*i])
                printpath(*i, d, visited, path, path_index);
    }
 
    path_index--;
    visited[u] = false;
}

int graph::BFS(int start)
{   list<int> BFSqueue;
	int num=0;
	// From the pseudeo code on Recitation2 page 5/44
    bool *visited = new bool[nodecounter];
    for(int i = 0; i < nodecounter; i++) //for all ndoes
        visited[i] = false;
 
    visited[start] = true; //first node
    BFSqueue.push_back(start);
    list<int>::iterator i; //to explore adjmat
 
    while(!BFSqueue.empty())
    {   start = BFSqueue.front();
		int tmp=start;
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
        cout << c << " ";
		num++;
        BFSqueue.pop_front();
 
		for(i = adjacency[start].begin(); i != adjacency[start].end(); ++i)
        {   if(!visited[*i])
            {   visited[*i] = true;
                BFSqueue.push_back(*i);
            }
        }
    }
	cout << endl;
	return num;
}


 int main() {
	 
/*FILE OPERATIONS*/
	FILE *ptr_file;
	int linenum=0;

	//open file
	 ptr_file =fopen("input2.txt","r");
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
			

    //construct graph from the adjacency matrix that read from file
	graph g(linenum);
		 for(i=0;i<linenum;i++){
			  for(k=0;k<linenum;k++){
				  if(adjmat[i][k]==1)//edge varsa
				  g.addEdge(i,k);}
				}
	
	struct edge reversed[50];
	int x=0;
	
	graph grev(linenum);
	
	cout<<"Graph is reversed new edges are:"<<endl;
	for(k=0;k<linenum;k++){
		list<int> tmp;
		tmp.assign (g.adjacency[k].begin(),g.adjacency[k].end()); //holds edges of kth line
		while(!tmp.empty()){
		struct edge tmpedge;
		//change directions to opposite
		tmpedge.node1=tmp.front(); 
		tmpedge.node2=k;
		tmp.pop_front();
		reversed[x]=tmpedge;
		grev.addEdge(tmpedge.node1,k);
		cout<<reversed[x].node1<<"-"<<reversed[x].node2<<endl;
		x++;		}
	 }
	
	cout<<"BFS for graph:"<<endl;
	int n1=0;
	n1=g.BFS(0);
	cout<<"BFS for reversed graph:"<<endl;
	int n2=0;
	n2=grev.BFS(0);
	cout<<n1<< "nodes in g and "<<n2<<" nodes in grev are visited"<<endl;
	if(n1==n2 && n2==linenum)
		cout<<"Graph is strongly connected"<<endl;
	else
		cout<<"Graph is not strongly connected"<<endl;
		
	return 0;
}
