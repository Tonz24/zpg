//
// Created by Tonz on 17.10.2023.
//

#pragma once


#include "Model.h"

class Tree : public Model {
public:
    Tree();

private:
    static inline const std::vector<float> tree = {
            0, 0, 0,    0, 1, 0,
            0, 0, 100,    0, 1, 0,
            100, 0, 0,    0, 1, 0,

            0, 0, 100,    0, 1, 0,
            100, 0, 100,    0, 1, 0,
            100, 0, 0,    0, 1, 0
    };
};