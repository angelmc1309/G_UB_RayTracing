#pragma once

#include "Material.h"
#include "Texture.h"

class MaterialTextura : public Material
{
public:
    MaterialTextura(QString nomfitxer);
    virtual ~MaterialTextura();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
    virtual vec3 getDiffuse(vec2 point) const;
    virtual bool hasTexture();

private:
    shared_ptr<Texture> texture;
};
