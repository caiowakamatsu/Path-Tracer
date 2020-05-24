#pragma once

#include <bvh/utilities.hpp>
#include "vector"
#include "Triangle.h"
#include "Vector3.h"
#include "Camera.h"
#include "ColourCache.h"
#include <vector>
#include "Texture.h"
#include "RenderStack.h"
#include <bvh/triangle.hpp>
#include <bvh/vector.hpp>
#include <bvh/bvh.hpp>
#include <bvh/sweep_sah_builder.hpp>
#include <bvh/single_ray_traverser.hpp>
#include <bvh/intersectors.hpp>
#include "ModelLoader.h"
#include "Triangle.h"
#include "NormalMat.h"

using bvhVec = bvh::Vector3<float>;
using bvhRay = bvh::Ray<float>;

class World {
private:
    int width, height, maxBounce, spp, sppRt, chunkSizeX, chunkSizeY, chunkCountX, chunkCountY;
    float aspect, sampleStart, sampleOffset;
    Vector3 cameraLocation, lookatLocation;
    Texture& texture;
    std::vector<Triangle*> triangles;
    std::vector<bvh::Triangle<float>> bvh_triangles;
    bool colour(Ray& ray, HitRecord& out);
    void renderChunk(int chunkID, int* out, Camera& cam);
    void renderChunks(int* out, Camera& cam);
    RenderStack renderStack;
    bvh::Bvh<float> bvh;
public:
    World(int, int, Texture&, int = 4, int = 1);
    ~World();
    void setCameraLocation(Vector3 location);
    void setLookAt(Vector3 location);
    void addTriangle(Triangle* triangle);
    void render(int*, int threads);
    void buildBvh();
    void loadModel(const char* path, const std::vector<Vector3>& offsets = {}, Material* material = nullptr);
    Vector3 trace(Ray ray, int);
};
