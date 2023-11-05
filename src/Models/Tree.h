//
// Created by Tonz on 26.10.2023.
//

#pragma once


#include "Model.h"

#include "tree_data.h"


class Tree : public Model {
public:
    Tree();

private:

    static inline std::vector<float> treeData{};

    static inline bool vectorFilled{false};

    static void fillVector();
};