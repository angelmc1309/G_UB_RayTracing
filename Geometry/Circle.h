#ifndef CIRCLE_H
#define CIRCLE_H

#include "Object.h"
#include "Animation.h"
#include "Translate.h"

class Circle:public Object
{
public:
    Circle(vec3 center, float radi, float data);
    virtual ~Circle(){}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;
private:
    vec3 center;
    float radi;

};


#endif // CIRCLE_H
