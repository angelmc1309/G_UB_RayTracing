#include "SceneFactoryData.h"
#include "Geometry/MaterialTextura.h"
SceneFactoryData::SceneFactoryData(shared_ptr<ConfigMappingReader> mr):SceneFactory()
{
    map = make_shared<Mapping>(mr);

    this->normalPlaBase = mr->normalPlaorCentre;
    this->dPlaBase = mr->dPlaorRadi;
    this->groundType = mr->groundType;
    this->xMax = mr->Vxmax;
    this->xMin = mr->Vxmin;
    this->zMax = mr->Vzmax;
    this->zMin = mr->Vzmin;
    this->texturePath = mr->texturePath;
}


shared_ptr<Scene> SceneFactoryData::createScene(QString filename) {

    auto scene = make_shared<Scene>();
    auto rdr = make_shared<RealDataReader>(scene);
    rdr->readFile(filename, map);

    if (groundType == ObjectFactory::OBJECT_TYPES::SPHERE)
        scene->terra = make_shared<Sphere>(this->normalPlaBase, this->dPlaBase, -1.0f);

    else if (groundType == ObjectFactory::OBJECT_TYPES::PLANE)
        scene->terra = make_shared<FittedPlane>(this->normalPlaBase, this->dPlaBase, -1.0f,
                                                this->xMax, this->xMin, this->zMax, this->zMin);

    scene->terra->setMaterial(make_shared<MaterialTextura>(this->texturePath));
    //auto mat = make_shared<Lambertian>(vec3(0.7, 0.4, 0.4));
    //scene->terra->setMaterial(mat);

    scene->objects.push_back(scene->terra);
    return scene;
}

shared_ptr<Scene> SceneFactoryData::createScene() {
    auto scene= make_shared<Scene>();
    //  TODO: Només si voleu provar manualment algunes dades posades
    //  hardcoded aqui

    return scene;
}
