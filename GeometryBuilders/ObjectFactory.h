#pragma once

#include "Geometry/Object.h"
#include "Geometry/Sphere.h"
#include "Geometry/Plane.h"
#include "Geometry/Triangle.h"
#include "Geometry/Cylinder.h"
#include "Geometry/BoundaryObject.h"


class ObjectFactory
{
    ObjectFactory(){};

public:
    enum  OBJECT_TYPES{
        SPHERE,
        PLANE,
        TRIANGLE,
        CYLINDER,
        BR_OBJECT
    };

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(vec3 v, double aux, float data, OBJECT_TYPES t);
    shared_ptr<Object> createObject(vec3 x, vec3 y, vec3 z, float data, OBJECT_TYPES t);
    shared_ptr<Object> createObject(vec3 x, double r, double a, float data, OBJECT_TYPES t);
    shared_ptr<Object> createObject(QString &fileName, float data, OBJECT_TYPES t);
    shared_ptr<Object> createObject(vector<vec3>points, vector<double> properties, float data, QString fileName, OBJECT_TYPES t);

};

