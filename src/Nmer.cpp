#include <fstream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"

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
 	set<string> conjunto;
	string cadena = "";
 	listar(el_Nmer.root(), conjunto, cadena);
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

Nmer Nmer::Prefix(string adn) {
	Nmer subarbol = Nmer();
	set<string> conjunto;
	set<pair<string,int> > conjunto_total = level(max_long);	// Se recorre todo el Nmer y se guarda en conjunto_total
	bool coincide = true;

	for (set<pair<string,int> >::iterator itr = conjunto_total.begin(); itr != conjunto_total.end(); itr++) {
		if ( (*itr).first.size() >= adn.size() ) {
			for (int i = 0; i < adn.size() && coincide; i++) {
				if ( (*itr).first[i] != adn[i]) {	// Si no coinciden
					coincide = false;
				} else {
					if (i == adn.size() - 1) {
						conjunto.insert( (*itr).first );
					}
				}
			}
			coincide = true;
		}
	}

	// Se insertan las cadenas extraidas del proceso anterior
	for (set<string>::iterator itr = conjunto.begin(); itr != conjunto.end(); itr++) {
		subarbol.insertar_cadena( *itr );
	}

	return subarbol;
}

void Nmer::sequenceADN(unsigned int tama, const string & adn ) {
	cout << "[SEQUENCE ADN] Leyendo cadena: " << adn << endl;
	string cadena = "";
	for ( int i = 0 ; i < adn.size() - tama + 1; i++) {
		for (int j = i; j <= tama + i - 1; j++) {
			cadena = cadena + adn[j];
		}
		// cout << "\tCadena: " << cadena << endl;
		if (cadena.size() == tama)
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
		if (!n_act.k_child(indice).null()) { // Ya esta insertado el nodo
			(*n_act.k_child(indice)).second++;
		}
		else {								// No está insertado
			par.first = cadena[i];
			par.second = 1;
			el_Nmer.insert_k_child( n_act, indice, par);
		}
		n_act = n_act.k_child(indice);
	}

	// Si la cadena insertada es mayor que la profundidad máxima anterior se modifica esta
	if (max_long < cadena.size())
		max_long = cadena.size();
}

bool Nmer::containsString (const string adn) {
	ktree < pair<char,int>, 4 >::const_node nodo_actual = el_Nmer.root();
	bool esta = true;
	int indice;

	for (int i = 0; i < adn.size() & esta; i++) {
		indice = indice_nodo( adn[i] );
		if ( !nodo_actual[indice].null() )
			nodo_actual = nodo_actual[indice];
		else
			esta = false;
	}

	return esta;
}

set <pair <string,int>/*, OrdenCre*/ > Nmer::rareNmer (int threshold) {
	set <pair <string, int> > conjunto;
	typename ktree<pair<char,int>,4>::const_node n = el_Nmer.root();
	string cadena = "";

	for (int i = 0; i < 4; i++)
		if ( !n[i].null() )
			leer_rare(conjunto, n[i], cadena, threshold);

	return conjunto;
}	

set < pair <string,int> /*, OrdenDecre*/>  Nmer::commonNmer(int threshold) {
	set <pair<string,int>/* OrdenDecre*/> conjunto;
	typename ktree<pair<char,int>,4>::const_node n = el_Nmer.root();
	string cadena = "";

	for (int i = 0; i < 4; i++) {
		if ( !n[i].null() && (*n[i]).second >= threshold)
			leer_common(conjunto, n[i], cadena, threshold);
	}

	return conjunto;
}



void Nmer::leer_rare (set < pair<string,int> /*, OrdenCre*/> &conjunto, typename ktree<pair<char,int>,4>::const_node n, string &cadena, int threshold) {
	
	string actual = cadena + (*n).first;
	bool no_hijos = true;

	for (int i = 0; i < 4; i++) {
		if ( !n[i].null() ) {
			leer_rare (conjunto, n[i], actual, threshold);
			no_hijos = false;
		}
	}

	if (no_hijos) {
		if ( (*n).second <= threshold) {
			if (actual[0] == '-')	// Si la cadena empieza por el caracter - de la raiz se elimina
				actual.erase(0,1);
			conjunto.insert ( pair <string, int>(actual, (*n).second));
		}
	}
}

