#pragma once

#include "Texture.h"

namespace neu {
	class Cubemap : public Texture {
	public:
		bool Load(const std::string& filenames);

		void UpdateGui() override {}
	};
}