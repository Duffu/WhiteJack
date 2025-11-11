#pragma once
#include "raylib.h"
#include <iostream>
#include <map>
#include <string>
#include "core/Utils.h"
#include "game/Card.h"
// ResourceManager is a singleton class to avoid prop-drilling
class ResourceManager
{
private:
    std::map<std::string, Texture2D> m_textures;
    Sound m_hurtSound;
    Music m_backgroundMusic;
    ResourceManager();
    ~ResourceManager();

public:
    ResourceManager(const ResourceManager &) = delete;
    void operator=(const ResourceManager &) = delete;
    static ResourceManager &GetInstance()
    {
        static ResourceManager instance;
        return instance;
    }
    void LoadTexture(const std::string &name, const std::string &filePath);
    Texture2D GetTexture(const std::string &name);
    Texture2D GetTexture(const Card &card);
    Sound &GetHurtSound();
    Music &GetBackgroundMusic();
};
