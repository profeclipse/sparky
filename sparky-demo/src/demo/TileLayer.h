#pragma once

#include "sparky-core.h"

class TileLayer : public sparky::Layer {
	public:
		TileLayer(sparky::Shader *shader)
			: sparky::Layer(new sparky::BatchRenderer2D(),shader,
					sparky::mat4::orthographic(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f)) {
			}

		~TileLayer() {}
};
