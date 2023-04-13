#include "Scene.h"
#include <typeinfo>
Scene::Scene()
{
    pmin.x = -0.5f;  pmin.y = -0.5f; pmin.z = -0.5f;
    pmax.x = 0.5f;  pmax.y = 0.5f; pmax.z = 0.5f;
}


/*
** TODO: FASE 1: Metode que testeja la interseccio contra tots els objectes de l'escena
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

    // TODO FASE 0 i FASE 1: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode intersection per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el IntersectionInfo del raig,
    // pero no en aquesta funcio.
    bool returnVal = false, iterVal = false;
    int minIndex = 0;
    float minT = t_max;

    for (unsigned int i = 0; i < objects.size(); i++) {
        iterVal = objects.at(i)->hit(raig,t_min,t_max,info);
        returnVal |= iterVal;
        if (info.t > minT && iterVal) {
            objects.at(minIndex)->hit(raig,t_min,t_max,info);

        } else if (iterVal) {
            minIndex = i;
            minT = info.t;
        }
    }
   return returnVal;
}


/*
** TODO: Funcio ComputeColorRay es la funcio recursiva del RayTracing.
** TODO: FASE 0 per a fer el degradat del fons
** TODO: FASE 1 per a cridar a la intersecció amb l'escena i posar el color de l'objecte
** TODO: Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** TODO: Fase 2 per a tractar reflexions i transparències
**
*/
vec3 Scene::ComputeColor (Ray &ray, int depth) {
    // TODO: A canviar el càlcul del color al afegit textures
    vec3 color;
    vec3 ray2;

    ray2 = normalize(ray.direction);

    vec3 colorTop(1.f,1.f,1.f);
    vec3 colorBot(0.5f,0.7f,1.f);
    //color = 0.5f*vec3(ray2.x+1, ray2.y+1, ray2.z+1);
    color = colorBot * ray2.y + colorTop * (1.f - ray2.y);
    HitInfo info;

    if (hit(ray,0,pow(2.0,20.0),info)) {
        //color = (normalize(info.normal)+1.f) / 2.f;
        //color = BlinnPhong(info, ray);
        color = ComputeRayColor(0, depth, ray, info);
    }
    return color;
}


void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        objects[i]->update(nframe);
    }
}


