#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;

int maxof(int x,int y, int z){
	int max=x;
	if(y>max)
		max=y;
	if(z>max)
		max=z;
		
	return max;
}


int main(){
	//char const* seq1="xISALIGNED";
	//char const * seq2="xTHISLINE";
	
	//char const* seq1="xACTGATTCA";
	//char const * seq2="xACGCATCA";
	
	char const* seq1="xGAATTCAGTTA";
	char const * seq2="xGGATCGA";
	
	int M=strlen(seq1);
	int N=strlen(seq2);
	vector<char> directions;
	vector<char> aligned_seq1;
	vector<char> aligned_seq2;
	vector<char>::iterator it;
	vector<char>::iterator it2;

	int matrix[N][M];//zaten M+1 N+1
	char directions_matrix[N][M];
	int i,j,k;
	
	int gap=0;
	int Sij;	
	//initialization for column 0 and row 0
	for(i=0;i<M;i++)
		matrix[0][i]=i*gap;
	for(i=0;i<N;i++)
		matrix[i][0]=i*gap;
	
	
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			directions_matrix[i][j]='X';
		
	directions_matrix[0][0]='B'; //sign to check whether we arrive at starting point or not(baslangıc)
	
	int tmp;
	////filling table
	for(i=1;i<N;i++){
		for(j=1;j<M;j++){
			if(seq1[j]==seq2[i])
				Sij=1; //match
			else
				Sij=0;//missmatch
			
			tmp=maxof(	matrix[i-1][j-1]+Sij,
						matrix[i][j-1]+gap,
						matrix[i-1][j]+gap		);
						
			if(tmp==matrix[i-1][j-1]+Sij) //köseden gelmis
				directions_matrix[i][j]='K';
			else if(tmp==matrix[i][j-1]+gap) //soldan gelmis
				directions_matrix[i][j]='S';
			else
				directions_matrix[i][j]='U'; //ustten gelmis
			
			matrix[i][j] =tmp;
							
		}}
	
	
	//tracing back
	int solution[N][M];
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			solution[i][j]=0;
			
	i=N-1;j=M-1;	
	solution[i][j]=matrix[i][j];
	char dir='U';
	
	while(dir!='B'){
			dir=directions_matrix[i][j];
		
			if(dir=='K')
			 {j--;i--; directions.push_back('K');}
			else if(dir=='S')
			  {j--; directions.push_back('S');}
			else if(dir=='U')
			  {i--;directions.push_back('U');}
		    else if(dir=='X')
			  {i--;directions.push_back('U');}
			 
			 solution[i][j]=matrix[i][j]; 
	}
	
	//print matrix
	cout<<endl<<"Generated matrix:"<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++)
			cout<<matrix[i][j]<<" ";
		cout<<endl;
	}	
	
	cout<<endl<<"Solution:"<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++)
			cout<<solution[i][j]<<" ";
		cout<<endl;
	}
	
 //cout<<endl;
 //for ( it=directions.end(); it != directions.begin()+1; it--)
 //		cout <<" "<< *it;
 //cout<<endl;

cout<<endl<<"One of the optimal alignment is"<<endl;
i=1;
//print seq1
 for (it=directions.end(); it != directions.begin()-1; it--){
		if(*it=='U')
		{cout<<"_"; aligned_seq1.push_back('_');}
		else if(*it=='K' || *it=='S') 
		{cout<<seq1[i];aligned_seq1.push_back(seq1[i]);i++;}
}
cout<<endl;
i=1;
//print seq2
 for (it=directions.end(); it != directions.begin()-1; it--){
		if(*it=='S')
		{cout<<"_";aligned_seq2.push_back('_');}
		else if(*it=='K' || *it=='U') 
		{cout<<seq2[i]; aligned_seq2.push_back(seq2[i]); i++;}
}

cout<<endl;

int max_global_algnmnt_score=0;
it2=aligned_seq2.begin(); 
 for (it=aligned_seq1.begin(); it != aligned_seq1.end(); it++){
	if(*it!='_' && *it2!='_' )
			max_global_algnmnt_score++;
	it2++;
	}

cout<<endl<<"Max global alignment score is "<<max_global_algnmnt_score<<endl<<endl;
	
	return 0;
}
