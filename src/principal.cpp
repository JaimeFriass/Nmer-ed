
#include <iostream>
#include <string>
using namespace std;

#include "ktree.h"
#include "Nmer.h"


int main() {
    Nmer arbol = Nmer();
    arbol.sequenceADN(6, "ATACATCATTGTGG");
    // arbol.recorrer_niveles();
    return 0;
}