#pragma once

#include "RGE/rge_exports.h"

#include <glad/glad.h>

namespace RGE
{
	namespace Render
	{
		class RGE_EXPORT Texture2D
		{
		public:
			// Holds the ID of the texture object
			unsigned int ID;
			// Texture image dimensions
			unsigned int width, height;
			// Texture format
			unsigned int internalFormat;
			unsigned int imageFormat;

			// Texture configuration
			unsigned int wrapS; // wrapping mode on S axis
			unsigned int wrapT; // wrapping mode on T axis
			unsigned int filterMin; // filtering mode if texture pixels < screen pixels
			unsigned int filterMax; // filtering mode if texture pixels > screen pixels

			// Constructor (set default texture modes)
			Texture2D();

			// Generates texture from image data
			void Generate(unsigned int width, unsigned int height, unsigned char* data);

			// Binds the texture as the current active GL_TEXTURE_2D texture object
			void Bind() const;
		};

	} // Render

} // RGE
