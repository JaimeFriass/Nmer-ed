
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H
#include <string>
#include <set>
using namespace std;
#include "ktree.h"

//template <typename T, int K>
//extern void recorrido_preorden(typename ktree<T,K>::const_node n);


class Nmer {
public:
  typedef unsigned int size_type;
  
  /** @brief Constructor primitivo .
      Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
  Nmer();
  
  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   * La cadena original viene descrita en el fichero serializado
   */ 
  bool loadSerialized(const string & nombre_fichero);
  
  
  /** @brief Imprime los Nmers
   * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
   */ 
   void list_Nmer() const;
   
   
  /** @brief Máxima longitud de los Nmers almacenados
   */ 
   unsigned int length()const;
   
     
  /** @brief Número de Nmers almacenados
   */ 
   size_type size() const;
  /** @brief Devuelve la altura del nodo argumentado
   * @param n nodo a calcular su altura
   */ 
   int altura_nodo(ktree< pair<char,int>, 4>::const_node n) const;
  /** @brief Recorre la cadena de ADN para extraer subcadenas de longitud tama e insertarlas en el
   * Nmer.
   * @param tama tamaño de las subcadenas del ADN a extraer
   * @param adn cadena de ADN de la cual extraer subcadenas
   */ 
   void sequenceADN(unsigned int tama, const string & adn);
  /** @brief Devuelve el conjunto de subcadenas que aparecen un numero de veces.
   * @param threshold numero de veces que aparecen las subcadenas
   *
   * Devuelve el conjunto de subcadenas (no prefijo) que aparecen un número de veces menor o igual
   * a threshold veces en el Nmer.
   *
   */ 
   // set <pair <string,int>, vector<pair <string,int> >,  OrdenCre > rareNmer (int threshold);

   void recorrer_niveles() const;
  
private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias 
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

  void insertar_cadena(string cadena);
  unsigned int indice_nodo(const char car);
  set<string> listar(ktree<pair<char,int> ,4>::const_node n, set<string> conjunto, string &cadena) const;
 
  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
   public:
    pair<char,int> operator()( const string & cad) {
	    pair<char,int> salida;
	    salida.first = cad[0];
	    salida.second = stoi(cad.substr(1)); 
	    return salida;
    }
  };

   /** @brief Functor para convertir un pair<char,int> en un string 
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second); 
       return salida;
     }
  };

  class OrdenCre {
    public:
    bool operator() ( pair<char,int> par1, pair<char,int> par2) const {
		return par1.second < par2.second;
    }
  };
};

#endif
