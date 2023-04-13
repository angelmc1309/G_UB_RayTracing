#include "ObjectFactory.h"

//! createObject
/*!
  \sa testMe()
  \param x coordenada x on cal colocar el centre de l'objecte en el món virtual
  \param y coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param z coordenada x on cal colocar el centre de l'objecte en el món virtual.
  \param aux paràmetre addicional per codificar el radi de l'esfera o la d del pla.
  \param v valor d'escalaque cal aplicar a l'objecte
  \param t tipus d'objecte a construir: SPHERE, PLANE, ....
*/

shared_ptr<Object> ObjectFactory::createObject(vec3 v, double aux, float data, OBJECT_TYPES t)
{
    shared_ptr<Object> o;
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE:
        o = make_shared<Sphere>(v, aux, data);
        break;
    case PLANE:
        o = make_shared<Plane>(v, aux, data);
        break;
    default:
        break;
    }
    return o;
}

shared_ptr<Object> ObjectFactory::createObject(QString &fileName, float data, OBJECT_TYPES t){
    shared_ptr<Object> o;
     switch (t) {
     case BR_OBJECT:
         o = make_shared<BoundaryObject>(fileName, data);
         break;
     default:
         break;
     }

     return o;
}

shared_ptr<Object> ObjectFactory::createObject(vec3 x, vec3 y, vec3 z, float data, OBJECT_TYPES t){
    shared_ptr<Object> o;

    switch (t) {
    case TRIANGLE:
        o = make_shared<Triangle>(x, y, z, data);
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<Object> ObjectFactory::createObject(vec3 x, double r, double a, float data, OBJECT_TYPES t){
    shared_ptr<Object> o;

    switch (t) {
    case CYLINDER:
        o = make_shared<Cylinder>(x, r, a, data);
        break;
    default:
        break;
    }

    return o;
}

shared_ptr<Object> ObjectFactory::createObject(vector<vec3>points, vector<double> properties, float data, QString fileName, OBJECT_TYPES t){
    shared_ptr<Object> o;
    // TODO Fase 1:
    // Quan es creen els objectes cal que les coordenades
    // es mapegin a mon virtual aquí
    // TODO Fase 1:
    // Incloure diferents objectes: CILINDRES, TRIANGLES, BR_OBJECTES, PRISMES POLIGONALS
    switch (t) {
    case SPHERE:
        o = make_shared<Sphere>(points.at(0), properties.at(0), data);
        break;
    case PLANE:
        o = make_shared<Plane>(points.at(0), properties.at(0), data);
        break;
    case TRIANGLE:
        o = make_shared<Triangle>(points.at(0), points.at(1), points.at(2), data);
        break;
    case BR_OBJECT:
        o = make_shared<BoundaryObject>(fileName, data);
        break;
    case CYLINDER:
        o = make_shared<Cylinder>(points.at(0), properties.at(0), properties.at(1), data);
        break;
    default:
        break;
    }

    return o;
}

