
#include <iostream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"


int main() {
    Nmer arbol = Nmer();
    //arbol.sequenceADN(6, "ATACATCATTGTGG");
    // arbol.recorrer_niveles();
    arbol.loadSerialized("datos/cadenaSimple.srl");
    cout << "Length: " << arbol.length() << endl;
    cout << "Size: " << arbol.size() << endl;
    arbol.list_Nmer();
    return 0;
}