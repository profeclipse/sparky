#include <stdio.h>
#include <cstddef>
#include <string>
#include <unistd.h>
#include <iostream>
#include "sparky-gl.h"
#include "sparky-utils.h"
#include <Utilities.h>

namespace sparky {
	BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height,int* bpp) {
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(filename,0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
		{
			SP_ERROR("[load_image] - unknown image format or file not found '{}'",filename);
			return nullptr;
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif,filename);
		if (!dib)
		{
			SP_ERROR("[load_image] - failed to load file '{}'",filename);
			return nullptr;
		}

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		int bits = FreeImage_GetBPP(dib);
		if (bpp) {
			*bpp = bits;
		}

#ifdef __EMSCRIPTEN__
		if (bits > 16)
			SwapRedBlue32(dib);
#endif

		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result,pixels,size);
		FreeImage_Unload(dib);
		return result;
	}
}
