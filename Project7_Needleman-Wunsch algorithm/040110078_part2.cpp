#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
vector<char>::iterator it;
vector<char>::iterator it2;
vector<char>::iterator myit;

vector<char> seq1;
vector<char> seq2;
int matrixsize=24;
int sub_matrix[24][24];
vector<char> header;

int maxof(int x,int y, int z){
	int max=x;
	if(y>max)
		max=y;
	if(z>max)
		max=z;
		
	return max;
}

void readSubstitutionMatrix(){
	char line[256];
	
	FILE *ptr_file=fopen("BLOSUM62.txt", "r");
	if(ptr_file==NULL) {
		printf("An error has occured: can't open file\n");  
		exit(1);}

	char * buffer=fgets(line, sizeof(line), ptr_file);
	while(buffer[0]=='#')
		buffer=fgets(line, sizeof(line), ptr_file);
	
	//7. satırı okumus olacak
	char ch = 'x';
	int count=0;
	while (ch != '\n' ) {
		ch=buffer[count++];
		if(ch!=' ')
		header.push_back(ch);
	}
	header.pop_back(); //ARNDCQEGHILKMFPSTWYVBZX*
	
    int i=0,j=0,k=0;
	char tmp;
	while(i<matrixsize){//dosyanın sonuna gelmediği sürece
		buffer=fgets(line, sizeof(line), ptr_file);
		for(k=3;k<strlen(buffer);k=k+3){
				tmp=buffer[k-1];				
				if(tmp==' ')
					sub_matrix[i][j++]=atoi(&buffer[k]);
				else if(tmp=='-')
					sub_matrix[i][j++]=-1*atoi(&buffer[k]);
				else{ 
					char m[2];
					m[0]=buffer[k-1];
					m[1]=buffer[k];
					sub_matrix[i][j++]=atoi(m);	
					}
		}
		i++;//next row
		j=0;		
	}		
	 
	fclose(ptr_file);
}

void readFastaSeq(){
	char line[256];
	vector<char>::iterator it;
	
	FILE *ptr_file=fopen("human-hemoglobin-sequence.fasta", "r");
	if(ptr_file==NULL) {
		printf("An error has occured: can't open file\n");  
		exit(1);}

	char * fileinfo=fgets(line, sizeof(line), ptr_file);
	char ch = 'x';
	seq1.push_back(ch);

	while (ch != EOF ) {
		ch=(char)fgetc(ptr_file);
		if(ch!='\n')
		seq1.push_back(ch);
	}
	
	seq1.pop_back();
		
	//reading the second sequence
	ptr_file=fopen("mouse-hemoglobin-sequence.fasta", "r");
	if(ptr_file==NULL) {
		printf("An error has occured: can't open file\n");  
		exit(1);}

	fileinfo=fgets(line, sizeof(line), ptr_file);
	ch = 'x';
	seq2.push_back(ch);
	while (ch != EOF ) {
		ch=(char)fgetc(ptr_file);
		if(ch!='\n')
		seq2.push_back(ch);
	}
	
	seq2.pop_back();
	fclose(ptr_file);

}

int getSubstitutionValue(char c1,char c2){
	int ix=0;
	char elements[matrixsize];
	
	for (myit=header.begin(); myit != header.end(); ++myit)
		elements[ix++]=*myit;
	
	int i=0,j=0;
	
	while(elements[i]!=c1)
		i++;
	while(elements[j]!=c2)
		j++;
	
	return sub_matrix[i][j];	
}

