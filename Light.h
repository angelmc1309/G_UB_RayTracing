#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>

using namespace glm;


class Light
{
public:
    Light();
    Light(vec3 ambiental, vec3 difusa, vec3 specular, vec3 coeficients, vec3 pos);
    virtual ~Light();

    vec3 ambiental;
    vec3 difusa;
    vec3 specular;
    vec3 atenuacio;
    vec3 position;

};

#endif // LIGHT_H
