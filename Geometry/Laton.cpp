#include "Laton.h"

Laton::Laton()
{
    diffuse = vec3(0.780392, 0.568627, 0.113725);
    ambiental = vec3(0.329412, 0.223529, 0.027451);
    specular = vec3(0.992157, 0.941176, 0.807843);
    transparent = vec3(0.0,0.0,0.0);
    shiness = 0.21794872f;
}

Laton::Laton(const vec3& colorD, const vec3& colorA,
                       const vec3& colorS, const vec3& colorT, float b) : Material(){
    diffuse = colorD;
    ambiental = colorA;
    specular = colorS;
    transparent = colorT;
    shiness = b;
}

Laton::~Laton(){}

// simple scattering
bool Laton::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    // rec.p (punt del raig on hi ha la intersecció) - origen
    vec3 target = normalize(r_in.dirVector());

    // metemos el vector incidente y la normal al plano
    vec3 reflectit = reflect(target, rec.normal);

    // ¿Es posible que hay acne?
    // En todo caso hay que sumarle un epsilon a rec.p
    // TODO
    r_out.push_back( Ray(rec.p, reflectit));
    color = specular;
    return true;
}
