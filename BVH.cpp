//
// Created by legend on 5/14/20.
//

#include "BVH.h"

BVH::BVH(AABB aabb) {
    self = aabb;
}

void BVH::split(int maxPerNode){
    BVH* currentBest[2];
    float currentSurfaceArea = -1.0f;
    // Go through every axis
    for(int i=0; i<3; i++){
        float axisDelta = (self.max[i] - self.min[i]);
        float axisSplitSize = axisDelta / 4.0f;
        for(float a=0; a<axisDelta; a+=axisSplitSize){
            // Create the AABB's
            AABB current[2];
            BVH* currentBVH[2];
            Vector3 offset;
            offset[i] = a;
            current[0] = AABB(self.min[0], self.min[1], self.min[2], self.min[0] + offset[0], self.min[1] + offset[1], self.min[2] + offset[2]);
            current[1] = AABB(self.min[0] + offset[0], self.min[1] + offset[1], self.min[2] + offset[2], self.max[0], self.max[1], self.max[2]);
            // Resize both AABB's
            for(int j=0; j<2; j++) {
                AABB aabb = current[j];
                Vector3 min, max;
                BVH* bvh = new BVH(aabb);
                for (long y=shapes.size() - 1; y>=0; y--) {
                    AABB shapeBoundingBox = shapes[y]->getBoundingBox();
                    if (aabb.intersect(shapeBoundingBox)) {
                        bvh->shapes.emplace_back(shapes[y]);
                        min.x = fmin(shapeBoundingBox.min.x, min.x);
                        min.y = fmin(shapeBoundingBox.min.y, min.y);
                        min.z = fmin(shapeBoundingBox.min.z, min.z);
                        max.x = fmax(shapeBoundingBox.max.x, max.x);
                        max.y = fmax(shapeBoundingBox.max.y, max.y);
                        max.z = fmax(shapeBoundingBox.max.z, max.z);
                    }
                    aabb = AABB(min, max);
                    currentBVH[j] = new BVH(aabb);
                }
            }
            float areaRating = current[0].getAreaRating() + current[1].getAreaRating();
            if(areaRating < currentSurfaceArea || currentSurfaceArea < 0){
                currentSurfaceArea = areaRating;
                currentBest[0] = currentBVH[0];
                currentBest[1] = currentBVH[1];
            } else {
                delete currentBVH[0];
                delete currentBVH[1];
            }
        }
    }
    for(int i=0; i<2; i++){
        children[i] = currentBest[i];
        if(children[i]->shapes.size() > maxPerNode){
            for(int y=shapes.size()-1; y>=0; y--){
                auto shapeSelfPtr = shapes[y];
                for(auto& shapePtr : children[i]->shapes){
                    if(shapeSelfPtr == shapePtr){
                        shapes.erase(shapes.begin() + y);
                    }
                }
            }
            children[i]->split(maxPerNode);
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

