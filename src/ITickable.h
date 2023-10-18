//
// Created by Tonz on 17.10.2023.
//

#pragma once

#include <functional>
#include <utility>

class ITickable {
public:
    virtual void tick(){
        tickFunction();
    }

    void setTickFunction(std::function<void()> newFunc){
        this->tickFunction = std::move(newFunc);
    }

private:
    std::function<void()> tickFunction;
};