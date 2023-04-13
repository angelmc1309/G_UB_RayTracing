#include "VirtualWorldReader.h"


VirtualWorldReader::VirtualWorldReader(shared_ptr<Scene> s)
{
    scene = s;
}

void VirtualWorldReader::readFile(QString fileName, shared_ptr<Mapping> map) {

    mapping = map;
    std::cout << fileName.toStdString()<<std::endl;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
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
void VirtualWorldReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");

    if (QString::compare("sphere", fields[0], Qt::CaseInsensitive) == 0)
        sphereFound(fields);

    else if (QString::compare("plane", fields[0], Qt::CaseInsensitive) == 0)
        plaFound(fields);

    else if(QString::compare("triangle", fields[0], Qt::CaseInsensitive) == 0)
        triangleFound(fields);

    else if(QString::compare("brobject", fields[0], Qt::CaseInsensitive) == 0)
        brObjectFound(fields);

    else if(QString::compare("cylinder", fields[0], Qt::CaseInsensitive) == 0)
        cylinderFound(fields);

    else
        std::cerr << "Element unknown" << std::endl;
}

// Exemple d'esfera
// sphere, 0.5, 0.5, 0.0, 0.25
// centre i radi
void VirtualWorldReader::sphereFound(QStringList fields) {
    // En el fitxer de dades tindràs
    // sphere, centre.x, centre.y, centre.z, radi, propietats del material, textura
    if (fields.size() != 8 && fields.size() != 18
            && fields.size() != 6 && fields.size() != 10) {
        std::cerr << "Wrong sphere format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    // Construccio de l'objecte al Mon Virtual
    vector<vec3> points;
    vector<double> properties;

    vec3 centre = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    points.push_back(centre);
    properties.push_back(fields[4].toDouble());

    //Hacemos el mapeo de los puntos y valores

    mapping->mapeigPunt(centre);
    mapping->mapeigValor(fields[4].toDouble());

    o = ObjectFactory::getInstance().createObject(points, properties, -1.0f, "", ObjectFactory::OBJECT_TYPES::SPHERE);
    // Construccio i assignacio del material
    if(fields.length() == 8 ){
        auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble()
               ,fields[7].toDouble()));
        o->setMaterial(mat);
    }else if(fields.length() == 18){
        auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble()
                ,fields[7].toDouble()),vec3(fields[8].toDouble(),fields[9].toDouble()
                ,fields[10].toDouble()),vec3(fields[11].toDouble(),fields[12].toDouble()
                ,fields[13].toDouble()),vec3(fields[14].toDouble(),fields[15].toDouble()
                ,fields[16].toDouble()),fields[17].toFloat());
        o->setMaterial(mat);

    }
    else if(fields.length() == 6){
        std::string metal = " Metal";
        if(fields[5].toStdString() == " Metal"){
            auto mat = make_shared<Metal>();
            o->setMaterial(mat);
        }else if(fields[5].toStdString() == " Transparent"){
            auto mat = make_shared<Transparente>();
            o->setMaterial(mat);
        }
        else if(fields[5].toStdString() == " Laton"){
            auto mat = make_shared<Laton>();
            o->setMaterial(mat);
        }
        else if(fields[5].toStdString() == " Goma"){
            auto mat = make_shared<Goma>();
            o->setMaterial(mat);
        }
        else if(fields[5].toStdString() == " Plastico"){
           auto mat = make_shared<Plastico>();
           o->setMaterial(mat);
        }
    }else if(fields.size() == 10){
        if(fields[5].toStdString() == " Transparent"){
            auto mat = make_shared<Transparente>(vec3(fields[6].toDouble(),
                    fields[7].toDouble(),fields[8].toDouble()));
            mat->indiceRefraccion = fields[9].toDouble();
            o->setMaterial(mat);
        }
    }


    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}


void VirtualWorldReader::brObjectFound(QStringList fields) {

    // TODO Fase 1: Per incloure BrObjecte
    //  Es suposa que serà una linia del fitxer de l'estil
    //  brobject, nomDelFitxer, propietats del material, textura

    if (fields.size() != 5 && fields.size() != 16) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }

    shared_ptr<Object> o;

    vector<vec3> points;
    vector<double> properties;

    o = ObjectFactory::getInstance().createObject(points, properties, -1.0f, fields[1],
            ObjectFactory::OBJECT_TYPES::BR_OBJECT);


    //***************************************
    // PARA TESTEAR LOS MATERIALES
    //****************************************
    //auto mat = make_shared<Transparente>();
    //auto mat = make_shared<Metal>();
    //auto mat = make_shared<Laton>();
    //auto mat = make_shared<Plastico>();
    //auto mat = make_shared<Goma>();

    if(fields.length() == 5){
        auto mat = make_shared<Lambertian>(vec3(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble()));
    }else{
        auto mat = make_shared<Lambertian>(vec3(fields[2].toDouble(),fields[3].toDouble(),fields[4].toDouble()),
                vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()), vec3(fields[8].toDouble(),
                fields[9].toDouble(),fields[10].toDouble()),vec3(fields[11].toDouble(),fields[12].toDouble(),fields[13].toDouble()),
                fields[14].toDouble());

        o->setMaterial(mat);
    }

    scene->objects.push_back(o);


}

