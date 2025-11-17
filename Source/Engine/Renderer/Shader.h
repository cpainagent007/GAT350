#pragma once
#include "../Resources/Resource.h"

namespace neu {
	class Shader : public Resource {
	public:
		~Shader();

		bool Load(const std::string& filename, GLuint shaderType);

		GLuint GetShader() const { return m_shader; }

		void UpdateGui() override {}
	public:
		GLuint m_shader = 0;
	};
}