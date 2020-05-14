//
// Created by legend on 5/14/20.
//

#include "BVH.h"

BVH::BVH(AABB aabb) {
    self = aabb;
}

void BVH::split(){

}

void BVH::transverse(Ray &ray, std::vector<Shape *> &shapesPassBack) {
    std::vector<BVH*> intersected;
    for(int i=0; i<children.size(); i++){
        if(children[i]->self.intersect(ray))
            intersected.emplace_back(children[i]);
    }
    if(intersected.empty()){
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

