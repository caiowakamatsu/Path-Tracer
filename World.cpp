//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"

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
bool World::colour(Ray& ray, ColourCache& cache, std::vector<Ray>& rays) {
    HitRecord best(nullptr, ray);

    // Main intersection loop
    for(auto shape : shapes){
        HitRecord rec(shape, ray);
        shape->intersect(ray, rec);
        if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
    }

    if(!best.hit){ // This runs if there was no intersection, and it hit the skyyyyyy
//        cache.colour = Vector3(1, 1, 1);
//        cache.intensity = 1;
        float u = 0.5f * (ray.direction.x + 1.0f);
        float v = 0.5f * (ray.direction.y + 1.0f);
        cache.colour = texture.getUV(u, v);
        cache.intensity = 1;
        return false;
    } else { // Compute colour and intensity at intersection point and new ray
        best.shape->getMaterial()->transformRay(ray, rays, best);
        Vector3 uv = best.shape->getUV(best.intersectionPoint);
        best.shape->getMaterial()->getColour(cache.intensity, cache.colour, uv);
        return true;
    }
}

// This function returns the colour of a single path trace (With recursive rays)
Vector3 World::trace(Ray ray, int max) {
    int actualBounces = -1;
    ColourCache caches[max];
    std::vector<Ray> rays = std::vector<Ray>();
    for(int i=0; i<max; i++){
        actualBounces++;
        if(!colour(ray,caches[i], rays)) break;
//        if(max - i - 1 <= 0){
//            for(int j=0; j<rays.size(); j++){
//                Vector3 recursiveRes = trace(rays[j], max - i - 1);
//                caches[i].colour.mix(recursiveRes, 0.5f);
//            }
//        };
        rays = std::vector<Ray>();
    }
    Vector3 finalColour = caches[actualBounces].colour;
    for(int i=actualBounces-1; i>=0; i--){
        finalColour.mix(caches[i].colour, caches[i].intensity);
    }
    return finalColour;
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
