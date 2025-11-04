#include "raylib.h"
#include <iostream>
#include <map>
#include <string>
#include "core/Utils.h"
#include "game/Card.h"
class ResourceManager
{
private:
    std::map<std::string, Texture2D> m_textures;

public:
    ResourceManager();
    ~ResourceManager();
    void LoadTexture(const std::string &name, const std::string &filePath);
    Texture2D GetTexture(const std::string &name);
    Texture2D GetTexture(const Card &card);
};
