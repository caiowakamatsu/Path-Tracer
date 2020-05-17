//
// Created by legend on 5/14/20.
//

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

    Vector3 offset = Vector3();
    offset[axis] = (self.max[axis] + self.min[axis]) * .5f;
    splitCoord = self.min[axis] + offset[axis];

    // "left" bvh
    children[0] = new BVH(AABB(
            self.min[0],
            self.min[1],
            self.min[2],
            self.min[0] + offset[0],
            self.min[1] + offset[1],
            self.min[2] + offset[2]));

    // "right" bvh
    children[1] = new BVH(AABB(
            self.max[0],
            self.max[1],
            self.max[2],
            self.max[0] - offset[0],
            self.max[1] - offset[1],
            self.max[2] - offset[2]));

    for(auto p : shapes){
        AABB shapeAABB = p->getBoundingBox();
        if(shapeAABB.getCenter()[axis] < splitCoord){
            children[0]->self.extend(shapeAABB);
            children[0]->shapes.push_back(p);
        } else {
            children[1]->self.extend(shapeAABB);
            children[1]->shapes.push_back(p);
        }
    }

    for(int i=0; i<2; i++){
        if(children[i]->shapes.size() > maxPerNode){
//            children[i]->split(maxPerNode);
        }
    }
}

void BVH::transverse(Ray &ray, std::vector<Shape *> &shapesPassBack) {
    std::vector<BVH*> intersected;
    for(int i=0; i<2; i++){
        if(children[i]->self.intersect(ray))
            intersected.emplace_back(children[i]);
    }
    if(self.intersect(ray)){
        shapesPassBack = shapes;
    } else {
        std::vector<Shape*> transversed;
        for(int i=0; i<intersected.size(); i++){
            std::vector<Shape*> current;
            intersected[i]->transverse(ray, current);
            transversed.reserve(current.size());
            for(int j=0; j<current.size(); j++){
                transversed[j + transversed.size()] = current[j];
            }
        }
        shapesPassBack = transversed;
    }
}

