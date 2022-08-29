#include <gtest/gtest.h>

#include <asset_manager.hpp>

TEST(AssetManagerTest, Initialization)
{
    // We should be able to create the AssetManager
    EXPECT_NO_FATAL_FAILURE(RGE::AssetManager assetManager);
}

TEST(AssetManagerTest, LoadFromTexture)
{
    // Create AssetManager
    RGE::AssetManager assetManager;

    // Attempt to load a file that exists
    bool success = assetManager.LoadTexture("ITCOTCK", "assets/itcotck1.jpg");
    EXPECT_TRUE(success);

    // Attempt to load a file that does not exist
    success = assetManager.LoadTexture("HotRats", "assets/HotRats.png");
    EXPECT_FALSE(success);
}

