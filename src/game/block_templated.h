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

template <typename T>
std::map<BlockFace, std::vector<int>>&
BlockTemplated<T>::GenerateTextureLayersVaoMap()
{
    //initialize texture layers map (using lambda so it only runs once)
    static std::map<BlockFace, std::vector<int>> texture_layers_map = []() {
        std::map<BlockFace, std::vector<int>> temp_map;
        for (auto& [face, texture] : T::texture_layers_) {
            int texture_layer = static_cast<int>(texture);
            temp_map[face] = {texture_layer, texture_layer, texture_layer, texture_layer, texture_layer, texture_layer};
        }
        return temp_map;
    }();

    return texture_layers_map;
}

#endif // BLOCK_TEMPLATED_H
