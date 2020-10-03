#include "interface.hpp"
#include <cmath>

static const double g=9.81; // en m.s-1
static double l=1; //en m
static double h=0.02; //en s

//--------------
// Question 7.a
//--------------

void dessine_pendule(double theta){
	int x0, x1, y0, y1;
	x0 = 400;
	x1 = 0;
	y0 = 300;
	y1 = 200;


	double cosval;
	cosval = cos(theta);

	double sinval;
	sinval = sin(theta);


	/* On utilise les fonctions de rotation d'un vecteur par rapport à un angle pour les positions du pendule */
	int tempx1 = x1 * cosval - y1 * sinval;
	int tempy1 = x1 * sinval + y1 * cosval;

	x1 = tempx1;
	y1 = tempy1;


	dessine_ligne(x0, y0, x0+x1, y0+y1);
	dessine_cercle(x0+x1, y0+y1, 30);

}

//--------------
// Question 8.a
//--------------

void f(double t,double theta,double omega,double& dtheta,double& domega){
	dtheta = omega;
	domega = -g/l * sin(theta);
}
  
//--------------
// Question 8.b
//--------------

void rk1(double t,double& theta,double& omega){
	double domega;
	double dtheta;
	f(t, theta, omega, dtheta, domega);

	theta = theta + t*dtheta;
	omega = omega + t*domega;

	cout<<"theta = "<<theta<<endl;

}

//--------------
// Question 8.c
//--------------

void rk2(double t,double& theta,double& omega){
	double domega;
	double dtheta;

	f(t, theta, omega, dtheta, domega);

	double rk1theta = theta; 
	double rk1omega = omega;

	rk1(t, rk1theta, rk1omega); //On calcule hf(tn, an) via RK1

	rk1theta -= theta; //On soustrait la valeur d'an à an+1 (calculé grâce RK1) pour 
	rk1omega -= omega; //obtenir hf(tn, an) au lieu de an + hf(tn, an)

	theta = theta + 1/2 * rk1theta; //On calcule an+h/2*f(tn,an)
	omega = omega + 1/2 * rk1omega;

	rk1(t+h*0.5, theta, omega); 

}

//---------------
// Fonction main
//---------------

int main(){
  // Creation d'une interface graphique de 450x580
  initialise_interface(800,600);

  // Quitter vaudra true si l'utilisateur demande à quitter
  bool quitter=false;

  // Evenement de l'interface
  SDL_Event ev;
  SDL_KeyboardEvent cev;
  SDL_MouseButtonEvent mbev;
  
  // Condition initiale
  double theta=pi/8;
  double omega=0;
  double t=0;
  // Loop dealing event
  while(not quitter){
    unsigned int debut=SDL_GetTicks();
    //Event detection
    while(SDL_PollEvent(&ev)!= 0){
      switch(ev.type){
      case SDL_QUIT:
	// Fermeture fenetre demandée
	quitter=true;
	break;
      default:
	break;
      }
    }
    efface();
    dessine_pendule(theta);
    t+=h;
	rk2(h, theta, omega);
    rafraichissement();
    unsigned int ecoule=SDL_GetTicks()-debut;
    if(1000*h>ecoule){ // Conversion de h en ms
      SDL_Delay(1000*h-ecoule);
    }
  }
  ferme_interface();
}
