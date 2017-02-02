#include <fstream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"


#define BLACK    "\033[0m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define WHITE    "\033[37m"

//template<typename T, int K>
//extern void recorrido_preorden(typename ktree<T,K>::const_node n);


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
 //     ktree< pair <char,int> , 4>::recorrido_preorden(el_Nmer.root());
 	string cadeneta = "0000000000000000000";
 	set<string> conjuntete;
 	listar(el_Nmer.root(), conjuntete, cadeneta);
 	cout << "FINALIZADO LIST_NMER" << endl;
}
 
unsigned int Nmer::length() const {
   return max_long;
}
 
Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

// -------------------------------------------
// | 			Métodos pedidos				 |
// -------------------------------------------
void Nmer::sequenceADN(unsigned int tama, const string & adn ) {
	cout << "[SEQUENCE ADN] Leyendo cadena: " << adn << endl;
	string cadena = "";
	for ( int i = 0 ; i < adn.size() - tama + 1; i++) {
		for (int j = i; j <= tama + i - 1; j++) {
			cadena = cadena + adn[j];
		}
		cout << "\tCadena: " << cadena << endl;
		if (cadena.size() == tama)
			insertar_cadena(cadena);
		cadena.clear();
	}
}

void Nmer::insertar_cadena(const string cadena) {
	/*
	typename ktree<pair<char,int>,4>::node n_act = el_Nmer.root();
	int indice;
	pair<char,int> par;
	cout << "\t[INSERTAR_CADENA] Insertando cadena " << cadena << endl;
	for (int i = 0; i < cadena.size(); i++) {
		indice = indice_nodo(cadena[i]);
		if (!n_act.k_child(indice).null()) { // Ya esta insertado el nodo
			cout << "\t\tYa esta insertado el nodo, se incrementa" << endl;
			(*n_act.k_child(indice)).second++;
			cout << "\t\tContador = " << (*n_act.k_child(indice)).second << endl;
		}
		else {								// No está insertado
			cout << "\t\tNo esta insertado, se inserta " << cadena[i] << endl;
			par.first = cadena[i];
			par.second = 1;
			el_Nmer.insert_k_child( n_act, indice, par);
		}
		n_act = n_act.k_child(indice);
	}
	*/
}



/*
set <pair <string,int>, OrdenCre > rareNmer (int threshold) {
	set < pair <string,int>, OrdenCre> conjunto;
	typename ktree<pair <char,int>, 4>::const_node n = el_Nmer.root();
	typename ktree<pair <char,int>, 4>::const_node aux;
	queue<typename ktree<pair<char,int> ,4>::const_node > cola;
	pair <string,int

	if (!n.null())
		cola.push(n);

  	while (!cola.empty()){
 		aux = cola.front();
    	cola.pop();

		cout << "(" <<  (*aux).first  << " - " << (*aux).second <<"); ";
    	for (auto hijo : aux)
      		cola.push(hijo);
	  }
}
*/

// -------------------------------------------
// | 			Métodos auxiliares			 |
// -------------------------------------------

int Nmer::altura_nodo(typename ktree<pair<char,int> ,4>::const_node n) const{
	int hmax=-1;
	if (!n.null()){
	  	for (auto hijo:n) {
	    	int hact = altura_nodo(hijo);
	    if (hact > hmax)
	      	hmax = hact;
		}
		return hmax+1;
	}
	else return -1;
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
void Nmer::recorrer_niveles() const {
	/*typename ktree< pair <char,int>, 4>::const_node n = el_Nmer.root();
	typename ktree< pair <char,int>, 4>::const_node aux;
	queue<typename ktree<pair<char,int> ,4>::const_node > cola;

	if (!n.null())
		cola.push(n);

  	while (!cola.empty()){
 		aux = cola.front();
    	cola.pop();
    	for (int i = 0; i < altura_nodo)
		cout << "(" <<  (*aux).first  << " - " << (*aux).second <<"); ";
    	for (auto hijo : aux)
      		cola.push(hijo);
  }
  cout << endl;
  */
}

set<string> Nmer::listar(ktree<pair<char,int> ,4>::const_node n, set<string> conjunto, string &cadena) const {
	cout << YELLOW << "[LISTAR] cadena: " << cadena << endl;
	if (!n.null()){
		if ( (*n).second != 0 ) {
		 	int altura = 5 - altura_nodo(n);
		 	cout << GREEN << "[ALTURA]" << " Altura nodo actual: " << altura << WHITE <<  endl; º
		  	cadena[altura - 1] = (*n).first;
		  	conjunto.insert(cadena);
		} else {
			cout << RED << "El nodo actual tiene etiqueta " << (*n).first << " - " << (*n).second << WHITE << endl;
		}

		cerr << "Antes de ini" << endl;
		cout << "Nodo: " << (*n).first << " - " << (*n).second << endl;
		  	typename ktree<pair<char,int> ,4>::const_node::child_iterator ini = n.begin();
		  	typename ktree<pair<char,int> ,4>::const_node::child_iterator fin = n.end();
		  	while (ini != fin){
		  		cerr << "ENTRA?" << endl;
		     	listar(*ini, conjunto, cadena);
		     	++ini;
		   	}
		cerr << "Post ini" << endl;
	}
}

set< pair<string,int> , OrdenCre > Nmer::level(int l) {
	set<pair<string,int>, OrdenCre> resultado;
	string cadena = "";
	if (l<0) {
		for (int i = 0>; i < 4; i++)
			if (!el_Nmer.root()[i].null() )
				recorreLevel(&resultado, el_Nmer.root()[i], cadena, l - 1);
	}

	return resultado;
}

void Nmer::recorreLevel(set>pair<string,int>,OrdenCre> *conjunto, typename ktree<pair<char,int>,4>::const_node n, const string &cadena, int l) {
	string actual = cadena + (*n).fist;

	if (l = 0)
		(*conjunto).insert( pair<string,int> (actual, (*n).second) );
	else
		for (int i = 0; i < 4; i++)
			if (!n[i].null() )
				recorreLevel(ptr_set, n[i], actual, i - 1);
}

 

