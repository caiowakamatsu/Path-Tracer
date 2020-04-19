//
// Created by legend on 3/18/20.
//

#include <cstdio>
#include "iostream"
#include "World.h"
#include <cmath>
#include <algorithm>
#include <thread>

World::World(int w, int h, Texture& t, int m, int s) : texture(t) {
    width = w;
    height = h;
    maxBounce = m;
    spp = s;
    aspect = (float) width / height;

    // Split the world into different chunks to be rendered
    chunkCountX = 16; // Ill add a way to do these dynamically or something later
    chunkCountY = 16;
    chunkSizeX = width / chunkCountX;
    chunkSizeY = height / chunkCountY;
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
        best.emission = texture.getUV(u, v);
        best.albedo = Vector3(0, 0, 0);
        best.reflectiveness = 0;
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
            Vector3 a = throughput * cur.emission;
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

// Renders a chunk of the scene
void World::renderChunk(int id, int* out, Camera& cam){
    Ray ray;
    int sx = (id % chunkCountX) * chunkSizeX;
    int sy = (id / chunkCountY) * chunkSizeY;
    int maxX = sx + chunkSizeX;
    int maxY = sy + chunkSizeY;
    for(int x=sx; x<maxX; x++){
        for(int y=sy; y<maxY; y++){
//    for(int y=sy; y<maxY; y++){
//        for(int x=sx; y<maxX; x++){
            Vector3 sample = Vector3(0, 0, 0);
            for(int i=0; i<spp; i++){
                ray = cam.getRay(
                        (static_cast<float>(x) + drand48()) / width * 2 - 1,
                        (static_cast<float>(y) + drand48()) / height * 2 - 1);
                Vector3 aa_sample = trace(ray, maxBounce);
                sample += aa_sample;
            }
            out[x + (height - y - 1) * width] =
                    255 << 24 |
                    (static_cast<int>(sqrtf(sample.z / spp) * 255.0f) << 16) |
                    (static_cast<int>(sqrtf(sample.y / spp) * 255.0f) << 8) |
                    (static_cast<int>(sqrtf(sample.x / spp) * 255.0f) << 0);
        }
    }
}

// Method for threads
void World::renderChunks(std::vector<int> ids, int *out, Camera &cam) {
    for(auto& id : ids){
        renderChunk(id, out, cam);
    }
}

// Renders out the entire scene
void World::render(int* out, int threads) {
    auto cam = Camera(new Vector3(0, 0, 20), new Vector3(0, 0, -1), 30, aspect);
    const auto processor_count = std::thread::hardware_concurrency();
    if(processor_count * 2 - 2 < threads){
        std::cout << "[WARN] Specified more threads than machine has forcing down to " << processor_count * 2 - 2 << " threads." << std::endl;
        threads = processor_count * 2 - 2;
    }
    std::vector<std::vector<int>> chunksids;
    chunksids.reserve(threads);
    for(int i=0; i<chunkCountX * chunkCountY; i++){
        int threadID = i % threads;
        chunksids[threadID].emplace_back(i);
    }
    std::vector<std::thread> renderThreads;
    for(int i=0; i<threads; i++){
        renderThreads.emplace_back(&World::renderChunks, this, chunksids[i], std::ref(out), std::ref(cam));
    }
    for(int i=0; i<threads; i++){
        renderThreads[i].join();
    }
//    for(int i=0; i<chunkCountX * chunkCountY; i++){
//        int currentThreadID = i % threads;
//        renderThreads[currentThreadID]
//    }
}
