#pragma once

#include "Material.h"


class Metal : public Material
{
public:
    Metal();
    Metal(const vec3& colorD);
    Metal(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b);
    virtual ~Metal();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};


