#include "Fonctions.h"

void resize_Window(SDL_Window* Fenetre, SDL_Renderer* Rendu, int x, int y)
{
	SDL_SetWindowSize(Fenetre, x, y);
	SDL_RenderClear(Rendu);
	SDL_RenderPresent(Rendu);
}

void convert_multiple(TCHAR* buf)
{
	int i;
	for (i = 0;;i++)
	{
		if (buf[i] == '\0')
		{
			buf[i] = '\n';
			if (buf[i + 1] == '\0')
				break;
		}
	}
}

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

void Afficher_ID(int ID, SDL_Texture ** tableau, int x, int y, SDL_Renderer * rendu)
{
	int h = (ID - ((ID / 10000) * 10000)) / 100;
	int w = ID - ((ID / 100) * 100);
	SDL_Rect clip = { SIZETILE * w, SIZETILE * h, SIZETILE, SIZETILE };
	SDL_Rect position = { x, y, SIZETILE, SIZETILE };
	SDL_RenderCopy(rendu, tableau[(ID / 10000) - 1], &clip, &position);
}