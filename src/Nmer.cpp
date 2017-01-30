#include <fstream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"

template<typename T, int K>
extern void recorrido_preorden(typename ktree<T,K>::const_node n);


Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
  
}

bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;
 
 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n'); 
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = stoi(cadena);
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb); 
    fe.close();
    return true;
 } // else
 fe.close();
 return false;
}
 
void Nmer::list_Nmer() const {
    // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
      recorrido_preorden<pair<char,int>,4>(el_Nmer.root());
}
 
unsigned int Nmer::length() const {
   return max_long;
}
 
Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

void Nmer::sequenceADN(unsigned int tama, const string & adn ) {
	string cadena;
	for ( int i = 0 ; i < adn.size() - tama; i++) {
		for (int j = i; j <= tama; j++) {
			cadena += adn[j];
		}
		insertar_cadena(cadena);
		cadena.clear();
	}
}

void Nmer::insertar_cadena(const string cadena) {
	typename ktree<pair<char,int>,4>::node n_act = el_Nmer.root();
	int indice;
	pair<char,int> par;
	for (int i = 0; i < cadena.size(); i++) {
		indice = indice_nodo(cadena[i]);
		if (!n_act.k_child(indice).null()) // Ya esta insertado el nodo
			(*n_act.k_child(indice)).second++;
		else {								// No está insertado
			(*n_act.k_child(indice)).first = cadena[i];
			(*n_act.k_child(indice)).second = 1;
		}
		n_act = n_act.k_child(indice);
	}	
}

unsigned int Nmer::indice_nodo(const char car) {
	if (car == 'A')
		return 0;
	if (car == 'G')
		return 1;
	if (car == 'C')
		return 2;
	if (car == 'T')
		return 3;
	else
		return 50;
}

 

