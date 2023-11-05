//
// Created by Tonz on 31.10.2023.
//

#pragma once


#include "Model.h"

class Quad : public Model {
public:
    Quad();
private:

    static inline const std::vector<float> quadData = {
            //pos       //normals   uv
            -1,0,-1,    0,1,0,      0,0,
            -1,0, 1,    0,1,0,      0,1,
             1,0, 1,    0,1,0,      1,1,

             1,0, 1,    0,1,0,      1,1,
             1,0,-1,    0,1,0,      1,0,
            -1,0,-1,    0,1,0,      0,0
    };
};


