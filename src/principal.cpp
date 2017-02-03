
#include <iostream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"

class OrdenCre {
public:
    bool operator() ( pair<string,int> par1, pair<string,int> par2) const {
		  return par1.second < par2.second;
    }
};

int main() {
    Nmer arbol = Nmer();
    arbol.sequenceADN(6, "ATACATCATTGTGG");
    arbol.sequenceADN(5, "AAAAATCATG");
    arbol.recorrer_niveles();
    //arbol.loadSerialized("datos/cadenaSimple.srl");
    cout << "Length: " << arbol.length() << endl;
    cout << "Size: " << arbol.size() << endl;
    // arbol.list_Nmer();
    set< pair<string,int> /*, OrdenCre */ > conjunto = arbol.level(3);
    cout << "Tamaño del set: " << conjunto.size() << endl;
    for ( set<pair<string,int>/* , OrdenCre */>::iterator itr = conjunto.begin(); itr != conjunto.end(); itr++)
        cout << (*itr).first << " - " << (*itr).second << endl;
    return 0;
}