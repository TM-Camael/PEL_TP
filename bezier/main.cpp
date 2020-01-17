#include "interface.hpp"
#include <vector>
#include "point.hpp"

void dessiner_point(Point p, int c){
  dessine_rectangle(p.lire_x(), p.lire_y(), 2*c+1, 2*c+1);
  rafraichissement();
}

void faire_dessin(vector<Point> liste_point){
  for(int i=1; i<liste_point.size(); i++){
    DrawDottedLine(liste_point[i-1].lire_x(),liste_point[i-1].lire_y(), liste_point[i].lire_x(),liste_point[i].lire_y());
  }
  rafraichissement();
}

bool bezier_negligeable(Point a, Point b, Point c, Point d){
  double distancep = distance(a,b)+distance(b,c)+distance(c,d);
  if(distancep<0.1){
    return true;
  } else {
    return false;
  }
}

void bezierCurve(Point a, Point b, Point c, Point d){ 
  cout<<a<<" "<<d<<endl;
  if(bezier_negligeable(a,b,c,d)){
    dessine_ligne(a.lire_x(),a.lire_y(),d.lire_x(),d.lire_y());
  } else {
    Point ab = millieu(a,b);  
    Point bc = millieu(b,c);
    Point cd = millieu(c,d);
    Point abc = millieu(ab,bc);
    Point bcd = millieu(bc,cd);
    Point abcd = millieu(abc,bcd);    
    bezierCurve(a,ab,abc,abcd);
    bezierCurve(abcd,bcd,cd,d);
  }
  rafraichissement();
} 

int main(){  
  // Creation d'une interface graphique de 800x600
  initialise_interface(800,600);

  // Quitter vaudra true si l'utilisateur demande à quitter
  bool quitter=false;

  // Evenement de l'interface
  SDL_Event ev;
  SDL_KeyboardEvent cev;
  SDL_MouseButtonEvent mbev;
  
  std::vector<Point> liste_point;
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
    liste_point.push_back(Point(mbev.x,mbev.y));
    if(liste_point.size() != 5){
      dessiner_point(liste_point[liste_point.size()-1],1);
    }
    cout<<liste_point.size()<<endl;
    if(liste_point.size()==4){
      cout<<"Dessin courbe de Bézier"<<endl;
      faire_dessin(liste_point);
      Point a = liste_point[0];
      Point b = liste_point[1];
      Point c = liste_point[2];
      Point d = liste_point[3];
      bezierCurve(a,b,c,d);
    } else if(liste_point.size()==5){
      cout<<"Efface courbe de Bézier"<<endl;
      liste_point.clear();
      
      efface();
      rafraichissement();
    }
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
