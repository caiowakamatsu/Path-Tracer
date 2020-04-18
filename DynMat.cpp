//
// Created by legend on 4/18/20.
//

#include "DynMat.h"


DynMat::DynMat(float d, float r, Texture t, Vector3 e) : diffuse(d), reflectiveness(r), texture(t), emission(e) {

}

void DynMat::transformRay(Ray &ray, HitRecord &rec) {
    Vector3 rayOrigin = ray.direction;
    Vector3 a = rec.normal * rec.normal.dot(rec.ray.direction) * 2;
    Vector3 reflection = rayOrigin - a;
    Vector3 offset = rec.normal * 0.0001f;
    ray.origin = rec.intersectionPoint + offset;
    ray.direction = reflection.toUnitVector();
    if(diffuse > 0){
        Vector3 point = Vector3(drand48() * 2 - 1, drand48() * 2 - 1, drand48() * 2 - 1);
        point = point.toUnitVector();
        ray.direction.mix(point, diffuse);
    }

}

void DynMat::getColour(Vector3& outEmission, Vector3 &outColour, Vector3 &uv) {
    outEmission = emission;
    outColour = texture.getUV(uv.x, uv.y);
}
