#ifndef _STRUCT_H_
#define _STRUCT_H_

#include"SDL\SDL.h"
#include"SDL\SDL_image.h"

typedef struct sTileMap
{
	SDL_Texture * Origine;
	int ID;
}TileMap;

typedef struct sVector
{
	int x;
	int y;
}Vector;

typedef struct sParams
{
	SDL_Window* Fenetre;
	SDL_Renderer *Rendu;
	int NB_Sprites;
	SDL_Texture** Tableau;
	int* Tab_ID;
	int Destination;
	char* Cwd;
}Params;

#endif