#include "utilities.h"

void graficar() {
    system("dot -Tpng /home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/outHEAP.txt -o imgHEAP.png");
    system("dot -Tpng /home/pimed/build-BinHeap-Desktop_Qt_5_12_5_GCC_64bit-Debug/outarrayHEAP.txt -o imgarrayHEAP.png");
}
