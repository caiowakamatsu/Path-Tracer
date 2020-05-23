//
// Created by legend on 5/14/20.
//

#include <algorithm>
#include <assert.h>
#include <iostream>
#include "BVH.h"

BVH::BVH(AABB aabb) {
    self = aabb;
}

void BVH::split(int maxPerNode) {
    // Find axis we want to split on
    int axis = 0;
    float splitCoord;
    {
        float currentBestDelta = 0.;
        for (int i = 0; i < 3; i++) {
            if (abs(self.max[i] - self.min[i]) > currentBestDelta)
                axis = i;
        }
    }
    splitCoord = (self.max[axis] + self.min[axis]) * .5f;

    // "left" bvh
    children[0] = new BVH(AABB(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max()));

    if(children[0] == nullptr)
        std::cerr << "Children 0 is a nullptr";

    // "right" bvh
    children[1] = new BVH(AABB(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max()));

    if(children[1] == nullptr)
        std::cerr << "Children 1 is a nullptr";

    for(auto p : shapes){
        AABB shapeAABB = p->getBoundingBox();
        if(shapeAABB.getCenter()[axis] < splitCoord){
            children[0]->self.extend(shapeAABB);
            assert(p != nullptr);
            children[0]->shapes.push_back(p);
        } else {
            children[1]->self.extend(shapeAABB);
            assert(p != nullptr);
            children[1]->shapes.push_back(p);
        }
    }

    if(children[0]->shapes.empty() || children[1]->shapes.empty()){
        std::sort(shapes.begin(), shapes.end(), [=](Shape* a, Shape* b){
           return a->getBoundingBox().getCenter()[axis] < b->getBoundingBox().getCenter()[axis];
        });
        children[0]->self = AABB(
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max()
                );
        children[1]->self = AABB(
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max()
                );
        size_t halfSize = shapes.size() / 2;
        for(size_t i=0; i<halfSize; ++i){
            AABB a = shapes[i]->getBoundingBox();
            children[0]->self.extend(a);
            children[0]->shapes.push_back(shapes[i]);
        }
        for (size_t i=halfSize; i < shapes.size(); ++i){
            AABB a = shapes[i]->getBoundingBox();
            children[1]->self.extend(a);
            children[1]->shapes.push_back(shapes[i]);
        }
    }


    shapes.clear();
    for(int i=0; i<2; i++){
        if(children[i]->shapes.size() > maxPerNode){
            children[i]->split(maxPerNode);
        }
    }
}

bool BVH::isEnd() {
    return children[0] == nullptr && children[1] == nullptr;
}

void BVH::traverse(Ray &ray, HitRecord& best) {
    if(!self.intersect(ray)){
        return;
    }
    if(isEnd()){
        for(auto& shape : shapes){
            HitRecord rec(shape, ray);
            shape->intersect(ray, rec);
            if ((rec.hit && !best.hit) || ((rec.distance < best.distance) && rec.distance != -1.0f)) best = rec;
        }
    } else {
        children[0]->traverse(ray, best);
        children[1]->traverse(ray, best);
    }
}

