#include "Fonctions.h"

void Jeu(Params* Parametres)
{
	char buffer[2048];
	resize_Window(Parametres->Fenetre, Parametres->Rendu, 9 * SIZETILE, 9 * SIZETILE);
	SDL_SetWindowPosition(Parametres->Fenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	int continuer = 1, hauteur, largeur, i, j, openfile;
	OPENFILENAME ofn;
	TCHAR tmp[1024];
	tmp[0] = '\0';
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Fichier à ouvrir:");
	ofn.lpstrFilter = _T("Niveaux (*.lvl)\0*.lvl\0Tous (*.*)\0*.*\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER | OFN_FILEMUSTEXIST;
	int **fichier;
	char Nfichier[1024], *posEntree = NULL;
	char path[1024];
	FILE *Map;
	Vector pos_camera, pos_joueur;
	SDL_Texture* Selection = NULL;
	if (SIZETILE == 16)
	{
		strcpy_s(buffer, 2048, Parametres->Cwd);
		strcat_s(buffer, 1024, "\\Sprites\\Tilemap\\Selection.png");
		Selection = IMG_LoadTexture(Parametres->Rendu, buffer);
	}
	else
	{
		strcpy_s(buffer, 2048, Parametres->Cwd);
		strcat_s(buffer, 1024, "\\Sprites\\Tilemap\\Selection_32.png");
		Selection = IMG_LoadTexture(Parametres->Rendu, buffer);
	}
	if (!Selection)
	{
		printf("Impossible de charger le fichier Selection.png (%s)\n", SDL_GetError());
		return;
	}
	SDL_Event evenement;
	SDL_Rect PosTest;
	CLEAR;
	openfile = GetOpenFileName(&ofn);
	strcpy_s(path, 1024, ofn.lpstrFile);

	if (openfile == 0)
		return;
	fopen_s(&Map, path, "r+");
	if (!Map)
	{
		printf("Ouverture du fichier %s impossible\n", Nfichier);
		return;
	}
	fscanf_s(Map, "%d\t%d", &hauteur, &largeur);
	fichier = (int**)malloc(hauteur * sizeof(int*));
	for (int i = 0;i < hauteur;i++)
	{
		fichier[i] = (int*)calloc(largeur, sizeof(int));
	}
	for (int i = 0;i < hauteur;i++)
	{
		for (int j = 0;j < largeur;j++)
		{
			fscanf_s(Map, "%d", &(fichier[i][j]));
		}
	}
	fclose(Map);
	pos_camera.x = 0;
	pos_camera.y = 0;
	pos_joueur.x = 0;
	pos_joueur.y = 0;
	while (continuer && Parametres->Destination)
	{
		SDL_RenderClear(Parametres->Rendu);
		for (i = 0;i < hauteur;i++)
		{
			for (j = 0;j < largeur;j++)
			{
				if (fichier[i][j] != 0)
				{
					if ((SIZETILE * j - pos_camera.x >= 0) && (SIZETILE * j - pos_camera.x < 10 * SIZETILE) && (SIZETILE * i - pos_camera.y >= 0) && (SIZETILE * i - pos_camera.y < 10*SIZETILE))
					{
						Afficher_ID(fichier[i][j], Parametres->Tableau, SIZETILE * j - pos_camera.x, SIZETILE * i - pos_camera.y, Parametres->Rendu);
					}
				}
			}
		}
		PosTest.h = SIZETILE;
		PosTest.w = SIZETILE;
		PosTest.x = pos_joueur.x - pos_camera.x;
		PosTest.y = pos_joueur.y - pos_camera.y;
		SDL_RenderCopy(Parametres->Rendu, Selection, NULL, &PosTest);
		SDL_RenderPresent(Parametres->Rendu);
		SDL_PollEvent(&evenement);
		switch (evenement.type)
		{
		case SDL_QUIT:
			Parametres->Destination = 0;
			break;
		case SDL_KEYDOWN:
			switch (evenement.key.keysym.sym)
			{
			case SDLK_z:
				if (pos_joueur.y > 0)
					pos_joueur.y -= SIZETILE;
				if (pos_joueur.y - pos_camera.y < 0)
					pos_camera.y -= SIZETILE;
				break;
			case SDLK_s:
				if (pos_joueur.y < (hauteur - 1) * SIZETILE)
					pos_joueur.y += SIZETILE;
				if (pos_joueur.y - pos_camera.y > 8 * SIZETILE)
					pos_camera.y += SIZETILE;
				break;
			case SDLK_q:
				if (pos_joueur.x > 0)
					pos_joueur.x -= SIZETILE;
				if (pos_joueur.x - pos_camera.x < 0)
					pos_camera.x -= SIZETILE;
				break;
			case SDLK_d:
				if (pos_joueur.x < (largeur - 1) * SIZETILE)
					pos_joueur.x += SIZETILE;
				if (pos_joueur.x - pos_camera.x > 8 * SIZETILE)
					pos_camera.x += SIZETILE;
				break;
			case SDLK_ESCAPE:
				continuer = 0;
				break;
			default:
				continuer = 1;
				break;
			}
		}
	}
	SDL_DestroyTexture(Selection);
	for (int i = 0;i < hauteur;i++)
	{
		free(fichier[i]);
	}
	free(fichier);
}