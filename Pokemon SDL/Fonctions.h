#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include "Load.h"

typedef enum bool
{
	false,
	true
}bool;

void menuSDL(Params* Parametres);//Fonction du menu
void Editeur(Params* Parametres);//Fonction de l'éditeur de maps
void Jeu(Params* Parametres);//Foncion du jeu
void resize_Window(SDL_Window* Fenetre, SDL_Renderer* Rendu, int x, int y);//resimensionnne la fenetre, et la met en noir
void convert_multiple(TCHAR* buf);
void viderBuffer(void);//vide le buffer d'entree du programme
void Afficher_ID(int ID, SDL_Texture ** tableau, int x, int y, SDL_Renderer * rendu);//fonction qui affiche un tilemap en position x y grâce à son ID

#endif