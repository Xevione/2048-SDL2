#pragma once
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
#include <vector>
using namespace std;

class TextureManager
{
public:
	SDL_Renderer* renderer;
	TextureManager(SDL_Renderer* rendering);
	vector<SDL_Surface*> tableSurface;
	vector<SDL_Texture*> tableTexture;
	


	void initTexture();

	~TextureManager();
};
