#ifndef DICTIONARY_H
#define DICTIONARY_H


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
	
	
	
};

#endif // DICTIONARY_H
