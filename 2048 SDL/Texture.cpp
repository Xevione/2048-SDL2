#include "Texture.h"

#include <SDL.h>
#include <string>

TextureManager::TextureManager() {
	tableTexture = {
		fond = nullptr,

	}

	tab = {
		string fond = "src/fond2.bmp",
		string win = "src/win.bmp",
		string loose = "src/loose.bmp",
		string t0 = "src/0.bmp",
		string t2 = "src/2.bmp",
		string t4 = "src/4.bmp",
		string t8 = "src/8.bmp",
		string t16 = "src/16.bmp",
		string t32 = "src/32.bmp",
		string t64 = "src/64.bmp",
		string t128 = "src/128.bmp",
		string t256 = "src/256.bmp",
		string t512 = "src/512.bmp",
		string t1024 = "src/1024.bmp",
		string t2048 = "src/2048.bmp",
	};
	
}
