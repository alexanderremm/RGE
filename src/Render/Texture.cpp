#define RGE_EXPORTS

#include "RGE/Render/Texture.hpp"

namespace RGE
{
	namespace Render
	{
		Texture2D::Texture2D()
			: width(0),
			height(0),
			internalFormat(GL_RGB),
			imageFormat(GL_RGB),
			wrapS(GL_REPEAT),
			wrapT(GL_REPEAT),
			filterMin(GL_LINEAR),
			filterMax(GL_LINEAR)
		{
			glGenTextures(1, &this->ID);
		}

		void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
		{
			this->width = width;
			this->height = height;
			// Create texture
			glBindTexture(GL_TEXTURE_2D, this->ID);
			glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
			// Set texture wrap and filter mode
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
			// Unbind texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture2D::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, this->ID);
		}

	} // Render

} // RGE
