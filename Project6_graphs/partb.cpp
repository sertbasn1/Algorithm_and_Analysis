//============================================================================
// Name        : partb.cpp
// Author      : Nurefsan Sertbas
// Version     : 1.0
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <list>
using namespace std;

class graph
{   int nodecounter;    // Num of nodes in graph
    list<int> *adjacency; // Pointer to an array containing adjacency lists
 public:
    graph(int nodecounter);  
    void addEdge(int u, int v); //edge between u and v 
	int BFS(int start);

};
 
graph::graph(int nodecounter)
{   this->nodecounter = nodecounter;
    adjacency = new list<int>[nodecounter];
}
 
void graph::addEdge(int u, int v)
{   adjacency[u].push_back(v); // Add v to u’s list.
}
 
int graph::BFS(int start)
{   list<int> BFSqueue;
	int num=0;
	// From the pseudeo code on Recitation2 page 5/44
    bool *visited = new bool[nodecounter];
    for(int i = 0; i < nodecounter; i++) //for all ndoes
        visited[i] = false;
		
    visited[start] = true; //first nodecounter
    BFSqueue.push_back(start);
    list<int>::iterator i; //to explore adjmat
 
    while(!BFSqueue.empty())
    {   start = BFSqueue.front();
		num++;
        BFSqueue.pop_front();
 
		for(i = adjacency[start].begin(); i != adjacency[start].end(); ++i)
        {   if(!visited[*i])
            {   visited[*i] = true;
                BFSqueue.push_back(*i);
            }
        }
    }
	return num;
}

int main(){
	char nodes[2];
	cout<<"Enter two nodes to computes betwennnes (ex: AB)"<<endl;
	cin>>nodes;
	char node1=nodes[1];
	char node2=nodes[0];
	
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
			
/*Part b*/
	int s = node1-65, d = node2-65;
	int adjmat1[linenum][linenum];
		
	for(i=0;i<linenum;i++){
		for(k=0;k<linenum;k++){
		if( (i==s && k==d) || (i==d && k==s) )
			adjmat1[i][k]=0;
		else
			adjmat1[i][k]=adjmat[i][k];				  
			}
		}
		
	for(k=0;k<linenum;k++){
		if( (adjmat1[s][k]==1) && (adjmat1[d][k]==1)) //ortak nodecounter
			{for(i=0;i<linenum;i++)
			adjmat1[k][i]=0;
			for(i=0;i<linenum;i++)
			adjmat1[i][k]=0;}
		 }

	graph g1(linenum);
	for(i=0;i<linenum;i++){
		for(k=0;k<linenum;k++){
		if(adjmat1[i][k]==1)//edge varsa
		g1.addEdge(i,k);}
		}
					
	int n1=g1.BFS(s);
	int n2=g1.BFS(d);	
	cout<<"Betweennes of("<<node1<<","<<node2<<"):"<<n1<<"*"<<n2<<"="<<n1*n2<<endl;
	return 0;
}

