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

        inline const std::map<BlockFace, std::vector<int>>& GetTextureLayersVaoMap() const override { //FRONT, LEFT, BACK, RIGHT, TOP, BOTTOM
            return GenerateTextureLayersVaoMap();
        };

    private:
        static std::map<BlockFace, std::vector<int>>& GenerateTextureLayersVaoMap();
};

#endif // BLOCK_TEMPLATED_H
