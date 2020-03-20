//
// Created by legend on 3/18/20.
//

#include "World.h"

World::World() {

}

World::~World(){
    for(auto ptr : shapes){
        delete(ptr);
    }
}

void World::addShape(Shape * shapePtr) {
    shapes.push_back(shapePtr);
}

Vector3 World::trace(Ray * ray) {

    return Vector3(1.0f, 0.0f, 0.0f);
}
