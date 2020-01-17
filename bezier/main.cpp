#include "interface.hpp"

//--------------
// Question 3.a
//--------------

//--------------
// Question 3.b
//--------------

//--------------
// Question 4.a
//--------------

//--------------
// Question 5.a
//--------------

//--------------
// Question 5.b
//--------------

int main(){  
  // Creation d'une interface graphique de 800x600
  initialise_interface(800,600);

  // Quitter vaudra true si l'utilisateur demande à quitter
  bool quitter=false;

  // Evenement de l'interface
  SDL_Event ev;
  SDL_KeyboardEvent cev;
  SDL_MouseButtonEvent mbev;
  

  // Loop dealing event
  while(not quitter){

    //Event detection
    while(SDL_PollEvent(&ev)!= 0){
      switch(ev.type){
      case SDL_QUIT:
	// Fermeture fenetre demandée
	quitter=true;
	break;
      case SDL_KEYDOWN:
	// Touche enfoncée
	// Detection de la touche enfoncée
	cev=ev.key;
	switch(cev.keysym.sym){
	  // Touche Q
	case SDLK_q:
	  quitter=true;
	  break;
	default:
	  break;
	}
	break;
      case SDL_MOUSEBUTTONDOWN:
	mbev=ev.button;
	switch(mbev.button){
	case SDL_BUTTON_LEFT:
	cout<<"Clique gauche à la position "<<mbev.x<<" "<<mbev.y<<endl;
	  break;
	}
      default:
	break;
      }
    }
    SDL_Delay(100); 
  }
  ferme_interface();
}
