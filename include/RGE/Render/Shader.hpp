#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RGE/Core/Logging.hpp"
#include "RGE/Math/Vector.hpp"
#include "RGE/Math/Matrix.hpp"

namespace RGE
{
	namespace Render
	{
		class RGE_EXPORT Shader
		{
		public:
			// State
			unsigned int ID;
			// Constructor
			Shader();
			// Sets the current shader as active
			Shader& Use();
			// Compiles the shader from the given source code
			void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
			// Utility functions
			void SetFloat(const char* name, float value, bool useShader = false);
			void SetInteger(const char* name, int value, bool useShader = false);
			void SetVector2f(const char* name, float x, float y, bool useShader = false);
			void SetVector2f(const char* name, const Math::Vector2<float>& value, bool useShader = false);
			void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
			void SetVector3f(const char* name, const Math::Vector3<float>& value, bool useShader = false);
			void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
			void SetVector4f(const char* name, const Math::Vector4<float>& value, bool useShader = false);
			void SetMatrix4(const char* name, const Math::Matrix4& matrix, bool useShader = false);

		private:
			void CheckCompileErrors(unsigned int object, std::string type);
		};

	} // Render

} // RGE