void VirtualWorldReader::triangleFound(QStringList fields) {

    // TODO Fase 1: Per incloure Triangle
    //  Es suposa que serà una linia del fitxer de l'estil
    //  triangle, x1, y1, z1, x2, y2, z2, x3, y3, z3,, propietats del material, textura

    if (fields.size() != 13) {
        std::cerr << "Wrong brObject format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vector<vec3> points;
    vector<double> properties;

    vec3 pointA = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    vec3 pointB = vec3(fields[4].toDouble(), fields[5].toDouble(), fields[6].toDouble());
    vec3 pointC = vec3(fields[7].toDouble(), fields[8].toDouble(), fields[9].toDouble());

    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);

    mapping->mapeigPunt(pointA);
    mapping->mapeigPunt(pointB),
            mapping->mapeigPunt(pointC),

            // Construccio de l'objecte al Mon Virtual
            o = ObjectFactory::getInstance().createObject(points,
                                                          properties,
                                                          -1.0f,
                                                          "",
                                                          ObjectFactory::OBJECT_TYPES::TRIANGLE);
    // Construccio i assignacio del material
    auto mat = make_shared<Lambertian>(vec3(fields[10].toDouble(),fields[11].toDouble(),fields[12].toDouble()));
    o->setMaterial(mat);

    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}


void VirtualWorldReader::plaFound(QStringList fields) {
    // TODO Fase 1: Per incloure pla
    //Es suposa que tindràs una línia en el fitxer
    // plane, nx, ny, nz, d, , propietats del material, textura
    if (fields.size() != 9 && fields.size() != 10) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }

    if (QString::compare("plane", fields[0], Qt::CaseInsensitive) == 0) {
        // TODO Fase 1: Donar d'alta el pla com objecte de l'escena. Fixa't en el codi del mètode sphereFound
        // TODO Fase 1: Cal fer un pla acotat i no un pla infinit. Les dimensions del pla acotat seran les dimensions de l'escena en x i z
        shared_ptr<Object> o;

        vector<vec3> points;
        vector<double> properties;

        vec3 normalPlaBase = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
        float dPlaBase = fields[4].toDouble();

        points.push_back(normalPlaBase);
        properties.push_back(dPlaBase);

        mapping->mapeigPunt(normalPlaBase);
        mapping->mapeigValor(dPlaBase);


        o = ObjectFactory::getInstance().createObject(points,
                                                      properties,
                                                      -1.0f,
                                                      "",
                                                      ObjectFactory::OBJECT_TYPES::PLANE);

        // TODO Fase 4: llegir textura i afegir-la a l'objecte. Veure la classe Texture
        // Construccio i assignacio del material
        if(fields.size() == 9){
            auto mat = make_shared<Lambertian>(vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()));
            o->setMaterial(mat);
        }else if(fields.size() == 10){
            auto mat = make_shared<Metal>(vec3(fields[5].toDouble(),fields[6].toDouble(),fields[7].toDouble()));
            o->setMaterial(mat);
        }
        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }
}

void VirtualWorldReader::cylinderFound(QStringList fields){
    // Es suposa que serà una linia del fitxer .txt per definir el centre
    // del cilindre, el seu radi i la seva alçada:
    // cylinder, x, y, z, radi, alçada, propietats del material, textura
    if (fields.size() != 9) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }
    shared_ptr<Object> o;

    vector<vec3> points;
    vector<double> properties;

    vec3 center = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());

    points.push_back(center);
    properties.push_back(fields[4].toDouble());
    properties.push_back(fields[5].toDouble());

    mapping->mapeigPunt(center);
    mapping->mapeigValor(fields[4].toDouble());
    mapping->mapeigValor(fields[5].toDouble());


    o = ObjectFactory::getInstance().createObject( points,
                                                   properties,
                                                   -1.0f,
                                                   "",
                                                   ObjectFactory::OBJECT_TYPES::CYLINDER);

    auto mat = make_shared<Lambertian>(vec3(fields[6].toDouble(),fields[7].toDouble(),fields[8].toDouble()));
    o->setMaterial(mat);
    // Afegir objecte a l'escena
    scene->objects.push_back(o);
}
