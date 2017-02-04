
#include <iostream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"

class OrdenCre {
public:
    bool operator() ( pair<string,int> par1, pair<string,int> par2) const {
		  if (par1.second < par2.second)
            return true;
          else
            return false;
    }
};

class OrdenDecre {
public:
    bool operator() ( pair<string,int> par1, pair<string,int> par2) const {
		  if (par1.second > par2.second)
            return true;
          else
            return false;
    }
};
int main() {

    cout << "\n\n\033[1;46m" << "----------------------------------------------------------------------" << endl;
    cout                     << "                           TDA NMER                                   " << endl;
    cout                     << "----------------------------------------------------------------------" << "\n\033[0m\n\n" << endl;

    Nmer arbol = Nmer();

    // SequenceADN
    cout << "\n\033[1;46m" << "SEQUENCE ADN                                       \n";
    cout                     << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Leemos dos cadenas:\n";
    arbol.sequenceADN(6, "ATACATCATTGTGG");
    arbol.sequenceADN(5, "AAAAATCATG");
    cout << endl;
    // arbol.recorrer_niveles();
    cout << endl;

    // LOAD SERIALIZED
    cout << "\033[1;46m" << "LOAD SERIALIZED                                    \n";
    cout                   << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Cargamos el archivo cadenaSimple.srl\n\n";
    Nmer arbol_serialized = Nmer();
    arbol_serialized.loadSerialized("datos/cadenaSimple.srl");
    cout << "Profundidad:  " << arbol_serialized.length() << endl;
    cout << "Tamaño:       " << arbol_serialized.size() << endl;

    // LIST NMER
    // arbol.list_Nmer();

    // RARE NMER
    cout << "\n\033[1;46m" << "RARE NMER                                          \n";
    cout                 << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Hacemos el rareNmer del primer arbol con thresold 2\n\n";
    set< pair<string,int> /*, OrdenCre */ > conjunto = arbol.rareNmer(2);
    cout << "Numero de cadenas del rareNmer: " << conjunto.size() << endl << endl;
    for ( set<pair<string,int>/* , OrdenCre */>::iterator itr = conjunto.begin(); itr != conjunto.end(); itr++)
        cout << " ( "<< (*itr).first << " )" << endl;
        

    // COMMON NMER
    cout << "\n\033[1;46m" << "COMMON NMER                                        \n";
    cout                   << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Hacemos el commonNmer del primer arbol con thresold 2\n\n";
    conjunto = arbol.commonNmer(2);
    cout << "Numero de cadenas del commonNmer: " << conjunto.size() << endl << endl;
    for ( set<pair<string,int>/* , OrdenCre */>::iterator itr = conjunto.begin(); itr != conjunto.end(); itr++)
        cout << " ( "<< (*itr).first << " )" << endl;

    // PREFIX
    cout << "\n\033[1;46m" << "PREFIX                                             \n";
    cout                   << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Obtenemos el Nmer con las cadenas con prefijo TT:\n\n";
    Nmer subarbol = Nmer();
    subarbol = arbol.Prefix("TT");
    set < pair<string,int>/*, OrdenCre*/> cjto_prefix = subarbol.level(subarbol.length() );
    for ( set<pair<string,int>/* , OrdenCre */>::iterator itr = cjto_prefix.begin(); itr != cjto_prefix.end(); itr++)
        cout << " ( "<< (*itr).first << " )" << endl;  

    // CONTAINS STRING 
    cout << "\n\n\033[1;46m" << "CONTAINS STRING                                    \n";
    cout                     << "---------------------------------------------------" << "\n\033[0m\n";
    cout << "Está ATAC en el árbol? ";
    if (arbol.containsString("ATAC"))
        cout << "Sí\n\n";
    else
        cout << "No\n\n";

    return 0;

}