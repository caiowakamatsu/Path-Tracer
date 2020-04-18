//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"
#include <cmath>
#include <algorithm>

World::World(int w, int h, Texture& t, int m, int s) : texture(t) {
    width = w;
    height = h;
    maxBounce = m;
    spp = s;
    aspect = (float) width / height;
}

World::~World() = default;

void World::addShape(Shape * shapePtr) {
    shapes.push_back(shapePtr);
}

// This returns a single ray trace
bool World::colour(Ray& ray, HitRecord& out) {
    HitRecord best(nullptr, ray);

    // Main intersection loop
    for (auto shape : shapes) {
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }

    if (!best.hit) { // This runs if there was no intersection, and it hit the skyyyyyy
        Vector3 d = Vector3() - ray.direction;
        float u = 0.5f + atan2f(d.z, d.x) / (2 * M_PI);
        float v = 0.5f - asinf(d.y) / M_PI;
        best.albedo = texture.getUV(u, v);
        out = best;
        return false;
    } else { // Compute colour and intensity at intersection point and new ray
        best.shape->getMaterial()->transformRay(ray, best);
        Vector3 uv = best.shape->getUV(best.intersectionPoint);
        best.outRay = ray;
        best.shape->getMaterial()->getColour(best.emission, best.albedo, uv, best.reflectiveness, best);
        out = best;
        return true;
    }
}

// This function returns the colour of a single path trace (With recursive rays)
Vector3 World::trace(Ray ray, int max) {
    Vector3 throughput(1, 1, 1);
    Vector3 final(0, 0, 0);
    HitRecord cur = HitRecord(nullptr, ray);
    for(int i=0; i<max; i++){
        if(!colour(ray, cur)){
            Vector3 a = throughput * cur.albedo;
            final += a;
            break;
        }
        Vector3 a = throughput * cur.emission;
        final += a;
        a = cur.albedo * cur.reflectiveness;
        throughput *= a;
    }
    return final;
//    return Vector3(fmin(final.x, 1), fmin(final.y, 1), fmin(final.z, 1));
}

// Renders out the entire scene
void World::render(int* out) {

    auto camera = Camera(new Vector3(0, 0, 20), new Vector3(0, 0, -1), 30, aspect);
    Ray ray;
    #pragma omp parallel
    {
        #pragma omp for
        for(int x=0; x<width; x++){
            for(int y=0; y<height; y++){
                Vector3 sample(0, 0, 0);
                for(int i=0; i<spp; i++){
                    ray = camera.getRay(
                            ((float) x + drand48()) / width * 2 - 1,
                            ((float) y + drand48()) / height * 2 - 1);
                    Vector3 aa_sample = trace(ray, maxBounce);
                    sample += aa_sample;
                }
                out[x + (height-y-1) * width] =
                        255 << 24 |
                        (((int) ((sqrtf(sample.z / spp)) * 255))&0x0ff) << 16 |
                        (((int) ((sqrtf(sample.y / spp)) * 255))&0x0ff) << 8 |
                        (((int) ((sqrtf(sample.x / spp)) * 255))&0x0ff) << 0;
            }
        }
    }

}
