#include "Main.h"

// Metode principal del programa

int main(int argc, char **argv)
{
    cout << "Init..." <<endl;
    Q_INIT_RESOURCE(resources);
    //REAL DATA INICIALIZATION
    //auto controller = make_shared<Controller>("://resources/dadesEuropa.txt", "://resources/configMappingDataEuropa.txt", "://resources/configVisDataEuropa.txt");
    auto controller = make_shared<Controller>("://resources/dataBCN.txt", "://resources/configMappingDataBCN.txt", "://resources/configVisDataBCN.txt");
    
    //VIRTUAL DATA INICIALIZATION
    //auto controller = make_shared<Controller>("://resources/spheres.txt", "://resources/configMapping.txt", "://resources/configVisVirtual.txt");

    controller->start(argc, argv);
    return(0);
}
