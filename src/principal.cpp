
#include <iostream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"

template<typename T, int K>
void recorrido_preorden(const ktree<T,K> & arbol){
 recorrido_preorden<T,K>(arbol.root());
  
} 


template<typename T, int K>
void recorrido_preorden(typename ktree<T,K>::const_node   n){

if (!n.null()){
  cout << "( " << (*n) <<"); " <<endl;
  typename ktree<T,K>::const_node::child_iterator ini = n.begin();
  typename ktree<T,K>::const_node::child_iterator fin = n.end();
  while (ini!=fin){
     recorrido_preorden<T,K>(*ini);
     ++ini;
   }
 }
}


int main() {
    Nmer arbol = Nmer();
    arbol.sequenceADN(6, "ATACATCATTGTGG");
    return 0;
}