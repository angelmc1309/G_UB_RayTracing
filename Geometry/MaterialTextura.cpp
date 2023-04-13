#include "MaterialTextura.h"

MaterialTextura::MaterialTextura(QString nomfitxer) : Material()
{
    this->texture = make_shared<Texture>(nomfitxer);
    ambiental = vec3(0.001, 0.001, 0.001);
    specular = vec3(0.2,0.2,0.2);
    transparent = vec3(0.0,0.0,0.0);
    shiness = 5;
}

MaterialTextura::~MaterialTextura() {

}

vec3 MaterialTextura::getDiffuse(vec2 uv) const {
    return this->texture->getColorPixel(uv);
}

bool MaterialTextura::hasTexture() {
    return true;
}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    return false;
}
