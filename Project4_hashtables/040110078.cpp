//Nurefsan Sertbas
//040110078

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
const int m = 100;
 


//structure to hold id and data
struct data {
public:
		int id; // unique id for an element
		int data; // data for an element
};

class hashing {
		data htable[m]; //hashed data structs  >>table
		int counter; //number of elements in table
public:
		hashing();
		int hash(int &id);
		int rehash(int &id);
		int add(data &d);
		int remove(data &d);
		void display();
};


int hashing::hash(int &id) {
		return (id%m);
}
/*rehash function in case of ay collision*/
int hashing::rehash(int &id) {
		return ((id+1)%m);
}

hashing::hashing() {
		//create an array of data structure
		int i;
		for(i=0;i<m;i++) {
				htable[i].id = -1; //set all ids to -1(empty)
				htable[i].data = 0; //set all data values to 0 (default)
		}
		counter = 0;
}

int hashing::add(data &d) {
		if(counter < m) {
				int hashed = hash(d.id);
				if(hashed >= 0 && hashed <m && htable[hashed].id == -1) {
						//slot is empty, assign new data
						htable[hashed].id = d.id;
						htable[hashed].data = d.data;
						return 0;
				} else {
						
			int i=0;
			//to find an empty place
			while(i<m) {
							hashed = rehash(hashed);
							if(htable[hashed].id == -1) {
									htable[hashed].id = d.id;
									htable[hashed].data = d.data;
									return 0;
							} else if(i==m-1) {
									
									return -1; //terminate function with error 
							}
				i++; 
			}
				}
		} else {
				//table is full
				return (-1);
		}
}

int hashing::remove(data &d) {
		int hashed = hash(d.id);
		if(htable[hashed].id == d.id) {
				htable[hashed].id = -1;
				counter -= 1;
				return 0;
		} else {
			
		int i=0;
		while(i<m) {
					hashed = rehash(hashed);
					if(htable[hashed].id == d.id) {
							htable[hashed].id = -1; //set the id to -1 because it is going to be empty>>marked
							counter -= 1; //decrease 1 from number of elements
							return 0; 
					} else if(i==m-1) {
							return -1; 
			}
			i++;
				}
		}
}

void hashing::display() {
		int i;
		for(i=0;i<m;i++) {
				cout<<i<<":"<<htable[i].id<<endl;
		}
}

int main()
{
	FILE *ptr_file;
	int linenum=0;	
	int j=0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
/*FILE OPERATIONS*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

//open file 
   	 ptr_file =fopen("dataset.txt","r");
	   if (ptr_file==NULL)
   		 return 1;


//find the number of lines by reaching EOF
    char line[256];
    while (fgets(line, sizeof(line), ptr_file)) {
   		linenum++;    }

//take cursor to the start of the file
   	fseek(ptr_file,0,SEEK_SET);

   	int key[linenum];
    char *instruction[linenum];


//read the file and tokenize each line
	int i=0; 	char * pch;
	while (fgets(line, sizeof(line), ptr_file)) {
	char * pch=strtok (line,":");
	int k=0;
    while (pch) {
        if(k==0)
          instruction[i]=pch;
        else
          key[i]=atoi(pch);
    k++;
    pch = strtok(NULL, " ");}
				
	i++;  	  
    }
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
/*ALgorithm*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	data d;
	hashing h1;
	
	 
    int op;
  
	for(int i=0;i<linenum;i++){
	
	if (strcmp(instruction[i],"insert")==0)
		op=1;
	else if (strcmp(instruction[i],"delete")==0)
		op=2;
	//else if (strcmp(instruction[i],"retrieve")==0)
	//	op=3;
		
		switch(op){
	case 1:	 
			cout<<"İnsert operation with key:"<<key[i]<<endl;
            d.id=key[i];
			h1.add(d);
		    break;
	
	case 2:
			cout<<"Delete operation with key:"<<key[i]<<endl;
		    d.id=key[i];
			h1.remove(d);
			break;
	default:
			cout<<"Retrieve operation with key:"<<key[i]<<endl;
		continue;
		}		
	}
		
	cout<<"At the end of the program table is like that:"<<endl;
	h1.display();
	
	fclose(ptr_file);
    return 0;
}
		
		
		
		
		

