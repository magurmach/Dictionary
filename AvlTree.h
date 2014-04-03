/*
 * $Revision: 1.5 $
 * 
 * last checkin:
 *   $Author: shakib008 $ 
 *   $Date: 2014-03-17 07:12:58 +0600 (Fr, 28 Mar 2014) $ 
 ***************************************************************/
 
/** \file
 * \brief Declaration of AVLTree stand alone version
 * 
 * \author Sheikh Sahkib Ahmed
 * 
 * \par License:
 * This file is part of the Open Graph Drawing Framework (OGDF).
 * Copyright (C) 2005-2007
 * 
 * \par
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 2 or 3 as published by the Free Software Foundation
 * and appearing in the files LICENSE_GPL_v2.txt and
 * LICENSE_GPL_v3.txt included in the packaging of this file.
 *
 * \par
 * In addition, as a special exception, you have permission to link
 * this software with the libraries of the COIN-OR Osi project
 * (http://www.coin-or.org/projects/Osi.xml), all libraries required
 * by Osi, and all LP-solver libraries directly supported by the
 * COIN-OR Osi project, and distribute executables, as long as
 * you follow the requirements of the GNU General Public License
 * in regard to all of the software in the executable aside from these
 * third-party libraries.
 * 
 * \par
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * \par
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * 
 * \see  http://www.gnu.org/copyleft/gpl.html
 ***************************************************************/


#ifdef _MSC_VER
#pragma once
#endif



#ifndef AVLTREE_H
#define AVLTREE_H

#define Max(a,b) a>b?a:b
#include <iostream>        //traverseInOrder
#include <cstdlib>         //free()
#include <cstddef>         //nullptr
#include <stack>           //iterator
using namespace std;


template <class T, class S> class AVLTree;

/**
 * 
 *The class is the base AVLNode template class
 *This class stores all info of AVL tree's node 
 *No direct creation of this class was expected
 *But if you want you can.
*/
template<class T, class S> class AVLNode
{
protected:
	AVLNode<T,S> *left, *right,*parent;
	T key;
	S data;
	int height;
	
	//!set key of this node
	/**
     * @param _key of type T which will be the key of this node
     */
	void setKey(T _key){
		key=_key;
	}
	
	//! assign a height to the node
	/**
     * @param _height of type int which will be the new height of this node
     */
	void setHeight(int _height){
		height=_height;
	}
	
	//! set a node x to be parent of thi node
	/**
     * @param parent of type AVLNode<T>* which will set as the parent of this node
     */
	void setParent( AVLNode<T,S> *_parent){
		parent=_parent;
	}
	
	//! set a node x as the left child of the node and this node as the parent of x
	/**
     * @param _left of type AVLNode<T>* which will set as the left child of this node
     */
	void setLeftChild( AVLNode<T,S> *_left){
		left = _left;
		if(_left==nullptr) return;
		_left->setParent(this ); //auto update parent
	}
	
	//! set a node as the right children of the node
	/**
     * @param _right of type AVLNode<T>* which will set as the right child of this node
     */
	void setRightChild( AVLNode<T,S> *_right){
		right = _right;
		if(_right==nullptr) return;
		_right->setParent(this); //auto update parent
	}
	
	//! set a data for the key
	/**
	 * @param class<S> _data to srote against class<T> _key
	 * */
	void setData(S _data){
		data=_data;
	}
	
	//! return the height of the node
	int getHeight(){
		return height;
	}
	//! return pointer to the parent of the node
	AVLNode<T,S> * getParent(){
		return parent;
	}
	
	//! return pointer to the left children of the node
	AVLNode<T,S> * getLeftChild(){
		return left;
	}
	
	//! return pointer to the right children of the node
	AVLNode<T,S> * getRightChild(){
		return right;
	}
	
	//! returns if a node is even balanced (returns 0) or left heavy (return 1) or right heavy (returns -1) or unbalanced
	int getBalanceProperty(){
		int leftH=0,rightH=0;
		if(left!=nullptr){
			leftH=left->getHeight();
		}
		
		if(right!=nullptr){
			rightH=right->getHeight();
		}
		
		return (leftH-rightH);
	}
	
	//! Returns if this node is left child of its parent
	bool isLeftChild(){
		if(parent==nullptr) return false;
		if(parent->getLeftChild()== nullptr) return false;
		return key == parent->getLeftChild()->getKey();
	}
	
	//! Returns if this node is right child of its parent
	bool isRightChild(){
		if(parent==nullptr) return false;
		if(parent->getRightChild()== nullptr) return false;
		return key == parent->getRightChild()->getKey();
	}
	
	//! Get Successor of a node
	AVLNode<T,S> * getSuccessor(){
		AVLNode<T,S> *temp=right;
		AVLNode<T,S> *ret=temp;
		while(temp!=nullptr){
			ret=temp;
			temp=temp->getLeftChild();
			
		}
		return ret;
	}
	
	//! calculate height from left anf right subtree
	void calculateHeight(){
		int leftH=0 , rightH=0;
		if(left!=nullptr){
			leftH=left->getHeight();
		}
		if(right!=nullptr){
			rightH=right->getHeight();
		}
		
		height=Max( leftH , rightH )+1;
		
	}
	
public:

	//! Create an empty with height 0
	AVLNode<T,S>() {
		
		parent=nullptr;
		left=nullptr;
		right=nullptr;
		height=0;
		
	}
	//!destructor
	~AVLNode<T,S>() {
		//OS will free the memory
	}
	
	//! copy construtor
	AVLNode<T,S>(const AVLNode<T,S> *x){
		if(x==nullptr){
			parent=nullptr;
			left=nullptr;
			right=nullptr;
			height=0;
			return;
		}
		data=x->data;
		height=x->height;
		key=x->key;
		left=x->left;
		parent=x->parent;
		right=x->right;
	}
	
	//! returns key of this node
	T getKey(){
		return key;
	}
	
	//! returns class<S> data stored against class<T> _key
	S getData(){
		return data;
	}
	
	friend class AVLTree<T,S>;
	
};



