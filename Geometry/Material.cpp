#include "Material.h"



Material::Material():
    diffuse(1.0f)
  {}

Material::~Material()
{}

Material::Material(vec3 d){
    diffuse = d;
}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){
    this->ambiental = a;
    this->diffuse = d;
    this->specular = s;
    this->transparent = k;
    this->shiness = beta;
}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(double(rand())/RAND_MAX, double(rand())/RAND_MAX,double(rand())/RAND_MAX) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

vec3 Material::getDiffuse(vec2 point) const {
    return this->diffuse;
}

bool Material::hasTexture() {
    return false;
}
