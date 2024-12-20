#ifndef BLOCK_TEMPLATED_H
#define BLOCK_TEMPLATED_H

#include "block.h"

//using CRTP

template <typename T>
class BlockTemplated : public Block {
    public:
        inline BlockId GetId() const override {
            return T::id_;
        };

        inline BlockOpacity GetOpacity() const override {
            return T::opacity_;
        };

    private:
        //FRONT, LEFT, BACK, RIGHT, TOP, BOTTOM
        const int* GetTextureLayers() const override {
            return T::texture_layers_;
        };
};

#endif // BLOCK_TEMPLATED_H
