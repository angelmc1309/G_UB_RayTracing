#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    diffuse = color;
    ambiental = color * 0.25f;
    specular = vec3(0.5,0.5,0.5);
    transparent = vec3(0.0,0.0,0.0);
    shiness = 1.0f;
}

Lambertian::Lambertian(const vec3& colorD, const vec3& colorA,
                       const vec3& colorS, const vec3& colorT, float b):Material(){
    diffuse = colorD;
    ambiental = colorA;
    specular = colorS;
    transparent = colorT;
    shiness = b;
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    for(int i = 0; i < 1; i++) {
        vec3 target = rec.p + rec.normal + this->RandomInSphere();
        r_out.push_back( Ray(rec.p, target-rec.p));
    }
    color = diffuse;
    return true;
}
