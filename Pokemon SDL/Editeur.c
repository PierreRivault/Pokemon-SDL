#include "Fonctions.h"

void Editeur(Params* Parametres)
{
	char buffer[2048];
	resize_Window(Parametres->Fenetre, Parametres->Rendu, WINDOW_W, WINDOW_H);
	SDL_SetWindowPosition(Parametres->Fenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	TTF_Init();
	SDL_Color Blanc = { 255, 255, 255 };
	strcpy_s(buffer, 2048, Parametres->Cwd);
	strcat_s(buffer, 1024, "\\Ressources\\CENSCBK.ttf");
	TTF_Font *Font_Nums = TTF_OpenFont(buffer, 12);
	int hauteur, largeur, tileset_shawn = 1, local = 1, i, j, zone = 0;
	int ** fichier;
	SDL_Surface *Select, *Num_Ligne, *Num_Colonne;
	SDL_Texture* Selection = NULL, *tAff_indices;
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
	SDL_Rect selecteur, positionneur, Rzone, pos_Aff_indices;
	Vector pos_menu, taille_set, pos_affichage, pos_selecteur, pos_positionneur, taille_set_blocs, pos_zone, pos_camera, pos_camera_menu;
	SDL_Event Event;
	OPENFILENAME ofn;
	TCHAR tmp[1024];
	tmp[0] = '\0';
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Fichier à ouvrir:");
	ofn.lpstrFilter = _T("Niveaux (*.lvl)\0*.lvl\0Tous (*.*)\0*.*\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER;

	char Nfichier[256], *posEntree = NULL, Aff_indices[4];
	char path[1024];
	bool choix;
	FILE* Map = NULL;
	CLEAR;
	if (MessageBox(0, "Voulez-vous ouvrir un fichier?", "Ouvrir un fichier", MB_YESNO | MB_DEFBUTTON1) == IDYES)
	{
		GetOpenFileName(&ofn);
		strcpy_s(path, 1024, ofn.lpstrFile);
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
	}
	else
	{
		strcpy_s(path, 1024, "Saves\\Levels\\");
		printf("Nom du niveau:");
		fgets(Nfichier, 255, stdin);
		posEntree = strchr(Nfichier, '\n');
		if (posEntree)
			*posEntree = '\0';
		strcat_s(path, 1024, Nfichier);
		printf("Hauteur du niveau (en blocs):");
		scanf_s("%d", &hauteur);
		printf("Largeur du niveau (en blocs):");
		scanf_s("%d", &largeur);
		fichier = (int**)malloc(hauteur * sizeof(int*));
		for (int i = 0;i < hauteur;i++)
		{
			fichier[i] = (int*)calloc(largeur, sizeof(int));
		}
	}
	pos_affichage.x = AFFICHAGE_X;
	pos_affichage.y = AFFICHAGE_Y;
	pos_menu.x = 0;
	pos_menu.y = 0;
	pos_selecteur.x = 0;
	pos_selecteur.y = 0;
	pos_positionneur.x = 0;
	pos_positionneur.y = 0;
	pos_camera.x = 0;
	pos_camera.y = 0;
	pos_camera_menu.x = 0;
	pos_camera_menu.y = 0;
	while (local && Parametres->Destination)
	{
		SDL_RenderClear(Parametres->Rendu);
		SDL_QueryTexture(Parametres->Tableau[tileset_shawn - 1], NULL, NULL, &(taille_set.x), &(taille_set.y));
		taille_set_blocs.x = (taille_set.x - (taille_set.x % SIZETILE)) / SIZETILE;
		taille_set_blocs.y = (taille_set.y - (taille_set.y % SIZETILE)) / SIZETILE;
		for (i = 0;i < taille_set_blocs.x;i++)
		{
			for (j = 0;j < taille_set_blocs.y;j++)
				if ((((SIZETILE + 1) * j + pos_menu.y - pos_camera_menu.y) >= 0) && ((SIZETILE + 1) * j + pos_menu.y - pos_camera_menu.y) < WINDOW_H - SIZETILE)
					Afficher_ID(10000 * tileset_shawn + 100 * j + i, Parametres->Tableau, (SIZETILE + 1) * i + pos_menu.x, (SIZETILE + 1) * j + pos_menu.y - pos_camera_menu.y, Parametres->Rendu);
		}
		selecteur.x = (SIZETILE + 1) * (pos_menu.x + pos_selecteur.x);
		selecteur.y = (SIZETILE + 1) * (pos_menu.y + pos_selecteur.y) - pos_camera_menu.y;
		selecteur.h = SIZETILE;
		selecteur.w = SIZETILE;
		positionneur.x = SIZETILE * pos_positionneur.x + pos_affichage.x - pos_camera.x;
		positionneur.y = SIZETILE * pos_positionneur.y + pos_affichage.y - pos_camera.y;
		positionneur.h = SIZETILE;
		positionneur.w = SIZETILE;

		for (i = 0;i < hauteur;i++)
		{
			for (j = 0;j < largeur;j++)
			{
				if (fichier[i][j] != 0)
				{
					if ((pos_affichage.x + SIZETILE * j - pos_camera.x >= AFFICHAGE_X)&&(pos_affichage.x + SIZETILE * j - pos_camera.x < WINDOW_W)&&(pos_affichage.y + SIZETILE * i - pos_camera.y >= AFFICHAGE_Y)&&(pos_affichage.y + SIZETILE * i - pos_camera.y < WINDOW_H))
					{
						Afficher_ID(fichier[i][j], Parametres->Tableau, pos_affichage.x + SIZETILE * j - pos_camera.x, pos_affichage.y + SIZETILE * i - pos_camera.y, Parametres->Rendu);
					}
				}
			}
		}
		for (i = 0;i < hauteur;i++)
		{
			pos_Aff_indices.y = AFFICHAGE_Y + SIZETILE * i - pos_camera.y;
			if (pos_Aff_indices.y >= AFFICHAGE_Y && pos_Aff_indices.y < WINDOW_H)
			{
				sprintf_s(Aff_indices, 4, "%d", i + 1);
				Num_Ligne = TTF_RenderText_Blended(Font_Nums, Aff_indices, Blanc);
				tAff_indices = SDL_CreateTextureFromSurface(Parametres->Rendu, Num_Ligne);
				pos_Aff_indices.w = Num_Ligne->w;
				pos_Aff_indices.h = Num_Ligne->h;
				pos_Aff_indices.x = AFFICHAGE_X - 15;
				if (i > 98)
					pos_Aff_indices.x -= 8;
				SDL_RenderCopy(Parametres->Rendu, tAff_indices, NULL, &pos_Aff_indices);
				SDL_FreeSurface(Num_Ligne);
				SDL_DestroyTexture(tAff_indices);
			}
		}
		for (j = 0;j < largeur;j++)
		{
			pos_Aff_indices.x = AFFICHAGE_X + j*SIZETILE - pos_camera.x;
			if (pos_Aff_indices.x >= AFFICHAGE_X && pos_Aff_indices.x < WINDOW_W)
			{
				sprintf_s(Aff_indices, 4, "%d", j + 1);
				Num_Colonne = TTF_RenderText_Blended(Font_Nums, Aff_indices, Blanc);
				tAff_indices = SDL_CreateTextureFromSurface(Parametres->Rendu, Num_Colonne);
				pos_Aff_indices.w = Num_Colonne->w;
				pos_Aff_indices.h = Num_Colonne->h;
				pos_Aff_indices.y = AFFICHAGE_Y - 16;
				SDL_RenderCopy(Parametres->Rendu, tAff_indices, NULL, &pos_Aff_indices);
				SDL_FreeSurface(Num_Colonne);
				SDL_DestroyTexture(tAff_indices);
			}
		}
		SDL_RenderCopy(Parametres->Rendu, Selection, NULL, &selecteur);
		SDL_RenderCopy(Parametres->Rendu, Selection, NULL, &positionneur);
		if (zone == 1)
		{
			Rzone.x = SIZETILE * pos_zone.x + pos_affichage.x - pos_camera.x;
			Rzone.y = SIZETILE * pos_zone.y + pos_affichage.y - pos_camera.y;
			Rzone.w = SIZETILE;
			Rzone.h = SIZETILE;
			if ((Rzone.x >= AFFICHAGE_X) && (Rzone.x < WINDOW_W - SIZETILE) && (Rzone.y >= AFFICHAGE_Y) && (Rzone.y < WINDOW_H))
				SDL_RenderCopy(Parametres->Rendu, Selection, NULL, &Rzone);
		}
		SDL_RenderPresent(Parametres->Rendu);
		SDL_WaitEvent(&Event);
		switch (Event.type)
		{
		default:
			local = 1;
			break;
		case SDL_QUIT:
			Parametres->Destination = 0;
			break;
		case SDL_KEYDOWN:
			switch (Event.key.keysym.sym)
			{
			default:
				break;
			case SDLK_z:
				if (pos_selecteur.y > 0)
				{
					pos_selecteur.y--;
					if (pos_selecteur.y * (SIZETILE + 1) - pos_camera_menu.y < 0)
						pos_camera_menu.y -= (SIZETILE + 1);
				}
				break;
			case SDLK_s:
				if (pos_selecteur.y < taille_set_blocs.y - 1)
				{
					pos_selecteur.y++;
					if (pos_selecteur.y * (SIZETILE + 1) - pos_camera_menu.y > WINDOW_H - SIZETILE)
						pos_camera_menu.y += (SIZETILE + 1);
				}
				break;
			case SDLK_q:
				if (pos_selecteur.x > 0)
					pos_selecteur.x--;
				break;
			case SDLK_d:
				if (pos_selecteur.x < taille_set_blocs.x - 1)
					pos_selecteur.x++;
				break;
			case SDLK_UP:
				if (pos_positionneur.y > 0)
				{
					pos_positionneur.y--;
					if (pos_positionneur.y * SIZETILE - pos_camera.y < 0)
						pos_camera.y -= SIZETILE;
				}
				break;
			case SDLK_DOWN:
				if (pos_positionneur.y < hauteur - 1)
				{
					pos_positionneur.y++;
					if (pos_positionneur.y * SIZETILE - pos_camera.y + AFFICHAGE_Y > WINDOW_H - SIZETILE)
						pos_camera.y += SIZETILE;
				}
				break;
			case SDLK_LEFT:
				if (pos_positionneur.x > 0)
				{
					pos_positionneur.x--;
					if (pos_positionneur.x * SIZETILE - pos_camera.x < 0)
						pos_camera.x -= SIZETILE;
				}
				break;
			case SDLK_RIGHT:
				if (pos_positionneur.x < largeur - 1)
				{
					pos_positionneur.x++;
					if (pos_positionneur.x * SIZETILE - pos_camera.x + AFFICHAGE_X > WINDOW_W - SIZETILE)
						pos_camera.x += SIZETILE;
				}
				break;
			case SDLK_RETURN:
				if (zone == 1)
				{
					zone = 0;
					if ((pos_zone.x < pos_positionneur.x)&&(pos_zone.y < pos_positionneur.y))
					{
						for (int u = pos_zone.x;u <= pos_positionneur.x;u++)
						{
							for (int v = pos_zone.y;v <= pos_positionneur.y;v++)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else if ((pos_zone.x > pos_positionneur.x) && (pos_zone.y < pos_positionneur.y))
					{
						for (int u = pos_zone.x;u >= pos_positionneur.x;u--)
						{
							for (int v = pos_zone.y;v <= pos_positionneur.y;v++)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else if ((pos_zone.x < pos_positionneur.x) && (pos_zone.y > pos_positionneur.y))
					{
						for (int u = pos_zone.x;u <= pos_positionneur.x;u++)
						{
							for (int v = pos_zone.y;v >= pos_positionneur.y;v--)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else
					{
						for (int u = pos_zone.x;u >= pos_positionneur.x;u--)
						{
							for (int v = pos_zone.y;v >= pos_positionneur.y;v--)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
				}
				else
					fichier[pos_positionneur.y][pos_positionneur.x] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
				break;
			case SDLK_w:
				if (zone == 1)
				{
					zone = 0;
					if ((pos_zone.x < pos_positionneur.x) && (pos_zone.y < pos_positionneur.y))
					{
						for (int u = pos_zone.x;u <= pos_positionneur.x;u++)
						{
							for (int v = pos_zone.y;v <= pos_positionneur.y;v++)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else if ((pos_zone.x > pos_positionneur.x) && (pos_zone.y < pos_positionneur.y))
					{
						for (int u = pos_zone.x;u >= pos_positionneur.x;u--)
						{
							for (int v = pos_zone.y;v <= pos_positionneur.y;v++)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else if ((pos_zone.x < pos_positionneur.x) && (pos_zone.y > pos_positionneur.y))
					{
						for (int u = pos_zone.x;u <= pos_positionneur.x;u++)
						{
							for (int v = pos_zone.y;v >= pos_positionneur.y;v--)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
					else
					{
						for (int u = pos_zone.x;u >= pos_positionneur.x;u--)
						{
							for (int v = pos_zone.y;v >= pos_positionneur.y;v--)
							{
								fichier[v][u] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
							}
						}
					}
				}
				else
					fichier[pos_positionneur.y][pos_positionneur.x] = 10000 * tileset_shawn + 100 * pos_selecteur.y + pos_selecteur.x;
				break;
			case SDLK_DELETE:
				fichier[pos_positionneur.y][pos_positionneur.x] = 0;
				break;
			case SDLK_ESCAPE:
				local = 0;
				break;
			case SDLK_a:
				if (tileset_shawn > 1)
				{
					tileset_shawn--;
					pos_selecteur.x = 0;
					pos_selecteur.y = 0;
					pos_camera_menu.y = 0;
				}
				break;
			case SDLK_e:
				if (tileset_shawn < 8)
				{
					tileset_shawn++;
					pos_selecteur.x = 0;
					pos_selecteur.y = 0;
					pos_camera_menu.y = 0;
				}
				break;
			case SDLK_c:
				if (fichier[pos_positionneur.y][pos_positionneur.x] != 0)
				{
					tileset_shawn = (fichier[pos_positionneur.y][pos_positionneur.x]) / 10000;
					pos_selecteur.y = ((fichier[pos_positionneur.y][pos_positionneur.x]) - (((fichier[pos_positionneur.y][pos_positionneur.x]) / 10000) * 10000)) / 100;
					pos_selecteur.x = (fichier[pos_positionneur.y][pos_positionneur.x]) - (((fichier[pos_positionneur.y][pos_positionneur.x]) / 100) * 100);
				}
				break;
			case SDLK_t:
				pos_zone.x = pos_positionneur.x;
				pos_zone.y = pos_positionneur.y;
				zone = 1;
				break;
			case SDLK_f:
				fopen_s(&Map, path, "w");
				if (!Map)
				{
					printf("Impossible d'ecrire dans le fichier de sauvegarde\n");
					system("pause");
					local = 0;
					break;
				}
				rewind(Map);
				fprintf(Map, "%d\t%d\n", hauteur, largeur);
				for (i = 0;i < hauteur;i++)
				{
					for (j = 0;j < largeur;j++)
						fprintf(Map, "%d ", fichier[i][j]);
					fprintf(Map, "\n");
				}
				fclose(Map);
				break;
			}
		}
	}
	for (int i = 0;i < hauteur;i++)
	{
		free(fichier[i]);
	}
	free(fichier);
	SDL_DestroyTexture(Selection);
	TTF_CloseFont(Font_Nums);
	TTF_Quit();
}