#define RGE_EXPORTS

#include "RGE/Render/TextRenderer.hpp"

namespace RGE
{
	namespace Render
	{
		TextRenderer::TextRenderer(unsigned int width, unsigned int height)
		{
			// Initialize and load the FreeType lib
			if (FT_Init_FreeType(&m_ft)) // all functions return a value different than 0 whenever an error occurred
			{
				RGE::Logger::LOGC(RGE::LOG_ERROR, "FreeType: Could not init the library");
			}

			// Member variable initialization
			this->m_VAO = -1;
			this->m_VBO = -1;

			m_vertexShader = 
				R"glsl(
				#version 330 core
				layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
				out vec2 TexCoords;

				uniform mat4 projection;

				void main()
				{
					gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
					TexCoords = vertex.zw;
				}
				)glsl";

			this->m_fragmentShader = 
				R"glsl(
				#version 330 core
				in vec2 TexCoords;
				out vec4 color;

				uniform sampler2D text;
				uniform vec3 textColor;

				void main()
				{    
					vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
					color = vec4(textColor, 1.0) * sampled;
				}
				)glsl";

			// Load and configure shader
			this->textShader = Shader();
			this->textShader.Compile(m_vertexShader, m_fragmentShader);
			this->textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);
			this->textShader.SetInteger("text", 0);

			// Configure VAO/VBO
			glGenVertexArrays(1, &this->m_VAO);
			glGenBuffers(1, &this->m_VBO);
			glBindVertexArray(this->m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		TextRenderer::~TextRenderer()
		{
			// Free reference to FreeType 2 handles
			FT_Done_Face(m_face);
			FT_Done_FreeType(m_ft);
		}

		void TextRenderer::LoadFromFile(std::string font, unsigned int fontSize)
		{
			// Clear the previously loaded Characters
			this->characters.clear();

			// Load font as a face
			if (FT_New_Face(m_ft, font.c_str(), 0, &m_face))
			{
				RGE::Logger::LOGC(RGE::LOG_ERROR, "FreeType: Failed to load font");
			}

			// Set size to load glyph
			FT_Set_Pixel_Sizes(m_face, 0, fontSize);
			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// For the first 128 ASCII characters, pre-load/compile their characters and store them
			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph
				if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
				{
					RGE::Logger::LOGC(RGE::LOG_ERROR, "FreeType: Failed to load glyph");
					continue;
				}
				// Generate the texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_face->glyph->bitmap.width,
					m_face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Store the character for later use
				Character character =
				{
					texture,
					glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
					glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
					m_face->glyph->advance.x
				};
				characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void TextRenderer::LoadFromMemory(unsigned char* fontBuffer, unsigned int fontBufferLen, unsigned int fontSize)
		{
			// Clear the previously loaded Characters
			this->characters.clear();

			// Load font as a face
			if (FT_New_Memory_Face(m_ft, fontBuffer, fontBufferLen, 0, &m_face))
			{
				RGE::Logger::LOGC(RGE::LOG_ERROR, "FreeType: Failed to load font");
			}

			// Set size to load glyph
			FT_Set_Pixel_Sizes(m_face, 0, fontSize);
			// Disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			// For the first 128 ASCII characters, pre-load/compile their characters and store them
			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph
				if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
				{
					RGE::Logger::LOGC(RGE::LOG_ERROR, "FreeType: Failed to load glyph");
					continue;
				}
				// Generate the texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_face->glyph->bitmap.width,
					m_face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// Store the character for later use
				Character character =
				{
					texture,
					glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
					glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
					m_face->glyph->advance.x
				};
				characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void TextRenderer::RenderText(std::string text, float x, float y, float scale, Math::Vector3<float> color)
		{
			// Activate corresponding render state
			this->textShader.Use();
			this->textShader.SetVector3f("textColor", color);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(this->m_VAO);

			// Iterate through all the characters
			std::string::const_iterator c;
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = characters[*c];

				float xpos = x + ch.bearing.x * scale;
				float ypos = y - ch.bearing.y * scale;

				float w = ch.size.x * scale;
				float h = ch.size.y * scale;
				// Update VBO for each character
				float vertices[6][4] =
				{
					{ xpos,     ypos + h,   0.0f, 1.0f },
					{ xpos + w, ypos,       1.0f, 0.0f },
					{ xpos,     ypos,       0.0f, 0.0f },

					{ xpos,     ypos + h,   0.0f, 1.0f },
					{ xpos + w, ypos + h,   1.0f, 1.0f },
					{ xpos + w, ypos,       1.0f, 0.0f }
				};
				
				// Render glyph texture over quad
				glBindTexture(GL_TEXTURE_2D, ch.textureID);
				// Update content of VBO memory
				glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// Render the quad
				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Advance to next glyph
				x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
			}

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	} // Render

} // RGE
