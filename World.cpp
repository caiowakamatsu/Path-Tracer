//
// Created by legend on 3/18/20.
//
#include "iostream"
#include "World.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <random>

World::World(int w, int h, Texture& t, int m, int s) : texture(t) {
    width = w;
    height = h;
    maxBounce = m;
    spp = s;
    sppRt = static_cast<int>(sqrt(spp));
    aspect = (float) width / height;

    // Split the world into different chunks to be rendered
    chunkCountX = 32; // Ill add a way to do these dynamically or something later
    chunkCountY = 32;
    chunkSizeX = width / chunkCountX;
    chunkSizeY = height / chunkCountY;

    float initOffset = sqrtf(spp);
    sampleStart = 1.0f / (initOffset * 2);
    sampleOffset = 1.0f / initOffset;
}

World::~World() = default;

void World::addShape(Shape * shapePtr) {
    bvh.shapes.push_back(shapePtr);
}

// This returns a single ray trace
bool World::colour(Ray& ray, HitRecord& out) {
    HitRecord best(nullptr, ray);

    // Main intersection loop
    std::vector<Shape*> bvhShapes;
    bvh.transverse(ray, bvhShapes);

    /*
    if (!bvhShapes.empty()) {
        out.albedo = Vector3(0.0, 0, 0);
        out.reflectiveness = 0;
        out.emission = Vector3(1, 0, 0);
        return false;
    } else {
        out.albedo = Vector3(0.0, 0, 0);
        out.reflectiveness = 0;
        out.emission = Vector3(1, 0, 1);
        return true;
    }*/
    for (auto shape : bvhShapes) {
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
        Vector3 uv = Vector3(best.u, best.v, 0);
        best.outRay = ray;
        best.shape->getMaterial()->getColour(best.emission, best.albedo, uv, best.reflectiveness, best);
        out = best;
        return true;
    }
}

void World::buildBvh() {
    // blobsweat
    Vector3 min, max;
    for(auto shape : bvh.shapes){
        AABB shapeBoundingBox = shape->getBoundingBox();
        min.x = fmin(shapeBoundingBox.min.x, min.x);
        min.y = fmin(shapeBoundingBox.min.y, min.y);
        min.z = fmin(shapeBoundingBox.min.z, min.z);
        max.x = fmax(shapeBoundingBox.max.x, max.x);
        max.y = fmax(shapeBoundingBox.max.y, max.y);
        max.z = fmax(shapeBoundingBox.max.z, max.z);
    }
    bvh.self = AABB(min, max);
    bvh.split(50);
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);
    for(int x=sx; x<maxX; x++){
        for(int y=sy; y<maxY; y++){
            Vector3 sample = Vector3(0, 0, 0);
            for(int j=0; j<sppRt; j++){
                for(int k=0;k<sppRt; k++){
                    ray = cam.getRay(
                            (static_cast<float>(x) + dist(gen)) / width * 2 - 1,
                            (static_cast<float>(y) + dist(gen))/ height * 2 - 1);
                    Vector3 aa_sample = trace(ray, maxBounce);
                    sample += aa_sample;
                }
            }
            out[x + y * width] =
                    255 << 24 |
                    (static_cast<int>(sqrtf(sample.z / spp) * 255.0f) << 16) |
                    (static_cast<int>(sqrtf(sample.y / spp) * 255.0f) << 8) |
                    (static_cast<int>(sqrtf(sample.x / spp) * 255.0f) << 0);
        }
    }
}

// Method for threads
void World::renderChunks(std::vector<int> ids, int *out, Camera &cam) {
    while(!renderStack.empty()) {
        renderChunk(renderStack.pop(), out, cam);
    }
}

// Renders out the entire scene
void World::render(int* out, int threads) {
    auto cam = Camera(Vector3(50, 70, 50), Vector3(0, 0, 0), 30, aspect);
    const auto processor_count = std::thread::hardware_concurrency() - 2;
    if(processor_count < threads){
        std::cout << "[WARN] Specified more threads than machine has forcing down to " << processor_count << " threads." << std::endl;
        threads = processor_count;
    }
    std::vector<std::vector<int>> chunksids;
    chunksids.reserve(threads);
    int x = chunkCountX / 2;
    int y = chunkCountY / 2;
    bool left = false;
    bool down = false;
    int leftToTravel = 1;
    const int totalChunks = chunkCountX * chunkCountY;
#ifdef SPIRAL
    renderStack.push(x + y * chunkCountX);
    while(renderStack.size() <= totalChunks){
        for(int i=0; i<leftToTravel; i++){
            y += down ? -1 : 1;
            renderStack.push(x + y * chunkCountX);
        }
        down = !down;
        for(int i=0; i<leftToTravel; i++){
            x += left ? -1 : 1;
            renderStack.push(x + y * chunkCountX);
        }
        left = !left;
        leftToTravel++;
    }
#else
    for(int i=0; i<totalChunks; i++){
        renderStack.push(i);
    }
#endif
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
