#include "block_templated.h"

template <typename T>
std::map<BlockFace, std::vector<int>>&
BlockTemplated<T>::GenerateTextureLayersVaoMap()
{
    //initialize texture layers map (using lambda so it only runs once)
    static std::map<BlockFace, std::vector<int>> texture_layers_map = []() {
        std::map<BlockFace, std::vector<int>> temp_map;
        for (auto& [face, texture] : T::texture_layers_) {
            temp_map[face] = {texture, texture, texture, texture, texture, texture};
        }
        return temp_map;
    }();

    return texture_layers_map;
}
