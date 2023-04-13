#include "Cylinder.h"

Cylinder::Cylinder(vec3 center, float radi, float alcada, float data):Object(data)
{
    this->center = center;
    this->radi = radi;
    this->alcada = alcada;
}

bool Cylinder::hit(const Ray &r, float t_min, float t_max, HitInfo &info) const {

    float a, b, c, discriminant, t, t1, t2;

    a = pow(r.direction.x,2.0f) + pow(r.direction.z, 2.0f);

    b = 2.0f*r.direction.x*(r.origin.x - center.x) + 2.0f*r.direction.z * (r.origin.z - center.z);

    c = pow(r.origin.x - center.x, 2.0f) + pow(r.origin.z - center.z, 2.0f) - pow(radi, 2.0f);

    discriminant = b*b - 4.0f*a*c;

        if (discriminant >= 0.0f) {
            t1 = (-b + sqrt(discriminant)) / (2.0f*a);
            t2 = (-b - sqrt(discriminant)) / (2.0f*a);
        }
        else {
            return false;
        }


    t = std::min(t1, t2);    //choose the smallest and >=0 t

    if(t<t_min || t>t_max)
        t = std::max(t1, t2);
    if(t<t_min || t>t_max)
        return false;

    vec3 point = r.pointAtParameter(t);

    if (point.y <= center.y)
        return hitCircle(r,t_min, t_max, 0, info);

    else if(point.y >= center.y + alcada)
        return hitCircle(r, t_min, t_max, alcada, info);


   vec3 normal = normalize(vec3(2.0f * point.x, 0.0f, 2.0f * point.z));

   info.t = t;
   info.p = point;

   info.normal = normal;
   info.mat_ptr = material.get();

   return true;

}

void Cylinder::aplicaTG(shared_ptr<TG> t) {
    if (dynamic_pointer_cast<shared_ptr<TranslateTG>>(t)) {
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
}


bool Cylinder::hitCircle(const Ray &r,float t_min, float t_max, float alcada, HitInfo &info) const {
    vec3 centre2 = vec3(center.x, center.y + alcada, center.z);
    vec3 normal = vec3(0, 1, 0);

    float d = -normal[0]*center.x - normal[1]*(centre2.y) - normal[2]*center.z;

    vec3 rp = r.initialPoint();
    vec3 vp = r.dirVector();

    float temp =  -normal[0]*rp[0] - normal[1]*rp[1] - normal[2]*rp[2] - d;
    temp/= normal[0]*vp[0] + normal[1]*vp[1] + normal[2]*vp[2];

    if (temp > t_max || temp < t_min)
        return false;


    vec3 hitPoint = r.pointAtParameter(temp);
    vec3 distance = hitPoint - centre2;

    float d2 = dot(distance, distance);

    if (sqrtf(d2) > this->radi) return false;

    info.t = temp;
    info.p = hitPoint;

    info.normal = normal;
    info.mat_ptr = material.get();

    return true;
}
