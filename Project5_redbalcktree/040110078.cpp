//Nurefsan Sertbas
//040110078

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
using namespace std;

/*RBTree implemantation*/
struct node
{      int key;
	   char * name;
	   char * gender;
       node *parent;
       char color;
       node *left;
       node *right;
};
class RBTree
{     node *root;
      node *tmp;

	public :
      RBTree()
      {tmp=NULL;
       root=NULL;}
	   
      void insert(node *t);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void disp();
      void display( node *);
	  void display2(node *);
};
void RBTree::insert(node *t)
{
     int z,i=0;
     node *p,*tmp;
    
     p=root;
     tmp=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              tmp=p;
              if(p->key<t->key)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=tmp;
         if(tmp->key<t->key)
              tmp->right=t;
         else
              tmp->left=t;
     }
     insertfix(t);
}
void RBTree::insertfix(node *t)
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}


void RBTree::leftrotate(node *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBTree::rightrotate(node *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

void RBTree::disp()
{
     display2(root);
}

void RBTree::display2(node *p)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n Root NODE: ";
                cout<<"\n Key: "<<p->key;
				cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key;
                else
                       cout<<"\n There is no parent";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key;
                else
                       cout<<"\n There is no right child";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key;
                else
                       cout<<"\n There is no left child";
                cout<<endl;
    if(p->left){
     cout<<"\n\nLeft:\n";
     display(p->left); }

    if(p->right)
    {cout<<"\n\nRight:\n";
     display(p->right);}
    }
}

void RBTree::display(node *p)
{ //inorder reprssentation
    if (p != NULL) {
        display(p->left);
        printf("[%2d]\t", p->key);
        display(p->right);
    }
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

int main(int argc,char * argv[])
{  	//arguments from the command line
	char * filename=argv[0];	
	FILE *ptr_file;
	int j=0;
	RBTree obj;
	char * pch;
	int i=0; 	
	int k;
	char line[256];

/*Read from file and insert into RBTree*/

//open file 

   	 ptr_file =fopen(filename,"r");
	   if (ptr_file==NULL)
    		return 1;


    while(fgets(line, sizeof(line), ptr_file)!=NULL){
	//for each line
	node *tmp=new node;
	k=0;
	pch = strtok (line," \t");
	while (pch != NULL)
	{ k++;
    //printf ("%d %d %s\n",k,i,pch);
    if(k==1) tmp->name=pch;
	if(k==2) tmp->gender=pch; 
    if(k==3) tmp->key=atoi(pch);
	
    pch = strtok (NULL, " \t");
     tmp->left=NULL;
    tmp->right=NULL;
    tmp->color='r';
	}
	///////////////
	obj.insert(tmp);
	printf( "insert edilen node: %s %s %d\n", tmp->name, tmp->gender, tmp->key );
	i++;	
	}	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
 obj.disp();



	
	fclose(ptr_file);
    return 0;
}
		
		
		
		
		

