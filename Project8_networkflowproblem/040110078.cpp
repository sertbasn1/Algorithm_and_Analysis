//============================================================================
// name        : 040110078.cpp
// Author      : nurefsan Sertbas
// Version     : 1.0
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <vector>


using namespace std;
#define INFINITE 10000000
int augpath[6];
int pindex;


int findpath (int m, int n, int ** Flow, int * assigned, int ** adjmat,int * capofRobots,int * load, int s, int t, int minimum)
{  int N=m+n+2;
    assigned[s] = true;
    if (s == t)
        return minimum;
    
    for (int i = 0; i < N; i++) {
        int flow_capacity = adjmat[s][i] - Flow[s][i];
        if (!assigned[i] && flow_capacity > 0)
        {   if(pindex==2 && load[s]==capofRobots[s])
            break;
            
            augpath[pindex++]=s;  augpath[pindex++]=i;
            // find min capacity in augment. path
            if (int sent = findpath (m,n,Flow,assigned,adjmat,capofRobots,load,i, t, min (minimum, flow_capacity)))
            {
                // update capacity
                Flow[s][i] += sent;
                Flow[i][s] -= sent;
                return sent;
            }
        }
    }
    
    return false;
}


int main() {

    /*FILE OPERATIONS*/
	FILE *ptr_file;
     //open file
	 ptr_file =fopen("input.txt","r");
	 if (ptr_file==NULL)
	 	 return 1;

	//find the number of lines by reaching EOF
	    char line[256];
	    fgets(line, sizeof(line), ptr_file);
        char *token = strtok(line, " ");
        int m=atoi(token);
        token = strtok(NULL, " ");
        int n=atoi(token);

        cout<<"m:"<<m<<endl;
        cout<<"n:"<<n<<endl;
     
        int List[m][n];//which object can be carried by which robot
						
	//read the file and tokenize each line
     int i=0,k=0;
     int counter=0;
		while (counter<m) {
			fgets(line, sizeof(line), ptr_file);
			token = strtok(line, " ");
			List[counter][0]=atoi(token);
            k=1;
			while (k<n) {
			token = strtok(NULL, " ");
			List[counter][k]=atoi(token);
			k++;    		}
        counter++;
        }
    
    int *capofRobots=(int *)malloc(n*sizeof(int));
    i=0;
    fgets(line, sizeof(line), ptr_file);
    token = strtok(line, " ");
    capofRobots[i++]=atoi(token);
    while (i<n) {
        token = strtok(NULL, " ");
        capofRobots[i++]=atoi(token);
    }
    
// cheching the data read from the file
//    for(i=0;i<m;i++)
//         for(k=0;k<n;k++){
//             cout<<List[i][k];
//             if(k==n-1)
//                 cout<<endl;
//         }
//    
//    for(k=0;k<n;k++)
//        cout<<capofRobots[k];
//    cout<<endl;
    
    int N=m+n+2;
    int s = 0;
    int t = N-1;
   
    
    int **Flow=(int **)malloc(N*sizeof(int *));
    for(i=0;i<N;i++)
        Flow[i]=(int *)malloc(N*sizeof(int));
    
    int **adjmat=(int **)malloc(N*sizeof(int *));
    for(i=0;i<N;i++)
        adjmat[i]=(int *)malloc(N*sizeof(int));
    
    int *assigned=(int *)malloc(N*sizeof(int));
    
    int *load=(int *)malloc(n*sizeof(int));
    
    
    for(i=0;i<N;i++)
        for(k=0;k<N;k++){
            adjmat[i][k]=0;
    }

    for(i=0;i<N;i++)
        for(k=0;k<N;k++){
            Flow[i][k]=0;
    }
    
    for(i=0;i<N;i++)
            assigned[i]=0;
    
    for(i=0;i<n;i++)
        load[i]=0;
    
    
    
    
  
    //sink-robot edges
    adjmat[0][0]=0;
    for(i=1;i<N;i++){
        if(i<n+1)
            adjmat[0][i]=1;
    }
    for(i=1;i<N;i++){
        if(i<n+1)
            adjmat[i][0]=1;
    }
    
    
    //object-robot edges
    for(i=1;i<n+1;i++){
        for(k=(n+1);k<(m+n+1);k++){
            adjmat[i][k]=List[k-(n+1)][i-1];
        }
    }
    
    for(i=n+1;i<(m+n+1);i++){
        for(k=1;k<(n+1);k++){
            adjmat[i][k]=List[i-5][k-1];
        }
    }
    
    
    //object-terminaiton edges
    for(i=0;i<N;i++){
        if(i>=n+1)
            adjmat[(m+n+1)][i]=1;
    }
    for(i=0;i<N;i++){
        if(i>n)
            adjmat[i][(m+n+1)]=1;
    }
    
     adjmat[N-1][N-1]=0;
    
    
    cout<<endl<<"Adjacency Matrix of the network:"<<endl;
    
    for(i=0;i<N;i++)
        for(k=0;k<N;k++){
            cout<<adjmat[i][k];
            if(k==(m+n+1))
                cout<<endl;
        }
    
    //aply the algorithm
    int max_flow = 0;
    int tmp=0;
    vector<int> temp_foundassgnments;
    pindex=0;
    cout<<endl<<"Augmented Paths and Assignments:"<<endl;
    // while there is augmenting path , from s and t
    int c=m/n;
    
    while(c--){
    while (int sent = findpath (m,n,Flow,assigned,adjmat, capofRobots,load,s, t, INFINITE))
    {
        for(i=0;i<6;i++){
            if(augpath[5]==t)
            {
            if(i!=2 && i!=3){
                cout<<augpath[i];
                if(i!=5)
                    cout<<"-->";}
        }
}
        cout<<endl;
        
        if(augpath[5]==t){
        temp_foundassgnments.push_back(augpath[2]);
            temp_foundassgnments.push_back(augpath[3]);}

        
        max_flow += sent;
        for(i=0;i<N;i++)
            assigned[i]=0;
        for(i=0;i<6;i++)
            augpath[i]=0;
        pindex=0;
    }
    
    
    for(i=0;i<8;i=i+2){
        adjmat[temp_foundassgnments[i]][temp_foundassgnments[i+1]]=0;
        adjmat[temp_foundassgnments[i+1]][temp_foundassgnments[i]]=0;
    }
        
    for(i=0;i<N;i++)
        for(k=0;k<N;k++){
            Flow[i][k]=0;
        }
    
    for(i=0;i<N;i++)
        assigned[i]=0;
        
    
}
    
    int x=0;
    int matchcount=temp_foundassgnments.size();
    if(matchcount==0)
        cout<<"There is no such an assignment"<<endl;
    
    else{

    while(!temp_foundassgnments.empty())
    {
    cout<<"Assignment: Object "<<temp_foundassgnments.back()-n;
    temp_foundassgnments.pop_back();
    x=temp_foundassgnments.back();
        load[x-1]+=1;
    cout<<" assigned to Robot"<<x<<endl;
    temp_foundassgnments.pop_back();
    }

    cout <<"Num of matchings: "<< matchcount/2<<endl;
    }
	return 0;
}

