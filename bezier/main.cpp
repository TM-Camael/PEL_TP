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

bool bezier_negligeable(vector<Point> liste_point){
  int distancep = distance(liste_point[0],liste_point[1])+distance(liste_point[1],liste_point[2])+distance(liste_point[2],liste_point[3]);
  if(distancep>0.1){
    return true;
  } else {
    return false;
  }
}

void bezierCurve(vector<Point> liste_points){ 
  vector<Point> liste_points1;
  vector<Point> liste_points2;
  Point abcd;

  liste_points1.push_back(millieu(liste_points[0],liste_points[1]));
  liste_points1.push_back(millieu(liste_points[1],liste_points[2]));
  liste_points1.push_back(millieu(liste_points[2],liste_points[3]));
  
  dessiner_point(liste_points1[0],2);
  dessiner_point(liste_points1[1],2);
  dessiner_point(liste_points1[2],2);
  DrawDottedLine(liste_points1[0].lire_x() , liste_points1[0].lire_y(), liste_points1[1].lire_x(), liste_points1[1].lire_y());
  DrawDottedLine(liste_points1[1].lire_x() , liste_points1[1].lire_y(), liste_points1[2].lire_x(), liste_points1[2].lire_y());
  liste_points2.push_back(millieu(liste_points1[0],liste_points1[1]));
  liste_points2.push_back(millieu(liste_points1[1],liste_points1[2]));
  DrawDottedLine(liste_points2[0].lire_x(), liste_points2[0].lire_y(), liste_points2[1].lire_x(), liste_points2[1].lire_y());
  abcd = millieu(liste_points2[0],liste_points2[1]);
  dessiner_point(abcd, 4);
  //circleBres(centerX,centerY,10);
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
      bezier_negligeable(liste_point);
      faire_dessin(liste_point);
      bezierCurve(liste_point);
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
