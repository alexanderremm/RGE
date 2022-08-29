#include <asset_manager.hpp>

// Third-party includes
#include <SFML/Graphics/Texture.hpp>

namespace RGE
{
    
    // PImpl implmentation the same as SFML Texture class
    class Texture : public sf::Texture {};

    AssetManager::AssetManager()
    {

    }

    AssetManager::~AssetManager()
    {
        // Clear all current textures
        m_textures.clear();
    }

    bool AssetManager::LoadTexture(std::string name, std::string filepath)
    {
        Texture texture;

        if (!texture.loadFromFile(filepath))
        {
            return false;
        }

        m_textures[name] = std::make_unique<Texture>(texture);
        return true;
    }

};