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

        void AddTextureLayers(std::vector<int>& vao, const BlockFace face) const override;
};

template<typename T>
void
BlockTemplated<T>::AddTextureLayers(std::vector<int>& vao, const BlockFace face) const
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

    std::vector<int>& new_texture_layers = texture_layers_map.at(face);
    for (int i = 0; i < new_texture_layers.size(); i++) {
        vao.push_back(new_texture_layers[i]);
    }
}

#endif // BLOCK_TEMPLATED_H
