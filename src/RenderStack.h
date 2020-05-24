//
// Created by legend on 4/21/20.
//

#pragma once

#include <queue>
#include <mutex>

class RenderStack {
private:
    std::mutex mut;
    std::queue<int> stack;
public:
    bool empty(){
        return stack.empty();
    }
    void push(int id){
        std::lock_guard lockGuard(mut);
        stack.push(id);
    }
    int pop(){
        std::lock_guard lockGuard(mut);
        int top = stack.front();
        stack.pop();
        return top;
    }
    int size(){
        std::lock_guard lockGuard(mut);
        return stack.size();
    }
};

