//
// Created by Tonz on 07.10.2023.
//

#pragma once

#include <cstdint>

/*class VertexType{
public:
    enum class VertexTypeEnum : uint8_t{
        EMPTY = 0,
        POS = 1,
        NORMAL = 2,
        COLOR = 3,
        UV = 4
    };

    VertexType() = delete;
    explicit VertexType(const VertexTypeEnum& value) : value(value){}

    [[nodiscard]] int getOffset() const{
        switch (this->value) {
            case VertexTypeEnum::POS:
                return 0;
            case VertexTypeEnum::NORMAL:
                return 3;
            case VertexTypeEnum::COLOR:
                return 6;
            case VertexTypeEnum::UV:
                return 8;
        }
    }

    const VertexTypeEnum& getValue(){
        return this->value;
    }

private:
    const VertexTypeEnum& value;
};

inline VertexType::VertexTypeEnum operator | (VertexType::VertexTypeEnum a, VertexType::VertexTypeEnum b){
    return static_cast<VertexType::VertexTypeEnum>(static_cast<int>(a) | static_cast<int>(b));
}

inline VertexType::VertexTypeEnum operator & (VertexType::VertexTypeEnum a, VertexType::VertexTypeEnum b){
    return static_cast<VertexType::VertexTypeEnum>(static_cast<int>(a) & static_cast<int>(b));
}*/


enum class VertexType : uint8_t {
    EMPTY = 100,
    POS = 0,
    NORMAL = 3,
    COLOR = 6,
    UV = 9
};

class VertexElement{
public:
    virtual int getElementOffset() const = 0;
    virtual int getElementCount() const = 0;
};

class PosElement : public VertexElement{
public:
    virtual int getElementOffset() const override {return 0;}
    virtual int getElementCount() const override {return 3;}
};

class NorElement : public PosElement{
public:
    virtual int getElementOffset() const override {return 3;}
};


class ColElement : public PosElement{
public:
    virtual int getElementOffset() const override {return 6;}
};

class UvElement : public VertexElement{
public:
    virtual int getElementOffset() const override {return 9;}
    virtual int getElementCount() const override {return 2;}
};

class VertexSpecifier{
public:
    explicit VertexSpecifier(std::initializer_list<VertexType> typeList) : types(typeList){}

    int operator[](const uint32_t& index){
        int offset{0};
        for (int i = 0; i < index; i++){
            offset += static_cast<uint32_t>(this->types[i]);
        }
        return offset;
    }

    const std::vector<VertexType>& getTypes() const{
        return this->types;
    }

private:
    std::vector<VertexType> types{};
};