#include "Triangle.h"

Triangle::Triangle(vec3 punto1, vec3 punto2, vec3 punto3, float data) : Object(data)
{
    this->punto1 = punto1;
    this->punto2 = punto2;
    this->punto3 = punto3;
}

bool Triangle::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const {
    vec3 v1 = punto2 - punto1;
    vec3 v2 = punto3 - punto1;
    vec3 normal = cross(v1, v2);

    if (dot(r.dirVector(), normal) == 0)
        return false;


    float d = -normal[0]*punto1[0] - normal[1]*punto1[1] - normal[2]*punto1[2];

    vec3 rp = r.initialPoint();
    vec3 vp = r.dirVector();

    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;
    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    // Retornem false si no estem en el rang demanat
    if (temp > t_max || temp < t_min)
        return false;


    vec3 p = r.pointAtParameter(temp);
    if (dot(cross(punto2 - punto1, p - punto1), normal) < 0) return false;
    if (dot(cross(punto3 - punto2, p - punto2), normal) < 0) return false;
    if (dot(cross(punto1 - punto3, p - punto3), normal) < 0) return false;

    // Omplim el camp de info:
    info.t = temp;
    info.p = p;

    info.normal = normal;
    info.mat_ptr = material.get();

    return true;
}

void Triangle::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        // Per ara només es preveuen translacions
        vec4 pA(punto1, 1.0);
        pA = t->getTG() * pA;
        punto1.x = pA.x; punto1.y = pA.y; punto1.z = pA.z;

        vec4 pB(punto2, 1.0);
        pB = t->getTG() * pB;
        punto2.x = pB.x; punto2.y = pB.y; punto2.z = pB.z;

        vec4 pC(punto3, 1.0);
        pC = t->getTG() * pC;
        punto3.x = pC.x; punto3.y = pC.y; punto3.z = pC.z;
    }
}
