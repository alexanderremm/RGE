#define RGE_EXPORTS

#include "RGE/Render/Shader.hpp"

namespace RGE
{
	namespace Render
	{
		Shader::Shader()
		{
			ID = -1;
		}

		Shader& Shader::Use()
		{
			glUseProgram(this->ID);
			return *this;
		}

		void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
		{
			unsigned int sVertex, sFragment, gShader;

			// Vertex Shader
			sVertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(sVertex, 1, &vertexSource, NULL);
			glCompileShader(sVertex);
			CheckCompileErrors(sVertex, "VERTEX");

			// Fragment Shader
			sFragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(sFragment, 1, &fragmentSource, NULL);
			glCompileShader(sFragment);
			CheckCompileErrors(sFragment, "FRAGMENT");

			// If Geometry Shader is provided, compile it as well
			if (geometrySource != nullptr)
			{
				gShader = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(gShader, 1, &geometrySource, NULL);
				glCompileShader(gShader);
				CheckCompileErrors(gShader, "GEOMETRY");
			}

			// Shader Program
			this->ID = glCreateProgram();
			glAttachShader(this->ID, sVertex);
			glAttachShader(this->ID, sFragment);
			if (geometrySource != nullptr)
			{
				glAttachShader(this->ID, gShader);
			}
			glLinkProgram(this->ID);
			CheckCompileErrors(this->ID, "PROGRAM");

			// Delete the shaders as they're linked into our program now and longer needed
			glDeleteShader(sVertex);
			glDeleteShader(sFragment);
			if (geometrySource != nullptr)
			{
				glDeleteShader(gShader);
			}
		}

		void Shader::SetFloat(const char* name, float value, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform1f(glGetUniformLocation(this->ID, name), value);
		}

		void Shader::SetInteger(const char* name, int value, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform1i(glGetUniformLocation(this->ID, name), value);
		}

		void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform2f(glGetUniformLocation(this->ID, name), x, y);
		}

		void Shader::SetVector2f(const char* name, const Math::Vector2<float>& value, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
		}

		void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
		}

		void Shader::SetVector3f(const char* name, const Math::Vector3<float>& value, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
		}

		void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
		}

		void Shader::SetVector4f(const char* name, const Math::Vector4<float>& value, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
		}

		void Shader::SetMatrix4(const char* name, const Math::Matrix4& matrix, bool useShader)
		{
			if (useShader)
			{
				this->Use();
			}
			glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
		}

		void Shader::CheckCompileErrors(unsigned int object, std::string type)
		{
			int success;
			char infoLog[1024];
			if (type != "PROGRAM")
			{
				glGetShaderiv(object, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					glGetShaderInfoLog(object, 1024, NULL, infoLog);
					RGE_CORE_ERROR("Shader compile-time error! Type: {}", type);
					RGE_CORE_ERROR(infoLog, "\n -- --------------------------------------------------- -- ");
				}
			}
			else
			{
				glGetProgramiv(object, GL_LINK_STATUS, &success);
				if (!success)
				{
					glGetProgramInfoLog(object, 1024, NULL, infoLog);
					RGE_CORE_ERROR("Shader link-time error: Type: {}", type);
					RGE_CORE_ERROR(infoLog, "\n -- --------------------------------------------------- -- ");
				}
			}
		}

	} // Render

} // RGE
