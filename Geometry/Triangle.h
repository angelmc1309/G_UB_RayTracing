#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"

class Triangle:public Object
{
public:
    Triangle(vec3 punto1, vec3 punto2, vec3 punto3, float data);
    virtual ~Triangle(){}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;
private:
    vec3 punto1;
    vec3 punto2;
    vec3 punto3;

};

#endif // TRIANGLE_H
