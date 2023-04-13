#include "Metal.h"

Metal::Metal() : Material()
{
    /*
    diffuse = vec3(0.714, 0.4284, 0.18144);
    ambiental = vec3(0.2115, 0.1275, 0.054);
    specular = vec3(0.393548, 0.271906, 0.166721);
    shiness = 0.2f;
    */
    diffuse = vec3(0.7, 0.6, 0.5);
    ambiental = vec3(0.2,0.2, 0.2);
    specular = vec3(0.7, 0.7, 0.7);
    transparent = vec3(0.0,0.0,0.0);
    shiness = 10.0;

}
Metal::Metal(const vec3& colorD){
    diffuse = colorD;
    ambiental = vec3(0.2,0.2, 0.2);
    specular = colorD;
    transparent = vec3(0.0,0.0,0.0);
    shiness = 10.0;
}


Metal::Metal(const vec3& colorD, const vec3& colorA,
                       const vec3& colorS, const vec3& colorT, float b) : Material(){
    diffuse = colorD;
    ambiental = colorA;
    specular = colorS;
    transparent = colorT;
    shiness = b;
}

Metal::~Metal(){}

// simple scattering
bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
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