/**
 *  The class Initialization is used for initializing global variables.
 *  You should never create instances of it!
*/
template <class T,class S> class AVLTree
{
	
	AVLNode<T,S> *root;
	
	//!update all information and balance the tree after deletion or insertion
	/**
     * @param node which indicates the node inforfation to be updated 
     */
	void update(AVLNode<T,S> *);
	
	//! Rearrange 3 nodes in such a way that the node \z becomes balanced
    /**
     * @param z is the node that is the lowest unbalanced node now
	 * The algorithm used for this methode can be found in Data Structure 
	 * and algorithms in C++ (frist edition) by Goodrich, Tamassia and 
	 * Mount on pg. no. 430
	 * 
     */
	void rearrange(AVLNode<T,S> *);
	
	//! Clear left and right subtree of node. Then free the node
	/**
     * @param node of type AVLNode<T> to clear the whole tree
     */
	//!void clearTree(AVLNode<T> *);
	void clearTree(AVLNode<T,S>*);
	
	//! searches for a key in the tree. if found return the pointer to the tree else return nullptr
	/**
     * @param *key of type T to search in the tree and return AVLNode pointer
     */
	AVLNode<T,S>* find(const T & );
	
	
public:
	//! create an empty tree
	AVLTree<T,S>() {
		root=nullptr;
	}
	
	//! destructor
	~AVLTree<T,S>() {
		clearTree(root);
	}
	
	//!this class provides the general features of iterator
	/**
	 * the reason this class is inherited from AVLNode is
	 * we want to mask AVLNode and get a iterator so that
	 * only iterator can be enough to access the AVLTree
	 * */
	class iterator : public AVLNode<T,S>
	{
		bool isNull;
		
		//! this methode finds the next element and push in stack
		iterator getNextIterator();
		
		void increment(){
			iterator x=getNextIterator();
			if(!x.isNull){
				this->data=x.data;
				this->height=x.height;
				this->key=x.key;
				this->left=x.left;
				this->parent=x.parent;
				this->right=x.right;
			}
			else{
				this->isNull=true;
				this->parent=nullptr;
				this->left=nullptr;
				this->right=nullptr;
				this->height=0;
			}
		}
		public:
		
		//! empty constructor
		iterator() : AVLNode<T,S>(){
			isNull=true;
		}
		
		//! destructor
		~iterator(){
			
		}
		
		//!constructor to convert AVLNode into iterator type
		iterator(AVLNode<T,S> * x) : AVLNode<T,S>(x){
			if(x==nullptr){
				isNull=true;
			}
			else isNull=false;
		}
		
		//! prefix ++ operator for iterator
		void operator ++ (){
			this->increment();
			
		}
		
		//! postfix ++ operator for iterator
		void operator ++(int){
			this->increment();
		}
		
		//! returns if a a iterator is a nullptr
		bool isNullprt(){
			return isNull;
		}
		
		//! equal comperator for iterator, returns if two tree nodes are equivalent
		bool operator ==(iterator r){
			if((isNull==r.isNull && isNull) ||( isNull==r.isNull && r.left==this->left && r.right==this->right && this->parent==r.parent
			&& this->key==r.key && this->data==r.data && this->height==r.height)){
				return true;
			}
			return false;
		}
		
		//! not equal comperator for tree node
		bool operator !=(iterator r){
			if((isNull==r.isNull && isNull) ||( isNull==r.isNull && r.left==this->left && r.right==this->right && this->parent==r.parent
			&& this->key==r.key && this->data==r.data && this->height==r.height)){
				return false;
			}
			return true;
		}
		
	};
	
	//!Clear the AVL tree completely.
	void clear(){
		if(root == nullptr) return;
		clearTree(root);
		root = nullptr;
	}
	
	//! searches for a key in the tree. return iterator
	/**
     * @param *key of type T to search in the tree
     */
	iterator lookUp(const T & );
	
	//! insertes a new key in the AVL tree and returns itand if the key to be inserted is already in the tree returns pointer to that key
	/**
	 * @param *key of type <T> which would be inserted in the tree
	 * @return boolean if the node is a new insertion or old, if new, insert the data and return true else reutn false and update data
     */
	bool insert(const T & , const S &);
	
	//!this methode removes a node from tree
	/**
	 * @param *key of type <T> which would be removed from tree if present in the tree
	 */
	void remove(const T &);
	
	
	
	//! return the iterator of the beginning of the AVL Tree
	iterator begin();
public:
	iterator end(){
		return iterator(nullptr);
	}
};



