#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

// Standard includes
#include <map>
#include <memory>
#include <string>

namespace RGE
{

    // PImpl class declaration
    class Texture;

    /**
     * @brief The AssetManager is used to manage game assets. 
     * 
     * It currently supports the following asset types:
     *  - Images
     * 
     */
    class AssetManager
    {
    public:
        /**
         * @brief Construct a new Asset Manager object.
         * 
         */
        AssetManager();

        /**
         * @brief Destroy the Asset Manager object.
         * 
         */
        virtual ~AssetManager();

        // Non-copyable
        AssetManager(const AssetManager& other) = delete;
        AssetManager& operator=(const AssetManager& other) = delete;

        // Movable
        AssetManager(AssetManager&& other) = default;
        AssetManager& operator=(AssetManager&& other) = default;

        /**
         * @brief Load a new texture into the AssetManager.
         * 
         * This will load an image file from disk into the internal data map
         * manager. The following image types are supported:
         *  - bmp
         *  - png
         *  - tga
         *  - jpg
         *  - gif
         *  - psd
         *  - hdr 
         *  - pic
         * 
         * @param name     Name of the asset. This name will be used to
         *                 retrieve the texture from the data map.
         * @param filepath Path of where the texture is located on the
         *                 local disk.
         * @return true    if the texture was successfully loaded
         * @return false   if the texture was unsuccessfully loaded
         */
        bool LoadTexture(std::string name, std::string filepath);

    private:
        // Map to manage different textures
        std::map<std::string, std::unique_ptr<Texture>> m_textures;
    };
};

#endif