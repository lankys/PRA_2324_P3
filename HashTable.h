    #ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:

        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
    int h(std::string key){
        int acum = 0;
        for (int i = 0; i < key.length(); i++){
         acum +=int(key.at(i));

        }
        return acum% max;
    }
    

    public:
        HashTable(int size){
            table = new ListLinked<TableEntry<V>>[max];
            n = 0;
            max = size;
        }


        ~HashTable() {
            delete [] table;
        }

        int capacity()const{
            return max;
            }


        friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th){
            for (int i = 0; i < th.max; i++){
                out << "cubeta" << i << "elementos:";
                for (int j = 0; j < th.table[i].n; j++){
                    out << " " << j << th.table[i] << std::endl;
                }
            }
            return out;
            }
      
        V operator[](std::string key){
                return search(key);
        
        }
        void insert(std::string key, V value) override {
            //creo un table Entry con  el nombre i --> con una key y un value
            TableEntry<V> i(key, value); 
            //miramos si el elemento esta dentro de la tabla hash
            //para esto usamos el operador [] nos ubica en la cubeta  del cifrado de key,con el search buscamos  si el elemento esta en la cubeta
            if (table[h(key)].search(key) != -1){ 
                throw std::runtime_error(" elemento incluido");
            }
            else{
		    table[h(key)].prepend(i);
                //si no esta en la cubeta lo meto con un prepend
            }
            n++;//aumento el numero de el
        }

        V search(std::string key) override {
           //
            V aux = table[h(key)].search(key);
            if (aux == -1) {
                throw std::runtime_error("No exite");
            }
            TableEntry<V> valor = table[h(key)].get(aux);
            return valor.value;
        }

        V remove(std::string key) override {
            V aux = table[h(key)].search(key);
            if (aux == -1) {
                throw std::runtime_error("No exite");
            }
            TableEntry<V> valor = table[h(key)].remove(aux);
            n--;
            return valor.value;
        }



};

#endif