template <class T,class S>
void AVLTree <T,S> ::clearTree(AVLNode<T,S>* node){
	if(node == nullptr) return;
	clearTree(node->getLeftChild());
	clearTree(node->getRightChild());
	delete node;
}

template <class T,class S>
AVLNode<T,S>* AVLTree<T,S>::find(const T  &_key){
	
	AVLNode<T,S> *temp = root;
	while(temp!=nullptr){
		
		if(temp->getKey()== _key){
			
			return temp;
			
		}
		else if(temp->getKey() < _key){
			
			temp = temp->getRightChild();
			
		}
		else{
			
			temp = temp->getLeftChild();
			
		}
		
	}
	return nullptr;
}


template <class T,class S>
typename AVLTree<T,S>::iterator AVLTree<T,S>::lookUp(const T  &_key){
	
	AVLNode<T,S> *temp = find(_key);
	return iterator(temp);
}

template <class T , class S>
bool AVLTree<T,S>::insert(const T  &_key, const S &_data){
	
	AVLNode<T,S> *newNode=new AVLNode<T,S>();
	newNode->setKey(_key);
	newNode->setData(_data);
	AVLNode<T,S>  *insertHere;
	insertHere = nullptr;
	
	if(root==nullptr){
		
		root=newNode;
		root->calculateHeight();
		return root;
	}
	else{
		
		AVLNode<T,S> *temp=root;
		while(temp != nullptr){
			insertHere=temp;
			if(newNode->getKey()==temp->getKey()){
				//already in the tree, return true
				temp->setData(newNode->getData());
				return false;
			}
			else if(newNode->getKey() < temp->getKey()){
				temp=temp->getLeftChild();
			}
			else{
				
				temp=temp->getRightChild();
			}
		}
		
		if(insertHere->getKey() < newNode->getKey()){
			insertHere->setRightChild(newNode);
		}
		else{
			insertHere->setLeftChild(newNode);
		}
		
		update(newNode);
		return true;
	}
	
}

