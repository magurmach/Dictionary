#include <iostream>
#include <stdio.h>     //freopen used it
#include "AvlTree.h"
#include <cstddef>
#include "Dictionary.h"
#define FRO freopen("input 1.txt","r",stdin);
#define FROut freopen("out.txt","w",stdout);
using namespace std;


/**
 *
 * Expected Input File Format:
 * insert num   (inserts num as the key in the tree and outputs the height it has been inserted on
 * lookup num   (lookup for a node with key num and outputs if it has been found with)
 * clear        (clean the tree)
 * remove num   (remove the node with key num, if is in the tree)
 *
*/

int main(int argc, char **argv)
{
	FRO
	//FROut
	AVLTree<int,int> tree;
	int a,b;
	char x[15];
	while(cin>>x)
	{
		if(x[0]=='i')
		{
			cin>>a>>b;
			if(tree.insert(a,b))
			{
				cout<<"new insert"<<endl;
			}
			else
			{
				cout<<"update data"<<endl;
			}
		}
		else if(x[0]=='l')
		{
			cin>>a;
			AVLTree<int,int>::iterator it=tree.lookUp(a);
			if(it.isNullprt())
			{
				cout<<"not found"<<endl;
			}
			else cout<<it.getData()<<endl;
		}
		else if(x[0]=='r')
		{
			cin>>a;
			tree.remove(a);
		}
		else if(x[0]=='x')
		{
			break;
		}
		else if(x[0]=='c'){
			tree.clear();
		}
		else if(x[0]=='p'){
			AVLTree<int,int>::iterator it;
			cout<<"--------"<<endl;
			for(it=tree.begin();it!=tree.end();it++){
				cout<<it.getKey()<<" "<<it.getData()<<endl;
			}
			cout<<"--------"<<endl;
		}
	}
	Dictionary<int,int,AVLTree> mp;


	return 0;
}
