//
// Created by Tonz on 28.10.2023.
//

#pragma once
#include "Model.h"
#include "bushes_data.h"
class Bush : public Model {
public:
    Bush();
private:
    static inline std::vector<float> bushData{};

    static inline bool vectorFilled{false};

    static void fillVector();
};