// Update all nodes above this node
template <class T,class S>
void AVLTree<T,S>::update(AVLNode<T,S> *node){
	node->calculateHeight();
	
	if(abs(node->getBalanceProperty())>1){
		
		rearrange(node);
		
	}
	
	if(node->getParent()!=nullptr){
		
		update(node->getParent());
			
	}
	
}

template <class T,class S>
void AVLTree<T,S>::rearrange(AVLNode<T,S> *z){
	
	AVLNode<T,S> *x,*y,*a,*b,*c,*t0,*t1,*t2,*t3;
	int zLeftHeight=0;
	int zRightHeight=0;
	int yLeftHeight=0;
	int yRightHeight=0;
	
	if(z->getLeftChild()!=nullptr){
		
		zLeftHeight = z->getLeftChild()->getHeight();
		
	}
	if(z->getRightChild()!=nullptr){
		
		zRightHeight = z->getRightChild()->getHeight();
	}
	
	
	if(zLeftHeight > zRightHeight){
		
		c = z;
		y = z->getLeftChild();
		
		if(y->getLeftChild()!=nullptr){
			
			yLeftHeight = y->getLeftChild()->getHeight();
			
		}
		
		if(y->getRightChild() != nullptr){
			
			yRightHeight = y->getRightChild()->getHeight();
			
		}
		
		if(yLeftHeight > yRightHeight){
			
			x = y->getLeftChild();
			b = y;
			a = x;
			
			t0 = a->getLeftChild();
			t1 = a->getRightChild();
			t2 = b->getRightChild();
			t3 = c->getRightChild();
			
		}
		else{
			
			x = y->getRightChild();
			a = y;
			b = x;
			
			t0 = a->getLeftChild();
			t1 = b->getLeftChild();
			t2 = b->getRightChild();
			t3 = c->getRightChild();
		
		}
			
	}
	else{
		
		
		a = z;
		y = z->getRightChild();
		
		if(y->getLeftChild()!=nullptr){
			
			yLeftHeight = y->getLeftChild()->getHeight();
			
		}
		
		if(y->getRightChild()!=nullptr){
			
			yRightHeight = y->getRightChild()->getHeight();
			
		}
		if(yLeftHeight > yRightHeight){
			
			x = y->getLeftChild();
			c = y;
			b = x;
			
			t0 = a->getLeftChild();
			t1 = b->getLeftChild();
			t2 = b->getRightChild();
			t3 = c->getRightChild();
			
		}
		else{
			x = y->getRightChild();
			b = y;
			c = x;
			
			t0 = a->getLeftChild();
			t1 = b->getLeftChild();
			t2 = c->getLeftChild();
			t3 = c->getRightChild();
			
		}
		
	}
	
	/**
	 * Replacing Subtree rooted at z with new Subtree rooted at b
	 * Means we have to alternate the parent of b with the parent
	 * of z
	 */
	 //if z is root, update root of tree.
	 bool isRoot = (z->getParent()==nullptr);
	 
	 if(isRoot){
		 b->setParent( z->getParent() );
	 }
	 else if(z->isLeftChild()){
		 
		 z->getParent()->setLeftChild(b);
		 
	 }
	 else{
		 
		 z->getParent()->setRightChild(b);
		 
	 }
	 
	 b->setLeftChild(a);
	 b->setRightChild(c);
	 a->setLeftChild(t0);
	 a->setRightChild(t1);
	 c->setLeftChild(t2);
	 c->setRightChild(t3);
	 
	 //update Height
	 a->calculateHeight();
	 b->calculateHeight();
	 c->calculateHeight();
	 
	 if(isRoot) root=b;
}



