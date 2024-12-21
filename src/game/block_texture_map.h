#include "block_enums.h"
#include <map>
#include <string>

using namespace BlockEnum;

static const std::map<BlockTexture, std::string> block_texture_map = {
    {BlockTexture::BEDROCK, TEXTURES_PATH "/bedrock.png"},
    {BlockTexture::GRASS_SIDE, TEXTURES_PATH "/grass_side.png"},
    {BlockTexture::GRASS_TOP, TEXTURES_PATH "/grass_top.png"},
    {BlockTexture::DIRT, TEXTURES_PATH "/dirt.png"},
    {BlockTexture::STONE, TEXTURES_PATH "/stone.png"},
    {BlockTexture::OAK_SIDE, TEXTURES_PATH "/oak_side.png"},
    {BlockTexture::OAK_TOP, TEXTURES_PATH "/oak_top.png"},
    {BlockTexture::OAK_LEAVE, TEXTURES_PATH "/oak_leave.png"},
    {BlockTexture::SAND, TEXTURES_PATH "/sand.png"},
    {BlockTexture::WATER, TEXTURES_PATH "/water.png"},
    {BlockTexture::GLOWSTONE, TEXTURES_PATH "/glowstone.png"},
};
