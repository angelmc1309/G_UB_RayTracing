#include "Light.h"

Light::Light(){}

Light::Light(vec3 difusa, vec3 ambiental, vec3 specular, vec3 coeficients, vec3 pos)
{
    this->ambiental = ambiental;
    this->difusa = difusa;
    this->specular = specular;
    this->atenuacio = coeficients;
    this->position = pos;
}

Light::~Light(){}
