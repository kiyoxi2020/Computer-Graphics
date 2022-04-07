//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"
#include "Vector.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here
    
    Intersection insect = Scene::intersect(ray);
    Material *m = insect.m;
    Object *hitObject = insect.obj;
    Vector3f hitColor = Vector3f(0.0, 0.0, 0.0);
    Vector2f uv;
    uint32_t index = 0;
    if(insect.happened){
        float pdf_light;
        Intersection insect_light;
        sampleLight(insect_light, pdf_light);
        Vector3f p = insect.coords;
        Vector3f x = insect_light.coords;
        Vector3f ws = normalize(x-p);
        Vector3f wo = normalize(-ray.direction);
        Vector3f N = insect.normal.normalized();
        Vector3f NN = insect_light.normal.normalized();
        Ray px = Ray(p, ws);
        if((Scene::intersect(px).coords-x).norm()<EPSILON){
            hitColor += insect_light.emit * m->eval(wo, ws, N) *
                dotProduct(ws, N) * dotProduct(-ws, NN) / (dotProduct(x-p, x-p) * pdf_light);
        }
        if(m->hasEmission())
            return m->getEmission();
        float ksi = get_random_float();
        if(ksi<=RussianRoulette){
            Vector3f wi = normalize(insect.m->sample(wo, N));
            Intersection q = Scene::intersect(Ray(p, wi));
            if(q.happened && !q.m->hasEmission()){
                    hitColor += castRay(Ray(p, wi), depth+1) * m->eval(wo,wi,N) *
                        dotProduct(wi, N) / (m->pdf(wo, wi, N)*RussianRoulette);
            }
        }
    }
    hitColor = Vector3f::Max(hitColor, Vector3f(0.0,0.0,0.0));
    return hitColor;

}