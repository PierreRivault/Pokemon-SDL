#ifndef _LOAD_H_
#define _LOAD_H_

#define CLEAR system("cls");
#define PAUSE system("pause");

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <direct.h>
#include <windows.h>
#include "SDL\SDL_ttf.h"
#include "Struct.h"

#define SIZETILE 32
#define WINDOW_W 1920
#define WINDOW_H 1007
#define AFFICHAGE_X 17*SIZETILE + 20
#define AFFICHAGE_Y 112
#define NB_SPRITES 8

Params* InitParams(void);//Initialise les parametres "globaux" envoyés à ttes les fonctions du programmme
void FreeParams(Params * Parametres);//libère les paramètres "globaux"
SDL_Texture ** LoadTiles(SDL_Renderer * rendu);//fonction qui charge les 8 fichiers de tilemap
int * LoadID(SDL_Texture ** tableau);//alloue le tableau des ID correspondantes pour un fichier de tilemaps

#endif