template <class T,class S>
void AVLTree<T,S>::remove(const T &key){
	
	AVLNode<T,S> * nodeDelete=find(key);
	AVLNode<T,S>	 * successor;
	
	
	//!search for the key
	if(nodeDelete==nullptr){
		//!nothing to delete
		return;
		
	}
	else{
		successor=nodeDelete->getSuccessor();
		if(successor==nullptr){
			//!no successor
			if(nodeDelete->getParent()==nullptr){
				
				//!the node to be deleted is root
				root=nodeDelete->getLeftChild();
				if(root == nullptr) return;
				root->setParent(nullptr);
				//!no update needed
				
			}
			else{
				
				
				//!setting the parent of the deletion node to be the parent of the left subtree of deletion node
				if(nodeDelete->isLeftChild()){
					
						
					nodeDelete->getParent()->setLeftChild(nodeDelete->getLeftChild());
					
				}
				else{
					
					nodeDelete->getParent()->setRightChild(nodeDelete->getLeftChild());
					
				}
				update(nodeDelete->getParent());
				
			}
			
		}
		else {
			
			AVLNode<T,S> *successorParent=successor->getParent();
			
			//!if there is a successor there is a successorParent
			
			//!node to delete is root
			if(nodeDelete->getParent()==nullptr){
				
				if(successor->isRightChild()){
					
					//successor parent is going to be deleted
					successor->setLeftChild(nodeDelete->getLeftChild());
					root=successor;
					root->setParent(nullptr);
					update(successor);
				}
				else{
					
					successorParent->setLeftChild(successor->getRightChild());
					successor->setLeftChild(nodeDelete->getLeftChild());
					successor->setRightChild(nodeDelete->getRightChild());
					root=successor;
					root->setParent(nullptr);
					update(successorParent);
				}
				
				
			}
			else{
				
				//!the node to be deleted not root and is external
				if(successor->isRightChild()){
					//successor parent is going to be deleted
					successor->setLeftChild(nodeDelete->getLeftChild());
					if(nodeDelete->isLeftChild()){
						
						nodeDelete->getParent()->setLeftChild(successor);
					
					}
					else if(nodeDelete->isRightChild()){
						
						nodeDelete->getParent()->setRightChild(successor);
					
					}
					update(successor);
					
				}
				else{
					
					successorParent->setLeftChild(successor->getRightChild());
					successor->setLeftChild(nodeDelete->getLeftChild());
					successor->setRightChild(nodeDelete->getRightChild());
					if(nodeDelete->isLeftChild()){
					
						nodeDelete->getParent()->setLeftChild(successor);
					
					}
					else if(nodeDelete->isRightChild()){
					
						nodeDelete->getParent()->setRightChild(successor);
					
					}
					update(successorParent);	
				}
			}	
			
		}
		
		delete nodeDelete;
		
	}
	
}

template <class T,class S>
typename AVLTree<T,S>::iterator AVLTree<T,S>::begin(){
	
	AVLNode<T,S> *temp=root,*ret=nullptr;
	while(temp!=nullptr){
		ret=temp;
		temp=temp->getLeftChild();
	}
	return iterator(ret);
}

template <class T, class S>
typename AVLTree<T,S>::iterator AVLTree<T,S>::iterator::getNextIterator(){
	AVLNode<T,S> *next=nullptr;
	next=this->getSuccessor();
	
	if(next!=nullptr){
		iterator ans(next);
		return ans;
	}
	else{
		AVLNode<T,S> *ret = nullptr,*temp=nullptr;
		
		//cout<<this->getKey()<<" "<<this->getParent()->getKey()<<endl;
		
		if(this->isLeftChild()){
			temp=this->getParent()->getLeftChild();
			//cout<<"Left"<<endl;
		}
		else if(this->isRightChild()){
			temp=this->getParent()->getRightChild();
			//cout<<"Right"<<endl;
		}
		
		while(temp!=nullptr){
			if(temp->isLeftChild()){
				ret=temp->getParent();
				//cout<<ret->getKey()<<endl;
				break;
			}
			else{
				temp=temp->getParent();
				/*if(temp==nullptr) cout<<"NL"<<endl;
				else
				{
					cout<<temp->getKey()<<endl;
				}*/
			}
		}
		//cout<<"came get out"<<endl;
		
		return iterator(ret);
	}
}

#endif