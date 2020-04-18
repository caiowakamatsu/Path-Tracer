//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"
#include <cmath>

World::World(int w, int h, Texture& t, int m, int r) : texture(t) {
    width = w;
    height = h;
    maxBounce = m;
    maxRefraction = r;
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
    for(auto shape : shapes){
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }

    if(!best.hit){ // This runs if there was no intersection, and it hit the skyyyyyy
        Vector3 d = Vector3() - ray.direction;
        float u = 0.5f + atan2f(d.z, d.x) / (2 * M_PI);
        float v = 0.5f - asinf(d.y) / M_PI;
        best.emission = texture.getUV(u, v);
        best.albedo = Vector3(0, 0, 0);
        out = best;
        return false;
    } else { // Compute colour and intensity at intersection point and new ray
        best.shape->getMaterial()->transformRay(ray, best);
        Vector3 uv = best.shape->getUV(best.intersectionPoint);
        best.shape->getMaterial()->getColour(best.emission, best.albedo, uv);
        out = best;
        return true;
    }
}

Vector3 World::trace(Ray ray, int max) {
    Vector3 throughput(1, 1, 1);
    Vector3 final(0, 0, 0);
    HitRecord cur = HitRecord(nullptr, ray);
    for(int i=0; i<max; i++){
        if(!colour(ray, cur)){
            Vector3 a = throughput * cur.emission;
            final += a;
            break;
        }
        Vector3 a = throughput * cur.emission;
        final += a;
        throughput *= cur.albedo;
    }
    return final;
}

// Renders out the entire scene
void World::render(int* out) {
    auto camera = Camera(new Vector3(0, 0, 20), new Vector3(0, 0, -1), 30, aspect);
    Ray ray;
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            ray = camera.getRay(
                    (float) x / width * 2 - 1,
                    (float) y / height * 2 - 1);
            Vector3 sample = trace(ray, maxBounce);

            out[x + (height-y-1) * width] =
                    255 << 24 |
                    (((int) ((sample.z) * 255))&0x0ff) << 16 |
                    (((int) ((sample.y) * 255))&0x0ff) << 8 |
                    (((int) ((sample.x) * 255))&0x0ff) << 0;
        }
    }
}
