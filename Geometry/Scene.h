#pragma once


#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Animation.h"
#include "Object.h"
#include "Sphere.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "Plastico.h"
#include "Metal.h"
#include "Laton.h"
#include "Goma.h"
#include "Transparente.h"
#include "ColorMap.h"
#include "FittedPlane.h"
#include "Light.h"

class Scene: public Hitable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           REALDATA,
           TEMPORALVW,
           TEMPORALDATA
    } DATA_TYPES;

    typedef enum
    {
        MATERIAL,
        COLORMAP
    } MATERIAL_TYPES;

    Scene();
    virtual ~Scene() {};

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColor (Ray &ray, int depth);

    vec3 BlinnPhong (HitInfo& info, const Ray& raig);

    float ambientalOclusion(vec3 origin, vec3 normal);

    vec3 ComputeRayColor(int depth, int maxDepth, Ray r_second, HitInfo info);

    shared_ptr<Object> terra;

    void update(int nframe);

    void setDimensions(vec3 p1, vec3 p2);

    vec2 projectionFunction(vec3 point);

    // dimensions de l'escena virtual
    vec3 pmin, pmax;

    // Vector d'objectes continguts a l'escena
    std::vector<shared_ptr<Object>> objects;

    // TODO FASE 2: Afegir llums a l'escena
    shared_ptr<vec3> global;
    std::vector<shared_ptr<Light>> listLights;

};

