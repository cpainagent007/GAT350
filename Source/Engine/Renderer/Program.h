#pragma once

#include "Program.h"
#include "Shader.h"
#include "../Resources/Resource.h"
#include "Core/Logger.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <map>

class Shader;

namespace neu {
	
	class Program : public Resource
	{
	public:
		Program();
		~Program();

		bool Load(const std::string& filename);
		void AttachShader(const res_t<Shader>& shader);

		bool Link();
		void Use();

		// uniforms
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, unsigned int value);
		void SetUniform(const std::string& name, bool value);

		void SetUniform(const std::string& name, const neu::vec2& value);
		void SetUniform(const std::string& name, const neu::vec3& value);

		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

	private:
		GLint GetUniformLocation(const std::string& name);

	public:
		GLuint m_program = 0;
		std::map<std::string, GLint> m_uniformLocations;
	};
}
