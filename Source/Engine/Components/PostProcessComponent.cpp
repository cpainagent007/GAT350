#include "PostProcessComponent.h"
#include <Engine.h>

namespace neu {
	FACTORY_REGISTER(PostProcessComponent)

	void PostProcessComponent::Update(float dt)	{
	}

	void PostProcessComponent::Apply(Program& program) {
		program.SetUniform("u_parameters", (uint32_t)parameters);
		program.SetUniform("u_colorTint", colorTint);

		program.SetUniform("u_time", GetEngine().GetTime().GetTime());
		program.SetUniform("u_intensity", blend);
		program.SetUniform("u_baseMap", 0);
	}


	void PostProcessComponent::Read(const serial_data_t& value) {
		Object::Read(value);
	}

	void PostProcessComponent::UpdateGui() {
		uint32_t bitSelect = (uint32_t)parameters;

		bool check;

		check = bitSelect & (uint32_t)Parameters::GrayScale;
		if (ImGui::Checkbox("Grayscale", &check))
			check ? bitSelect |= (uint32_t)Parameters::GrayScale : bitSelect &= ~(uint32_t)Parameters::GrayScale;

		check = bitSelect & (uint32_t)Parameters::ColorTint;
		if (ImGui::Checkbox("Color Tint", &check))
			check ? bitSelect |= (uint32_t)Parameters::ColorTint : bitSelect &= ~(uint32_t)Parameters::ColorTint;

		check = bitSelect & (uint32_t)Parameters::Scanline;
		if (ImGui::Checkbox("Scanlines", &check))
			check ? bitSelect |= (uint32_t)Parameters::Scanline : bitSelect &= ~(uint32_t)Parameters::Scanline;

		check = bitSelect & (uint32_t)Parameters::Grain;
		if (ImGui::Checkbox("Grain / Noise", &check))
			check ? bitSelect |= (uint32_t)Parameters::Grain : bitSelect &= ~(uint32_t)Parameters::Grain;

		check = bitSelect & (uint32_t)Parameters::Invert;
		if (ImGui::Checkbox("Invert Colors", &check))
			check ? bitSelect |= (uint32_t)Parameters::Invert : bitSelect &= ~(uint32_t)Parameters::Invert;

		check = bitSelect & (uint32_t)Parameters::Vignette;
		if (ImGui::Checkbox("Vignette", &check))
			check ? bitSelect |= (uint32_t)Parameters::Vignette : bitSelect &= ~(uint32_t)Parameters::Vignette;

		parameters = (Parameters)bitSelect;

		ImGui::ColorEdit3("Color Tint", glm::value_ptr(colorTint));
		ImGui::SliderFloat("Blend", &blend, 0.0f, 1.0f);

	}
}
