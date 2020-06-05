#include<stdio.h>
#include<stdlib.h>
#include"Load.h"

Params* InitParams(void)
{
	Params* Parametres = calloc(1, sizeof(Params));
	Parametres->NB_Sprites = NB_SPRITES;
	Parametres->Fenetre = SDL_CreateWindow("Pocket Monsters", 0, 32, 0, 0, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!(Parametres->Fenetre))
	{
		printf("Erreur de creation de la fenetre (%s)\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	Parametres->Rendu = SDL_CreateRenderer(Parametres->Fenetre, -1, SDL_RENDERER_ACCELERATED);
	Parametres->Tableau = LoadTiles(Parametres->Rendu);
	Parametres->Tab_ID = LoadID(Parametres->Tableau);
	Parametres->Destination = 1;
	if ((Parametres->Cwd = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");
	return Parametres;
}

void FreeParams(Params * Parametres)
{
	for (int i = 0; i < Parametres->NB_Sprites; i++)
	{
		SDL_DestroyTexture(Parametres->Tableau[i]);
	}
	free(Parametres->Tableau);
	SDL_DestroyRenderer(Parametres->Rendu);
	free(Parametres->Tab_ID);
	SDL_DestroyWindow(Parametres->Fenetre);
}

SDL_Texture ** LoadTiles(SDL_Renderer * rendu)
{
	SDL_Texture ** tableau = (SDL_Texture**)calloc(NB_SPRITES, sizeof(SDL_Texture*));
	char* path;
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Grottes.png";
	else
		path = "Sprites\\Tilemap\\Grottes_32.png";
	SDL_Surface * Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Grottes.png (%s)\n", SDL_GetError());
	else
	{
		tableau[0] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[0])
		{
			printf("Impossible de convertir Grottes.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Interieur2.png";
	else
		path = "Sprites\\Tilemap\\Interieur2_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Interieur2.png (%s)\n", SDL_GetError());
	else
	{
		tableau[1] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[1])
		{
			printf("Impossible de convertir Interieur2.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Interieur3.png";
	else
		path = "Sprites\\Tilemap\\Interieur3_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Interieur3.png (%s)\n", SDL_GetError());
	else
	{
		tableau[2] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[2])
		{
			printf("Impossible de convertir Interieur3.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Interieur4.png";
	else
		path = "Sprites\\Tilemap\\Interieur4_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Interieur4.png (%s)\n", SDL_GetError());
	else
	{
		tableau[3] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[3])
		{
			printf("Impossible de convertir Interieur4.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Maison_exterieur.png";
	else
		path = "Sprites\\Tilemap\\Maison_exterieur_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Maison_exterieur.png (%s)\n", SDL_GetError());
	else
	{
		tableau[4] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[4])
		{
			printf("Impossible de convertir Maison_exterieur.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Maison_interieur.png";
	else
		path = "Sprites\\Tilemap\\Maison_interieur_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Maison_interieur.png (%s)\n", SDL_GetError());
	else
	{
		tableau[5] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[5])
		{
			printf("Impossible de convertir Maison_interieur.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Overworld.png";
	else
		path = "Sprites\\Tilemap\\Overworld_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Overworld.png (%s)\n", SDL_GetError());
	else
	{
		tableau[6] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[6])
		{
			printf("Impossible de convertir Overworld.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	if (SIZETILE == 16)
		path = "Sprites\\Tilemap\\Special.png";
	else
		path = "Sprites\\Tilemap\\Special_32.png";
	Texture = IMG_Load(path);
	if (!Texture)
		printf("Impossible de charger le fichier Special.png (%s)\n", SDL_GetError());
	else
	{
		tableau[7] = SDL_CreateTextureFromSurface(rendu, Texture);
		if (!tableau[7])
		{
			printf("Impossible de convertir Special.png en Texture (%s)\n", SDL_GetError());
			SDL_FreeSurface(Texture);
			return NULL;
		}
		SDL_FreeSurface(Texture);
	}
	return tableau;
}

int * LoadID(SDL_Texture ** tableau)
{
	int i = 0, w, h, j, k, l, count = 0;
	for (j = 0; j < 8; j++)
	{
		SDL_QueryTexture(tableau[j], NULL, NULL, &w, &h);
		i += (w / SIZETILE)*(h / SIZETILE);
	}
	int* tab_ID = (int*)calloc(i, sizeof(int));
	for (j = 0; j < 8; j++)
	{
		SDL_QueryTexture(tableau[j], NULL, NULL, &w, &h);
		for (k = 0; k < h/SIZETILE; k++)
		{
			for (l = 0; l < w / SIZETILE; l++)
			{
				tab_ID[count] = 10000 * (j+1) + 100 * k + l;
				count++;
			}
		}
	}
	return tab_ID;
}