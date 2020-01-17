#include "interface.hpp"


void initialise_interface(int l,int h){
  // Initialise la SDL
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    cout << "Erreur lors du chargement de la SDL : "<<SDL_GetError()<<endl;
    SDL_Quit();
    return;
  }

  // Crée la fenêtre et l'afficheur associé
  if(SDL_CreateWindowAndRenderer(l, h, 0, &fenetre, &afficheur)<0){
    cout <<"Erreur lors de la creation de la fenetre SDL : "<<SDL_GetError()<<endl;
    SDL_Quit();
    return;
  }

  // Efface la fenêtre
  efface();
  rafraichissement();
}

void defini_couleur_dessin(SDL_Colour c){
  couleur_dessin=c;
  SDL_SetRenderDrawColor(afficheur,c.r,c.g,c.b,SDL_ALPHA_OPAQUE);
}

void dessine_ligne(int x1,int y1,int x2,int y2){
  SDL_RenderDrawLine(afficheur,x1,y1,x2,y2);
}

void dessine_rectangle(int x,int y,int l,int h){
  SDL_Rect rect;
  rect.x=x;
  rect.y=y;
  rect.w=l;
  rect.h=h;
  SDL_RenderDrawRect(afficheur,&rect);
}

void efface(){
  // Choisie la couleur de fond
   SDL_SetRenderDrawColor(afficheur,couleur_fond.r,couleur_fond.g,couleur_fond.b,SDL_ALPHA_OPAQUE);

   // Rempli toute la fenetre
   SDL_RenderClear(afficheur);

   // Choisie la couleur de dessin
   SDL_SetRenderDrawColor(afficheur,couleur_dessin.r,couleur_dessin.g,couleur_dessin.b,SDL_ALPHA_OPAQUE);
}

void ferme_interface(){
  if(afficheur){
    SDL_DestroyRenderer(afficheur);
  }
  if(fenetre){
    SDL_DestroyWindow(fenetre);
  }
  SDL_Quit();
}

void rafraichissement(){
  SDL_RenderPresent(afficheur);
}

void rempli_rectangle(int x,int y,int l,int h){
  SDL_Rect rect;
  rect.x=x;
  rect.y=y;
  rect.w=l;
  rect.h=h;
  SDL_RenderFillRect(afficheur, &rect);
}

void DrawDottedLine(int x0, int y0, int x1, int y1) {
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
    int count = 0;
    while (1) {
        if (count < 10) {SDL_RenderDrawPoint(afficheur,x0,y0);}
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
        count = (count + 1) % 20;
    }
}
void drawCircle(int xc, int yc, int x, int y) 
{ 
    SDL_RenderDrawPoint(afficheur,xc+x,yc+y) ; 
    SDL_RenderDrawPoint(afficheur,xc-x,yc+y); 
    SDL_RenderDrawPoint(afficheur,xc+x,yc-y); 
    SDL_RenderDrawPoint(afficheur,xc-x,yc-y); 
    SDL_RenderDrawPoint(afficheur,xc+y,yc+x); 
    SDL_RenderDrawPoint(afficheur,xc-y,yc+x); 
    SDL_RenderDrawPoint(afficheur,xc+y,yc-x); 
    SDL_RenderDrawPoint(afficheur,xc-y,yc-x); 
} 
  
/*Function for circle-generation using Bresenham's algorithm */
void circleBres(int xc, int yc, int r) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    while (y >= x) 
    { 
        /*for each pixel we will draw all eight pixels */
        drawCircle(xc, yc, x, y); 
        x++; 
  
        /*check for decision parameter and correspondingly update d, x, y*/
        if (d > 0) 
        { 
            y--; 
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        drawCircle(xc, yc, x, y); 
    } 
} 