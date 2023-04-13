#include "Transparente.h"


Transparente::Transparente() : Material()
{
    // Objeto metalico transparente
    /*
    diffuse = vec3(0.714, 0.4284, 0.18144);
    ambiental = vec3(0.2115, 0.1275, 0.054);
    specular = vec3(0.393548, 0.271906, 0.166721);
    transparent = vec3(1.0, 1.0, 1.0);
    shiness = 0.2f;
    indiceRefraccion = 1.0f;
    */
    diffuse = vec3(0.7, 0.6, 0.5);
    ambiental = vec3(0.2,0.2, 0.2);
    specular = vec3(0.7, 0.7, 0.7);
    transparent = vec3(1.0, 1.0, 1.0);
    shiness = 10.0f;
    indiceRefraccion = 1.5f;

}

Transparente::Transparente(const vec3& colorD) : Material()
{
    diffuse = colorD;
    ambiental = colorD * 0.25f;
    specular = vec3(0.5,0.5,0.5);
    transparent = colorD;
    shiness = 1.0f;
    indiceRefraccion = 1.0f;
}


Transparente::Transparente(const vec3& colorD, const vec3& colorA, const vec3& colorS, const vec3& colorT, float b, float indexRefraccion) : Material()
{
    diffuse = colorD;
    ambiental = colorA;
    specular = colorS;
    transparent = colorT;
    shiness = b;
    indiceRefraccion = indexRefraccion;
}

Transparente::~Transparente(){}

bool Transparente::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, std::vector<Ray>& r_out) const {
    // Calculamos la Ley de Snell n2 · sin(theta1) = n2 · sin(theta2)

    vec3 normal = rec.normal;
    vec3 rayo_incidente = normalize(r_in.dirVector());

    float indice = 1.003f / this->indiceRefraccion;
    if (dot(rayo_incidente, normal) > 0.0) {
        indice = indiceRefraccion/1.003f;
        normal = -normal;// invertimos la normal
    }

    vec3 t = refract(rayo_incidente, normal, indice);
    color = transparent;
    r_out.push_back(Ray(rec.p, t));
    // Miramos si hay reflexion total interna
    if (length(t) < DBL_EPSILON) {
        vec3 t1 = reflect(rayo_incidente, normal);
        color = specular;
        r_out.push_back(Ray(rec.p, t1));
    }

    return true;
}
