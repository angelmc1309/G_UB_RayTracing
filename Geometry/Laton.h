#pragma once

#include "Material.h"

class Laton : public Material
{
public:
    Laton();
    Laton(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b);
    virtual ~Laton();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};