int main(){
	int i=0,j,k;
	vector<char> directions;
	vector<char> aligned_seq1;
	vector<char> aligned_seq2;
	vector<char> aligned_sign;

	readFastaSeq();
	readSubstitutionMatrix();
	
	int M=seq1.size();
	char cseq1[M];
	int N=seq2.size();
	char cseq2[N];
	int a=0,b=0;	
	
	for (it=seq1.begin(); it != seq1.end(); ++it){
		cseq1[a]=*it;
		//cout<<cseq1[a];
		a++;			
	}

	for (it=seq2.begin(); it != seq2.end(); ++it){
		cseq2[b]=*it;
		//cout<<cseq2[b];
		b++;			}
		
	
	int matrix[N][M];//zaten M+1 N+1
	char directions_matrix[N][M];

	int gap=1;
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
			Sij=getSubstitutionValue(cseq1[j],cseq2[i]);
						
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
	// cout<<endl<<"Generated matrix:"<<endl;
	// for(i=0;i<N;i++){
		// for(j=0;j<M;j++)
			// cout<<matrix[i][j]<<" ";
		// cout<<endl;
	// }	
	
	// cout<<endl<<"Solution:"<<endl;
	// for(i=0;i<N;i++){
		// for(j=0;j<M;j++)
			// cout<<solution[i][j]<<" ";
		// cout<<endl;
	// }		
			
	i=1;

	 for (it=directions.end(); it != directions.begin()-1; it--){
			if(*it=='U')
			{aligned_seq1.push_back('_');}
			else if(*it=='K' || *it=='S') 
			{aligned_seq1.push_back(cseq1[i]);i++;}
	}
	i=1;	
	 for (it=directions.end(); it != directions.begin()-1; it--){
			if(*it=='S')
			{;aligned_seq2.push_back('_');}
			else if(*it=='K' || *it=='U') 
			{aligned_seq2.push_back(cseq2[i]); i++;}
	}


	
	int temp=0;
	int match=0;      //|
	int missmatch=0;  //.
	int similarity=0; //:


	it2=aligned_seq2.begin();
	it=aligned_seq1.begin(); 
	myit=aligned_sign.begin(); 
	int score=0;

	while(it != aligned_seq1.end()){
		//count matches,similarities	
			if(*it==*it2 ){
				match++;
				score=score+getSubstitutionValue(*it,*it2);	
				aligned_sign.push_back('|');
			}
			else if(*it!='_' && *it2!='_' ){//count missmatches and similarity
				temp=getSubstitutionValue(*it,*it2);
				if(temp>0){//:
				similarity++;
				aligned_sign.push_back(':');}
				else{
				missmatch++;
				aligned_sign.push_back('.');}
			}
			else 
				aligned_sign.push_back(' ');
		++it2; ++it;
	}

	
	//PRINT RESULTS
	cout<<"One of the optimal alignment is"<<endl;
	it=aligned_seq1.begin();
	myit=aligned_sign.begin();
	it2=aligned_seq2.begin();
	int bar=100;	
	while(bar--)   {cout<<*it;it++;}
	bar=100;	cout<<endl;
	while(bar--)   {cout<<*myit;myit++;}
	bar=100;    cout<<endl;
	while(bar--)   {cout<<*it2;it2++;}
	
	
	cout<<endl<<endl;
	
	while(it!=aligned_seq1.end()) 	  {cout<<*it;it++;}
	cout<<endl;
	while(myit!=aligned_sign.end())   {cout<<*myit;myit++;}
	cout<<endl;
	while(it2!=aligned_seq2.end())    {cout<<*it2;it2++;}
	cout<<endl<<endl;
	
	//Print Summary of work	
	int length=aligned_seq1.size();
	int numofgap=(length-(a-1))+(length-(b-1)); //-1 for x character
	cout<<endl<<"##########	SUMMARY	##########"<<endl;
	cout<<"Length(with gap)  :"<<length<<endl;
	cout<<"Identity  	   	 :"<<match<<"/"<<length<<"  "<<100*match/length<<"(%)"<<endl;
	cout<<"Similarity     	 :"<<similarity<<"/"<<length<<"  "<<100*similarity/length<<"(%)"<<endl;
	cout<<"Gaps           	 :"<<numofgap<<"/"<<length<<"  "<<100*numofgap/length<<"(%)"<<endl;
	cout<<"Score          	 :"<<score<<endl;

	return 0;
}
