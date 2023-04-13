#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H
#pragma once

#include "Object.h"
#include "Animation.h"
#include "Translate.h"
#include "glm/gtx/constants.hpp"

class FittedPlane: public Object
{
public:
    FittedPlane();
    FittedPlane(vec3 normal, vec3 pass_point, float d);

    FittedPlane(vec3 normal, float d, float v, float xMin, float xMax, float zMin, float zMax);

    virtual ~FittedPlane(){}
    virtual bool hit(const Ray &r, float t_min, float t_max, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    double xMax, xMin, zMax, zMin;

private:
    vec3 normal;
    vec3 point;
};

#endif // FITTEDPLANE_H
