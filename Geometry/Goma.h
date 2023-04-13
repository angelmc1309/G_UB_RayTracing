#pragma once

#include "Material.h"

class Goma : public Material
{
public:
    Goma();
    Goma(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b);
    virtual ~Goma();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};

