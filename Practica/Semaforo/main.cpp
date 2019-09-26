#include "SemaforoList.h"

int main() {
    int time, numSem, control = 1, mayor = 0;
    int timeFinal = 0;
    SemaforoList S;
    
    std::cout << "Num. de semaforos: ";
    std::cin >> numSem;
    
    while( control <= numSem ) {
        std::cout << "Tiempo del semaforo #" << control << ": ";
        std::cin >> time;
        if( time > mayor ) {
            mayor = time;
        }
        Semaforo S1( time );
        S.insertLast( S1 );
        ++control;
    }

    while( timeFinal < ( 2 * mayor ) || !( S.compareLight())) {
        S.addAllLight();
        ++timeFinal;
        if( timeFinal >= 3600 ) {
            ++timeFinal;
            break;
        }
    }
    --timeFinal;

    int minutos = timeFinal / 60;
    int segundos = timeFinal % 60;
    
    if( timeFinal >= 3600 )
        std::cout << "Mayor a 1h" << std::endl;
    else
        std::cout << "Demorara " << minutos << " minutos y " << segundos << " segundos." << std::endl;
    
    return 0;
}