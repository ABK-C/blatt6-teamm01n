#include "Vektor.hh"
#include "Zylindermantel.hh"
#include "Vollzylinder.hh"
#include <iostream>
#include <memory>
#include <fstream>
#include <cmath>

std::ofstream fout("trägheit.txt");

int alles(double N, double M, double ZM_R, Vektor a, Vektor u, double ZM_L) {

  std::unique_ptr<Zylindermantel> zm(new Zylindermantel(ZM_R, ZM_L));

  double J = 0;     // Massentraegheitsmoment
  double m = M / N; // Masse eines Massenpunktes
  for (int i = 0; i < N; ++i) {
    Vektor x = zm->punkt();
    // Abstand Punkt x und Gerade a + t*u
    // Vektor n = ...;//Normalenvektor x-a kreuz u
    double r = (((x-a).Vektor::kreuz(u)).Vektor::betrag()) / (u.Vektor::betrag()); //|n|/|u|
    // std::cout << x << " :" << r << std::endl;
    // addiere Beitrag des Massenpunktes zum Traegheitsmoment
    J += m * r * r;
  }

    double JZMan = (M * ZM_R * ZM_R) + (M * std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2));

  std::unique_ptr<Vollzylinder> vz(new Vollzylinder(ZM_R, ZM_L));

  double I = 0;
  m = M / N;
  for (int i = 0; i < N; ++i) {
    Vektor x = vz->punkt();
    double r = (((x-a).Vektor::kreuz(u)).Vektor::betrag()) / (u.Vektor::betrag());
    I += m * r * r;
  }

    double IVZan = (M * ZM_R * ZM_R / 2) + (M * std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2));

 fout << ZM_R << " " << ZM_L << " " << M << " " << a << " " << u << " "
 << "|" << " " << JZMan << " " << J << " " << IVZan << " " << I << std::endl;
  
return 0;

}

int main() {

  const int N = 10000;     // Anzahl Integrationspunkte
  

  Vektor a(0,0,0); // Punkt auf der Rotationsachse
  Vektor u(0,0,1); // Richtung der Rotationsachse

  alles(N,1,1,a,u,1);
  alles(N,2,1,a,u,1);
  alles(N,1,2,a,u,1);
  a = Vektor(0,1,0);
  alles(N,1,1,a,u,1);
  alles(N,2,1,a,u,1);
  a = Vektor(0,2,0);
  alles(N,1,2,a,u,1);

  fout.close();

  return 0;

}


  //const double M = 1;      // Masse des Zylindermantels
  //const double ZM_R = 1.0; // Radius der Zylindermantels
  //const double ZM_L = 1.0; // Laenge des Zylindermantels
  //std::cout << "Aufpunkt:";
  //std::cin >> a;
  
  //std::cout << "Richtung:";
  //std::cin >> u;

  //std::cout << "Massentraegheitsmoment fuer einen Zylindermantel"
            //<< " mit a = " << a << " und u = " << u << ": " << J << std::endl;
             