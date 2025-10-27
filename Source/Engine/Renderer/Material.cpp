#include "Material.h"
#include "Program.h"

namespace neu {
	bool Material::Load(const std::string& filename) {
		// load material document
		serial::document_t document;
		if (!serial::Load(filename, document)) {
			LOG_WARNING("Could not load program file: {}", filename);
			return false;
		}

		// Program
		std::string programName;
		SERIAL_READ_NAME(document, "program", programName);

		program = Resources().Get<Program>(programName);

		// Texture
		std::string textureName;
		SERIAL_READ_NAME(document, "texture", textureName);

		texture = Resources().Get<Texture>(textureName);

		SERIAL_READ(document, shininess);
		SERIAL_READ(document, tiling);
		SERIAL_READ(document, offset);

		return true;
	}

	void Material::Bind() {
		program->Use();
		texture->SetActive(GL_TEXTURE0);
		texture->Bind();

		program->SetUniform("u_material.shininess", shininess);
		program->SetUniform("u_material.tiling", tiling);
		program->SetUniform("u_material.offset", offset);
	}
}