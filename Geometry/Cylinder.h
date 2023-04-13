#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "Circle.h"

class Cylinder: public Object
{
public:
    Cylinder(vec3 center, float radi, float alcada, float data);
    virtual ~Cylinder(){}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;
    bool hitCircle(const Ray &, float, float, float, HitInfo& info) const;

private:
    vec3 center;
    float radi;
    float alcada;
};

#endif // CYLINDER_H
