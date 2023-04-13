#include "Circle.h"

Circle::Circle(vec3 center, float radi, float data):Object(data){
    this->center = center;
    this->radi = radi;

}

bool Circle::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const{

    vec3 normal = vec3(0, 1, 0);
    float d = -normal[0]*center.x - normal[1]*center.y - normal[2]*center.z;

    vec3 rp = r.initialPoint();
    vec3 vp = r.dirVector();
    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;

    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];


    if (temp > t_max || temp < t_min)
        return false;

    vec3 hitPoint = r.pointAtParameter(temp);
    vec3 distance = hitPoint - this->center;

    float d2 = dot(distance, distance);

    if (sqrtf(d2) > this->radi) return false;

    info.t = temp;
    info.p = hitPoint;

    info.normal = normal;
    info.mat_ptr = material.get();

    return true;
}

void Circle::aplicaTG(shared_ptr<TG> t) {

    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}


