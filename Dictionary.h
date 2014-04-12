#ifndef DICTIONARY_H
#define DICTIONARY_H


#include <iostream>

using namespace std;

template < typename T, typename S, template<typename, typename> class Module >
class Dictionary
{
	Module<T,S> container;
public:

	//! Simple constructor for Dictionary
	/**
	 * @param empty construntor Dictionary< T,S, Module >()
	 * with @Module as @Module<T,S>
	 */
	Dictionary< T, S, Module >(){

	}

	~Dictionary< T , S, Module >(){

	}

	//! Iterator class for Dictionary
	class iterator{

		typename Module<T,S>::iterator internalIterator;

	public:

		//! Empty Iterator
		iterator(){

		}

		~iterator(){

		}

		//! For turning return of Mofule object
		iterator(const typename Module<T,S>::iterator & it){
			internalIterator=it;
		}

		//! Returns if the container pointer in Null
		bool isNullptr(){
			return internalIterator.isNullptr();
		}

		//! get Key from iterator
		T getKey(){
			return internalIterator.getKey();
		}

		//! get Data from iterator
		S getData(){
			return internalIterator.getData();
		}

		//! prefix ++ operator for iterator
		void  operator ++ (){
			internalIterator++;
		}

		//! postfix ++ operator for iterator
		void operator ++(int){
			internalIterator++;
		}

		//! equal comperator for iterator, returns if two tree nodes are equivalent
		bool operator ==(iterator r){
			return internalIterator==r.internalIterator;
		}

		//! not equal comperator for tree node
		bool operator !=(iterator r){
			return internalIterator!=r.internalIterator;
		}

	};

	bool insert(const T & _key, const S & _data){
		return container.insert(_key,_data);
	}

	iterator lookUp(const T & _key){
		return iterator(container.lookUp(_key));
	}

	void remove(const T & _key){
		container.remove(_key);
	}

	void clear(){
		container.clear();
	}

	//! return iterator to the beginning of the Module
	iterator begin(){
		return iterator(container.begin());
	}

	//! return iterator to the end of the Module
	iterator end(){
		return iterator(container.end());
	}

    //! Proxy class for Subscript with assignment support
	class SubscriptAssignment{
        T _key;
        S _data;
        Dictionary<T,S,Module> &parent;

        //!private constructor, no public instance can be created
        SubscriptAssignment(Dictionary<T,S,Module> & p,const T & k): parent(p), _key(k), _data(){

        }
    public:
        ~SubscriptAssignment(){

        }

        //operators

        bool operator =(const S & dat){
            return parent.container.insert(_key,dat);
        }

        operator const S&()
        {
            Dictionary<T,S,Module>::iterator it=parent.lookUp(_key);
            if(!it.isNullptr()){
                return it.getData();
            }
            return _data;
        }

        friend class Dictionary<T,S,Module>;
	};


	SubscriptAssignment operator [] (const T &k){
        return SubscriptAssignment(*this , k);
	}

	S const& operator[](const T & _key) const
	{
	    return lookUp(_key);
	}
};

#endif // DICTIONARY_H
