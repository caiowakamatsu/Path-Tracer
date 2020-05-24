//
// Created by legend on 3/18/20.
//
#include "iostream"
#include "World.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <random>
#include "Vertex.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader.h"

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

void World::addTriangle(Triangle *triangle) {
    Vertex* vertices = triangle->vertices;
    triangles.push_back(triangle);
    bvh_triangles.emplace_back(
            bvhVec(vertices[0].pos[0], vertices[0].pos[1], vertices[0].pos[2]),
            bvhVec(vertices[1].pos[0], vertices[1].pos[1], vertices[1].pos[2]),
            bvhVec(vertices[2].pos[0], vertices[2].pos[1], vertices[2].pos[2]));
}

// This returns a single ray trace
bool World::colour(Ray& ray, HitRecord& out) {
    HitRecord best(nullptr, ray);

    // Need to do bvh traversal
    bvhRay bvhray(
            bvhVec(ray.origin[0], ray.origin[1], ray.origin[2]),
            bvhVec(ray.direction[0], ray.direction[1], ray.direction[2]),
            0.001);

    bvh::ClosestIntersector<false, bvh::Bvh<float>, bvh::Triangle<float>> intersector(bvh, bvh_triangles.data());
    bvh::SingleRayTraverser<bvh::Bvh<float>> traverser(bvh);

    auto hit = traverser.traverse(bvhray, intersector);

    if (!hit) { // This runs if there was no intersection, and it hit the skyyyyyy
        Vector3 d = Vector3() - ray.direction;
        float u = 0.5f + atan2f(d.z, d.x) / (2 * M_PI);
        float v = 0.5f - asinf(d.y) / M_PI;
        best.emission = texture.getUV(u, v);
        best.albedo = Vector3(0, 0, 0);
        best.reflectiveness = 0;
        out = best;
        return false;
    } else { // Compute colour and intensity at intersection point and new ray
        // Fill in hit record information because we're using a bvh library to do stuff yeet
        best.triangle = triangles[hit->primitive_index];
        best.intersectionPoint = ray.getPoint(hit->distance());
        best.distance = hit->distance();
        best.normal = best.triangle->getNormal(best.intersectionPoint);
        Vector3 uv = best.triangle->getUv(Vector3(hit->intersection.u, hit->intersection.v, 0));

        best.triangle->getMaterial()->transformRay(ray, best);
        best.outRay = ray;
        best.triangle->getMaterial()->getColour(best.emission, best.albedo, uv, best.reflectiveness, best);
        out = static_cast<HitRecord &&>(best);
        return true;
    }
}

void World::buildBvh() {
    bvh::SweepSahBuilder<bvh::Bvh<float>> builder(bvh);
    auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers(bvh_triangles.data(), bvh_triangles.size());
    auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), bvh_triangles.size());
    builder.build(global_bbox, bboxes.get(), centers.get(), bvh_triangles.size());
}

void World::loadObj(const char *path, Material* meshMat, std::vector<Vector3> translations) {
    std::string inputfile = path;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty())
        std::cout << warn << std::endl;


    if (!err.empty())
        std::cerr << err << std::endl;

    if (!ret)
        exit(1);

    if(translations.empty())
        translations.emplace_back(Vector3(0, 0, 0));

    for(size_t s=0; s<shapes.size(); s++){
        size_t indexOffset = 0;
        std::cout << "Model Loaded [" << path << "]" << " Triangles [" << shapes[s].mesh.num_face_vertices.size() << "]" << std::endl;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            Vertex vertices[3];
            for (size_t v = 0; v < fv; v++) {
                // access to Vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + v];
                vertices[v] = Vertex(
                        Vector3(attrib.vertices[3*idx.vertex_index+0],
                                attrib.vertices[3*idx.vertex_index+1],
                                attrib.vertices[3*idx.vertex_index+2]),
                        attrib.texcoords[2*idx.texcoord_index+0],
                        attrib.texcoords[2*idx.texcoord_index+1]);
            }
            for(auto & translation : translations){
                Vertex translated[3] = {vertices[0], vertices[1], vertices[2]};
                translated[0].pos += translation;
                translated[1].pos += translation;
                translated[2].pos += translation;
                addTriangle(new Triangle(
                        translated[0],
                        translated[1],
                        translated[2],
                        meshMat));
            }

            indexOffset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
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
void World::renderChunks(int *out, Camera &cam) {
    while(!renderStack.empty()) {
        renderChunk(renderStack.pop(), out, cam);
    }
}

// Renders out the entire scene
void World::render(int* out, int threads) {
    auto cam = Camera(cameraLocation, lookatLocation, 30, aspect);
    const auto processor_count = std::thread::hardware_concurrency() - 2;
    if(processor_count < threads){
        std::cout << "[WARN] Specified more threads than machine has forcing down to " << processor_count << " threads." << std::endl;
        threads = processor_count;
    }
    std::vector<std::vector<int>> chunksids;
    chunksids.reserve(threads);

    const int totalChunks = chunkCountX * chunkCountY;
#ifdef SPIRAL
    int x = chunkCountX / 2;
    int y = chunkCountY / 2;
    bool left = false;
    bool down = false;
    int leftToTravel = 1;
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
    renderThreads.reserve(threads);
    for(int i=0; i<threads; i++){
        renderThreads.push_back(std::thread(&World::renderChunks, this, std::ref(out), std::ref(cam)));
    }
    for(int i=0; i<threads; i++){
        renderThreads[i].join();
    }
//    for(int i=0; i<chunkCountX * chunkCountY; i++){
//        int currentThreadID = i % threads;
//        renderThreads[currentThreadID]
//    }
}

void World::setCameraLocation(Vector3 location) {
    cameraLocation = location;
}
void World::setLookAt(Vector3 location) {
    cameraLocation = location;
}
