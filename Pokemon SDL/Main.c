#include"Fonctions.h"
#include "vld.h"

int main(int argc, char**argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur d'initialisation de la SDL (%s)\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	Params * Parametres = InitParams();
	if (Parametres == NULL)
	{
		PAUSE;
		return -1;
	}
	printf("%s\n", Parametres->Cwd);
	menuSDL(Parametres);
	FreeParams(Parametres);
	free(Parametres);
	SDL_Quit();
	
	return 0;
}