vec3 Scene::BlinnPhong(HitInfo &info, const Ray &raig) {

    vec3 interPoint = info.p;
    vec3 L, N, H;
    vec3 color(0.0,0.0,0.0);
    float epsilon = 0.01f;
    shared_ptr<Light> light;

    if (info.mat_ptr->hasTexture()) {
        info.textureCoords = this->projectionFunction(info.p);
    }

    for (uint i = 0; i < this->listLights.size(); i++) {
        vec3 iterColor(0,0,0);
        vec3 factorAtenuacio(0,0,0);
        light = this->listLights.at(i);

        L = normalize(light->position - interPoint);

        //SHADOW CHECK
        Ray rayToLight(info.p,L);
        HitInfo infoShadowRay;
        while (hit(rayToLight,epsilon,distance(rayToLight.origin,light->position),infoShadowRay)) {
            factorAtenuacio.x = (1.0f - infoShadowRay.mat_ptr->transparent.x)
                    + infoShadowRay.mat_ptr->transparent.x*factorAtenuacio.x;
            factorAtenuacio.y = (1.0f - infoShadowRay.mat_ptr->transparent.y)
                    + infoShadowRay.mat_ptr->transparent.y*factorAtenuacio.y;
            factorAtenuacio.z = (1.0f - infoShadowRay.mat_ptr->transparent.z)
                    + infoShadowRay.mat_ptr->transparent.z*factorAtenuacio.z;
            rayToLight.origin = infoShadowRay.p;
            if(factorAtenuacio.x >= 1.0f && factorAtenuacio.y >= 1.0f
                    && factorAtenuacio.x >= 1.0f){
                break;
            }
        }
        factorAtenuacio= glm::clamp(factorAtenuacio,0.0,1.0);
        if(factorAtenuacio.x >= 1.0f && factorAtenuacio.y >= 1.0f
                && factorAtenuacio.x >= 1.0f){
            continue;;
        }

        //DIFUSE COLOR
        vec3 difuseAndSpecular(0.0,0.0,0.0);
        N = normalize(info.normal);
        float LN = glm::max(dot(L,N),0.0f);
        difuseAndSpecular += LN * info.mat_ptr->getDiffuse(info.textureCoords) * light->difusa;

        //SPECULAR COLOR
        vec3 V = normalize(raig.origin-info.p);
        H = normalize((L + V) / (sqrt((L.x + V.x)*(L.x + V.x)) +
                                 sqrt((L.y + V.y)*(L.y + V.y)) +
                                 sqrt((L.z + V.z)*(L.z + V.z))));
        difuseAndSpecular += pow(glm::max(dot(N, H), 0.0f), info.mat_ptr->shiness) * info.mat_ptr->specular * light->specular;

        //ATENUACIO
        double d = distance(interPoint, light->position);
        difuseAndSpecular *= 1.0f / (light->atenuacio.x * pow(d, 2.0) + light->atenuacio.y * d + light->atenuacio.z);
        iterColor += difuseAndSpecular;

        //AMBIENTAL COLOR(local)
        //float oclusion = 1.0f - ambientalOclusion(info.p, info.normal);
        iterColor += (light->ambiental) * info.mat_ptr->ambiental;
        color += iterColor * (vec3(1,1,1)-factorAtenuacio);
    }

    // ADD GLOBAL LIGHT
    //float factorAmbientalOclusion = ambientalOclusion(info.p, info.normal);
    color += *(this->global) * info.mat_ptr->ambiental;

    return color;
}

float Scene::ambientalOclusion(vec3 origin, vec3 normal){

    Ray *vecToSky = new Ray(origin, normal);
    HitInfo *info = new HitInfo();

    int numberSkyRays = 0;

    //Haremos un total de 5 rayos aleatorios
    for(int i =0; i < 30; i++){
        vecToSky->direction *= (1.0f+float(rand())/(RAND_MAX/0.1));
        if(!hit(*vecToSky, 0.0001, 99999, *info)){
            numberSkyRays++;
        }
    }

    delete vecToSky;
    delete info;

    return numberSkyRays/5;
}

vec3 Scene::ComputeRayColor(int depth, int maxDepth, Ray r_second, HitInfo info){

    if(depth == maxDepth) {
        return BlinnPhong(info, r_second);
    }

    vector<Ray> *secondaryRays = new vector<Ray>();
    vec3 reflexColor, totalColor;

    info.mat_ptr->scatter(r_second, info, reflexColor, *secondaryRays);
    int raysHit = 0;

    for (uint i = 0; i < secondaryRays->size(); i++) {
        Ray next_Ray = secondaryRays->at(i);
        HitInfo next_info = info;

        if (hit(next_Ray, 0.001f, 99999, next_info)) {
           raysHit++;
           totalColor += BlinnPhong(info, r_second) + reflexColor*ComputeRayColor(depth+1, maxDepth, next_Ray, next_info);
        }
    }

    delete secondaryRays;

    if (totalColor != vec3(0,0,0))
        return totalColor * (1.0f / raysHit);
    else
        return BlinnPhong(info, r_second);

}

vec2 Scene::projectionFunction(vec3 point) {
    shared_ptr<FittedPlane> a = std::dynamic_pointer_cast<FittedPlane>(this->terra);
    vec3 origin = vec3(a->xMin, 0.0, a->zMin);
    vec2 uv;
    float w = (a->xMax - a->xMin);
    float h = (a->zMax - a->zMin);
    uv.x = (point.x - origin.x) / w;
    uv.y = (point.z - origin.z) / h;

    return uv;

}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

