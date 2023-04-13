#include "RealDataReader.h"


RealDataReader::RealDataReader(shared_ptr<Scene> s)
{
    scene = s;
}

void RealDataReader::readFile(QString fileName, shared_ptr<Mapping> map) {
    QFile file(fileName);

    mapping = map;

    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

// TODO: Fase 1: Cal afegir més tipus d'objectes
void RealDataReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}



void RealDataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    int n = mapping->getNumProps();

    if (fields.size() != (3 + n)) {
        std::cerr << "Wrong data format" << std::endl;
        return;
    }

    for (int i=0; i<n; i++) {

        shared_ptr<Object> o;
        ObjectFactory::OBJECT_TYPES groundType = mapping->getGroundType();
        double yPlanePos = mapping->getPlaneCenter();

        if (groundType == ObjectFactory::OBJECT_TYPES::PLANE) {
             yPlanePos = -yPlanePos;
        }

        vec3 puntBase = vec3(fields[1].toDouble(), yPlanePos, fields[2].toDouble());

        ObjectFactory::OBJECT_TYPES type = mapping->getObjectTypeProp(i);
        if (type == ObjectFactory::CYLINDER) {
           o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(puntBase),
                                                           0.1,
                                                           mapping->mapeigValor(fields[3 + i].toDouble(), i),
                                                           -1.0,
                                                           mapping->getObjectTypeProp(i));


        } else if (type == ObjectFactory::TRIANGLE) {
            vec3 mappedBase = mapping->mapeigPunt(puntBase);
            double mappedVal = mapping->mapeigValor(fields[3 + i].toDouble(), i);
            o = ObjectFactory::getInstance().createObject(mappedBase,
                                                            vec3 (mappedBase.x, mappedBase.y+1, mappedVal + mappedBase.z),
                                                            vec3 (mappedVal + mappedBase.x, mappedBase.y+1, mappedBase.z),
                                                          -1.0f,
                                                            mapping->getObjectTypeProp(i));

         } else {

            // Construccio de l'objecte al Mon Virtual
            puntBase.y += mapping->mapeigValor(fields[3 + i].toDouble(), i);
            o = ObjectFactory::getInstance().createObject(mapping->mapeigPunt(puntBase),
                                                          mapping->mapeigValor(fields[3 + i].toDouble(), i),
                                                          fields[3 + i].toDouble(),
                                                          mapping->getObjectTypeProp(i));

        }


        // Construccio i assignacio del material
        o->setMaterial(mapping->mapeigMaterial(i, mapping->getColorMapProp(i), fields[3 + i].toDouble()));
    
        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }
}


