#ifndef TRANSPARENTE_H
#define TRANSPARENTE_H
#pragma once

#include "Material.h"


class Transparente : public Material
{
public:
    Transparente();
    Transparente(const vec3& colorD);
    Transparente(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b, float indiceRefraccion);
    virtual ~Transparente();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
    float indiceRefraccion;



};

#endif // TRANSPARENTE_H
