#include "FittedPlane.h"

FittedPlane::FittedPlane(vec3 normal, vec3 pass_point, float v) : Object(v)
{
    this->normal = normalize(normal);
    this->point = pass_point;
}

FittedPlane::FittedPlane(vec3 normal, float d, float v, float xMax, float xMin, float zMax, float zMin) : Object(v) {
    this->xMax = xMax;
    this->xMin = xMin;
    this->zMax = zMax;
    this->zMin = zMin;

    this->normal = normalize(normal);

    if (abs(normal.z)>DBL_EPSILON)
        this->point = vec3(0.0, 0.0, -d/normal.z);

    else if (abs(normal.y)>DBL_EPSILON)
        this->point = vec3(0.0, -d/normal.y, 0.0);

    else
        this->point = vec3(-d/normal.x, 0.0, 0.0);
};


bool FittedPlane::hit(const Ray &raig, float t_min, float t_max, HitInfo &info) const {
    // Comprovem interseccio entre el pla i el raig
    // Comprovem si el normal al pla i el raig son ortogonals.
    // En aquest cas son paralels i no hi ha interseccio

    if (dot(raig.dirVector(), normal) == 0)
        return false;

    // En els altres casos hi haurà interseccio (si estem en el rang de min/max).
    // Cal omplir la info.

    // PLA: Ax+By+Cz+D=0
    // on A,B,C = normal

    // 1) Calculem la D = -Ax-By-Cz
    float d = -normal[0]*point[0] - normal[1]*point[1] - normal[2]*point[2];

    // 2) Imposem que la recta p+tv compleixi l'eq del pla
    // A(p1 + tv1) + ... + D = 0
    // Aillem la t

    vec3 rp = raig.initialPoint();
    vec3 vp = raig.dirVector();

    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;
    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    // Retornem false si no estem en el rang demanat
    if (temp > t_max || temp < t_min)
        return false;

    vec3 point = raig.pointAtParameter(temp);

    if (point.x < xMin || point.x > xMax || point.z < zMin || point.z > zMax)
        return false;

    // Omplim el camp de info:
    info.t = temp;
    info.p = point;

    info.normal = normal;
    info.mat_ptr = material.get();

    return true;
}

void FittedPlane::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        // Nomes movem el punt de pas
        vec4 newp(this->point, 1.0);
        newp = t->getTG() * newp;
        this->point.x = newp.x;
        this->point.y = newp.y;
        this->point.z = newp.z;
    }

}

