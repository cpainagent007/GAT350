#pragma once
#include "Resources/Resource.h"
#include "GUI/GUI.h"
#include "Program.h"
#include <glm/glm.hpp>

namespace neu {
	class Program;
	class Texture;

	class Material : public Resource, public GUI {
	public:
		enum class Parameters : uint32_t {
			None		= 0,
			BaseMap		= (1 << 0),
			SpecularMap	= (1 << 1),
			EmissiveMap	= (1 << 2),
			NormalMap	= (1 << 3),
			CubeMap		= (1 << 4)
		};

	public:
		Material() = default;
		~Material() = default;

		bool Load(const std::string& filename);

		void Bind();

		void UpdateGui() override;

	public:
		float shininess{ 2 };
		glm::vec2 tiling{ 1, 1 };
		glm::vec2 offset{ 0, 0 };
		glm::vec3 baseColor{ 1, 1, 1 };
		glm::vec3 emissiveColor{ 0, 0, 0 };
		float IOR = 1.3f;

		res_t<Program> program;
		res_t<Texture> baseMap;
		res_t<Texture> specularMap;
		res_t<Texture> emissiveMap;
		res_t<Texture> normalMap;
		res_t<Texture> cubeMap;

		Parameters parameters = Parameters::None;
	};
}