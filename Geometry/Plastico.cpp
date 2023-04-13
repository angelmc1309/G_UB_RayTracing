#include "Plastico.h"

Plastico::Plastico()
{
    // Plastico de color cian
    diffuse = vec3(0.0, 0.50980392, 0.50980392);
    ambiental = vec3(0.0, 0.1, 0.06);
    specular = vec3(0.50196078, 0.50196078, 0.50196078);
    transparent = vec3(0.0,0.0,0.0);
    shiness = 0.25f;
}


Plastico::Plastico(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b) : Material()
{
    diffuse = colorD;
    ambiental = colorA;
    specular = colorS;
    transparent = colorT;
    shiness = b;
}

Plastico::~Plastico(){}

// simple scattering
bool Plastico::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const {
    // rec.p (punt del raig on hi ha la intersecció) - origen
    vec3 target = normalize(r_in.dirVector());

    // metemos el vector incidente y la normal al plano
    vec3 reflectit = reflect(target, rec.normal);

    // ¿Es posible que hay acne?
    // En todo caso hay que sumarle un epsilon a rec.p
    // TODO
    r_out.push_back( Ray(rec.p, reflectit));
    color = diffuse;
    return true;
}
