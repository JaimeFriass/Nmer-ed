
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
#include <algorithm>
using namespace std;
#include "ktree.h"

class OrdenCre;
class OrdenDecre;


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
     /** @brief Devuelve el_Nmer.root()
   */ 
   ktree< pair<char,int>,4>::const_node root() const;
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
   */ 
   void recorrer_niveles() const;
  /** @brief Devuelve únicamente los Nmers de longitud ñ
   * @param l longitud
   */ 
   set< pair<string,int>/* , OrdenCre */ > level(int l);
  /** @brief Devuelve el Nmer asociado a un prefijo.
   * @param cadena string a buscar de prefijo
   */ 
   Nmer Prefix(string cadena);
   bool comparison(typename ktree< pair<char,int>,4>::const_node n1, typename ktree< pair<char,int>,4>::const_node n2) const;
  /** @brief Devuelve si la cadena esta contenida en alguna del Nmer.
   * @param adn string a buscar en el Nmer
   */ 
   bool containsString (const string adn);
  /** @brief Devuelve true si cada nodo de *this está también
   * representado en reference.
   * @param reference Nmer donde comparar nodos
   */ 
   bool included(const Nmer reference) const;
  /** @brief Devuelve la lista de todas las subcadenas que aparecen
   * menos de threshold veces en el Nmer ordenadas crecientemente.
   * @param threshold numero de veces
   */ 
   set <pair <string,int>/*, OrdenCre*/ > rareNmer (int threshold);
  /** @brief Devuelve la lista de las cadenas de longitud mayor posible
   * que aparecen más de threshold veces en el Nmer, en orden decreciente.
   * @param threshold numero de veces
   */ 
   set <pair <string,int>/*, OrdenCre*/ > commonNmer (int threshold);
  /** @brief Se devuelve un Nmer donde para cada nodo se computa la suma de
   * las frecuencias en *this y en referencia.
   * @param reference Nmer a comparar
   */ 
   // Nmer Union(const Nmer reference);
   
   
private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias 
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol
  void insertar_cadena(string cadena); 
  unsigned int indice_nodo(const char car);
  set<string> listar(ktree<pair<char,int> ,4>::const_node n, set<string> conjunto, string &cadena) const;
  void recorrer_level(int level, set<pair<string,int>/* , OrdenCre */> &conjunto, typename ktree<pair<char,int>,4>::const_node n, const string &cadena);
  void leer_rare (set <pair<string,int>/*, OrdenCre*/> &conjunto, typename ktree<pair<char,int>,4>::const_node n, string &cadena, int threshold);
  void leer_common(set < pair<string,int> /*, OrdenCre*/> &conjunto, typename ktree<pair<char,int>,4>::const_node n, string &cadena, int threshold);
  void recorre_prefix(set<string> &conjunto, typename ktree<pair<char,int>,4>::const_node n, string adn);
 // void union_aux(typename ktree<pair<char,int>,4>::node nodo1, typename ktree<pair<char,int>,4>::const_node nodo2);
  
 
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
};

#endif
