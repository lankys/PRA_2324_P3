
#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
	BSTree<TableEntry<V>>* tree;

    public:
        BSTreeDict(){
		tree = new BSTree<TableEntry<V>>;
	}
	~BSTreeDict(){
		delete tree;
	}
	friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
		//for(int x=0;x < bs.tree->size();x++){
		//	out << bs.tree[x] << " ";
		//}
		out << bs.tree[0];
		return out;
	}        
	V operator[](std::string key){
		return search(key);
	}
	
	//Metodos heredados
	virtual void insert(std::string key, V value) override{
		TableEntry<V> aux(key,value);
		tree -> insert(aux);	
	}
	virtual V search(std::string key) override{
		TableEntry<V> aux = tree->search(key);
		return aux.value;
	}
	virtual V remove(std::string key)override{
		V aux = search(key);
		tree->remove(key);
		return aux;
	}
	virtual int entries() override{
		return tree->size();
	}
};

#endif
