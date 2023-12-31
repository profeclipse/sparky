#pragma once

#include "sparky.h"

class TileLayer : public sparky::Layer {
	public:
		TileLayer(sparky::Ref<sparky::Shader> shader)
			: sparky::Layer(sparky::CreateRef<sparky::BatchRenderer2D>(),shader,
					sparky::mat4::orthographic(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f)) {
			}

		~TileLayer() {}
};
