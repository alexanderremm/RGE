#pragma once

#include <map>

#include <glad/glad.h>

// FreeType 2
#include <ft2build.h>
#include FT_FREETYPE_H

#include "RGE/Render/Shader.hpp"
#include "RGE/Render/Texture.hpp"
#include "RGE/Math/Vector.hpp"

namespace RGE
{
	namespace Render
	{
		struct Character
		{
			unsigned int textureID;     // ID to handle the glyph texture
			glm::ivec2 size;			// size of the glyph
			glm::ivec2 bearing;			// offset from the baseline to left/top of glpyh
			unsigned int advance;       // horizontal offset to advance to next glyph
		};

		class RGE_EXPORT TextRenderer
		{
		public:
			// Holds a list of pre-compiled characters
			std::map<char, Character> characters;
			// Shader used for text rendering
			Shader textShader;
			// Constructor
			TextRenderer(unsigned int width, unsigned int height);
			// Destructor
			~TextRenderer();
			// Pre-compiles a list of characters from the given font file
			void LoadFromFile(std::string font, unsigned int fontSize);
			// Pre-compiles a list of characters from the given font buffer
			void LoadFromMemory(unsigned char* fontBuffer, unsigned int fontBufferLen, unsigned int fontSize);
			// Renders a string of text using the pre-compiled list of characters
			void RenderText(std::string text, float x, float y, float scale, Math::Vector3<float> color = Math::Vector3<float>(1.0f, 1.0f, 1.0f));
		private:
			// Handle to Freetype library
			FT_Library m_ft;
			// Font face
			FT_Face m_face;

			// Render state
			unsigned int m_VAO, m_VBO;

			// Shaders
			const char* m_vertexShader;
			const char* m_fragmentShader;
		};

	} // Render

} // RGE