void Nmer::leer_common(set < pair<string,int> /*, OrdenCre*/> &conjunto, typename ktree<pair<char,int>,4>::const_node n, string &cadena, int threshold) {

	string actual = cadena + (*n).first;
	bool hijos_iguales = false;

	for (int i = 0; i < 4; i++) {
		if ( !n[i].null() ) {
			if ( (*(n[i])).second >= threshold) {
				hijos_iguales = true;
				leer_common(conjunto, n[i], actual, threshold);
			}
		}
	}

	if (!hijos_iguales)
		conjunto.insert( pair <string,int>(actual, (*n).second));
}

bool Nmer::included(const Nmer reference) const {
	return
		max_long <= reference.max_long &&
			comparison( this->el_Nmer.root(), reference.root() );
}

bool Nmer::comparison(typename ktree< pair<char,int>,4>::const_node n1, typename ktree< pair<char,int>,4>::const_node n2) const{
	bool comp = true;
	if (*n1 != *n2) comp = false;
	for (int i = 0; i < 4; i++)
		if ( !comparison(n1[i], n2[i])) comp = false;
	
	return comp;
}

/*Nmer Nmer::Union(const Nmer reference) {
	union_aux ( el_Nmer.root(), reference.root());
	return *this;
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

ktree<pair<char,int>,4>::const_node Nmer::root() const{
	return this->el_Nmer.root();
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
	typename ktree< pair <char,int>, 4>::const_node n = el_Nmer.root();
	typename ktree< pair <char,int>, 4>::const_node aux;
	queue<typename ktree<pair<char,int> ,4>::const_node > cola;

	if (!n.null())
		cola.push(n);

  	while (!cola.empty()){
 		aux = cola.front();
    	cola.pop();
		cout << "(" <<  (*aux).first  << " - " << (*aux).second <<"); ";
    	for (auto hijo : aux)
      		cola.push(hijo);
  }
  cout << endl;
}

set<string> Nmer::listar(ktree<pair<char,int> ,4>::const_node n, set<string> conjunto, string &cadena) const {
	if (!n.null()){
		if ( (*n).second != 0 ) {
		 	int altura = 5 - altura_nodo(n);
		  	cadena[altura - 1] = (*n).first;
		  	conjunto.insert(cadena);
		}
		  	typename ktree<pair<char,int> ,4>::const_node::child_iterator ini = n.begin();
		  	typename ktree<pair<char,int> ,4>::const_node::child_iterator fin = n.end();
		  	while (ini != fin){
		     	listar(*ini, conjunto, cadena);
		     	++ini;
		   	}
	}
}

set< pair<string,int> /* , OrdenCre */> Nmer::level(int l) {
	set<pair<string,int>/* , OrdenCre */> resultado;
	string cadena = "";
	if (l > 0) {
		for (int i = 0; i < 4; i++)
			if ( !el_Nmer.root()[i].null() ) { // Si la raiz del hijo no es nula
				recorrer_level(l - 1, resultado, el_Nmer.root()[i], cadena);
			}
	}

	return resultado;
}

void Nmer::recorrer_level(int level, set<pair<string,int>/*, OrdenCre*/> &conjunto, typename ktree<pair<char,int>,4>::const_node n, const string &cadena) {


	string actual = cadena + (*n).first;
	pair <string,int> par;
	par.first = actual;
	par.second = 1;
	conjunto.insert( par );

	for (int i = 0; i < 4; i++)
		if ( !n[i].null() ) {
			recorrer_level(level - 1, conjunto, n[i], actual);
		}
}

/* void Nmer::union_aux(typename ktree<pair<char,int>,4>::node nodo1, typename ktree<pair<char,int>,4>::const_node nodo2) {
	for (int i = 0; i < 4; i++) {
		if (!nodo1[i].null() && !nodo2[i].null())
			(*nodo1[i]).second = (*nodo1[i]).second + (*nodo2[i]).second;
		else
			el_Nmer.insert_k_child(nodo1, i, *nodo2[i]);

		union_aux ( nodo1[i], nodo2[i]);
	}
}
 */

