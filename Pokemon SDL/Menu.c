#include "Fonctions.h"

void menuSDL(Params* Parametres)
{
	char buffer[2048];
	SDL_SetWindowSize(Parametres->Fenetre, 1280, 720);
	int continuer = 1;
	TTF_Init();//initialisation polices
	//création des deux polices
	strcpy_s(buffer, 2048, Parametres->Cwd);
	strcat_s(buffer, 2048, "\\Ressources\\CENSCBK.ttf");
	TTF_Font* Titre = TTF_OpenFont(buffer, 125);
	strcpy_s(buffer, 2048, Parametres->Cwd);
	strcat_s(buffer, 2048, "\\Ressources\\CENSCBK.ttf");
	TTF_Font* STitre = TTF_OpenFont(buffer, 70);
	SDL_Color Noir = { 0, 0, 0 };
	//chargement des surfaces depuis les fichiers ressources
	strcpy_s(buffer, 2048, Parametres->Cwd);
	strcat_s(buffer, 2048, "\\Sprites\\Tilemap\\Lac_Colere.jpg");
	SDL_Surface *fond_merisier = IMG_Load(buffer);
	SDL_Surface *texte_titre = TTF_RenderText_Blended(Titre, "Test Pokemon SDL", Noir);
	SDL_Surface *texte_stitre1 = TTF_RenderText_Blended(STitre, "1 Tester le jeu", Noir);
	SDL_Surface *texte_stitre2 = TTF_RenderText_Blended(STitre, "2 Editeur de maps", Noir);
	SDL_Surface *texte_stitre3 = TTF_RenderText_Blended(STitre, "3 Quitter", Noir);
	//création de textures à partir des surfaces
	SDL_Texture* MainTexture = SDL_CreateTextureFromSurface(Parametres->Rendu, fond_merisier);
	SDL_Texture* Title = SDL_CreateTextureFromSurface(Parametres->Rendu, texte_titre);
	SDL_Texture* STitle1 = SDL_CreateTextureFromSurface(Parametres->Rendu, texte_stitre1);
	SDL_Texture* STitle2 = SDL_CreateTextureFromSurface(Parametres->Rendu, texte_stitre2);
	SDL_Texture* STitle3 = SDL_CreateTextureFromSurface(Parametres->Rendu, texte_stitre3);
	//création des SDL_Rect dans lesquels afficher les textures
	SDL_Rect pos = { 0, 0, 1280, 720 };
	SDL_Rect titlepos = { 640 - ((texte_titre->w) / 2), 50, texte_titre->w, texte_titre->h };
	SDL_Rect stitle1pos = { 640 - ((texte_stitre1->w) / 2), 250, texte_stitre1->w, texte_stitre1->h };
	SDL_Rect stitle2pos = { 640 - ((texte_stitre2->w) / 2), 335, texte_stitre2->w, texte_stitre2->h };
	SDL_Rect stitle3pos = { 640 - ((texte_stitre3->w) / 2), 420, texte_stitre3->w, texte_stitre3->h };
	SDL_Event evenement;//déclaration de la variable récupérant les évènements
	while (continuer && Parametres->Destination)//boucle principale
	{
		SDL_SetWindowPosition(Parametres->Fenetre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		//copie des textures sur le renderer
		SDL_RenderCopy(Parametres->Rendu, MainTexture, NULL, &pos);
		SDL_RenderCopy(Parametres->Rendu, Title, NULL, &titlepos);
		SDL_RenderCopy(Parametres->Rendu, STitle1, NULL, &stitle1pos);
		SDL_RenderCopy(Parametres->Rendu, STitle2, NULL, &stitle2pos);
		SDL_RenderCopy(Parametres->Rendu, STitle3, NULL, &stitle3pos);
		//affichage du renderer dans la fenetre
		SDL_RenderPresent(Parametres->Rendu);
		//attente d'un évènement SDL
		SDL_WaitEvent(&evenement);
		switch (evenement.type)
		{
		case SDL_QUIT://clic sur la croix
			continuer = 0;
			break;
		case SDL_KEYDOWN://appui sur une touche
			switch (evenement.key.keysym.sym)
			{
			case SDLK_KP_1:
				Jeu(Parametres);
				SDL_SetWindowSize(Parametres->Fenetre, 1280, 720);
				break;
			case SDLK_KP_2:
				Editeur(Parametres);
				SDL_SetWindowSize(Parametres->Fenetre, 1280, 720);
				break;
			case SDLK_KP_3:
			case SDLK_ESCAPE:
				continuer = 0;
				break;
			default:
				break;
			}
		case SDL_MOUSEBUTTONDOWN://clic principal de souris
								 //verification de la présence du pointeur de la souris dans certaines zones de la fenêtre
			if (evenement.motion.x >= stitle1pos.x && evenement.motion.x <= stitle1pos.x + stitle1pos.w&&evenement.motion.y >= stitle1pos.y&&evenement.motion.y <= stitle1pos.y + stitle1pos.h)
			{
				Jeu(Parametres);
				SDL_SetWindowSize(Parametres->Fenetre, 1280, 720);
			}
			if (evenement.motion.x >= stitle2pos.x && evenement.motion.x <= stitle2pos.x + stitle2pos.w&&evenement.motion.y >= stitle2pos.y&&evenement.motion.y <= stitle2pos.y + stitle2pos.h)
			{
				Editeur(Parametres);
				SDL_SetWindowSize(Parametres->Fenetre, 1280, 720);
			}
			if (evenement.motion.x >= stitle3pos.x && evenement.motion.x <= stitle3pos.x + stitle3pos.w&&evenement.motion.y >= stitle3pos.y&&evenement.motion.y <= stitle3pos.y + stitle3pos.h)
			{
				continuer = 0;
			}
		default:
			break;
		}
		SDL_RenderClear(Parametres->Rendu);//nettoyage du renderer
	}
	//libération mémoire
	TTF_CloseFont(Titre);
	TTF_CloseFont(STitre);
	SDL_FreeSurface(fond_merisier);
	SDL_FreeSurface(texte_titre);
	SDL_FreeSurface(texte_stitre1);
	SDL_FreeSurface(texte_stitre2);
	SDL_FreeSurface(texte_stitre3);
	SDL_DestroyTexture(MainTexture);
	SDL_DestroyTexture(Title);
	SDL_DestroyTexture(STitle1);
	SDL_DestroyTexture(STitle2);
	SDL_DestroyTexture(STitle3);
	//on quitte la SDL et SDL_TTF
	TTF_Quit();
}