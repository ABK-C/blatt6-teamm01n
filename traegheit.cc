#include "Vektor.hh"
#include "Zylindermantel.hh"
#include "Vollzylinder.hh"
#include <iostream>
#include <memory>
#include <fstream>
#include <cmath>

std::ofstream fout("trägheit.txt");

//int trägheit(int N, double M, double ZM_R, double ZM_L = 1, Vektor a, Vektor u) {

int main() {
  const int N = 10000;     // Anzahl Integrationspunkte
  const double M = 1;      // Masse des Zylindermantels
  const double ZM_R = 1.0; // Radius der Zylindermantels
  const double ZM_L = 1.0; // Laenge des Zylindermantels

  Vektor a(0,0,0);
  Vektor u(0,0,1);

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

  std::unique_ptr<Vollzylinder> vz(new Vollzylinder(ZM_R, ZM_L));

  double I = 0;
  for (int i = 0; 1 < N; ++i) {
    Vektor x = vz->punkt();
    double r = (((x-a).Vektor::kreuz(u)).Vektor::betrag()) / (u.Vektor::betrag());
    I += m * r * r;
  }

   double JZMan = M * (ZM_R * ZM_R + std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2));

   double JVZan = M * (ZM_R * ZM_R / 2 + std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2));

fout << ZM_R << " " << ZM_L << " " << M << " " << a << " " << u << " "
 << "|" << " " << JZMan << " " << J << " " << JVZan << " " << I << std::endl;

 return 0;
  
}

//}
//Vektor a; // Punkt auf der Rotationsachse
  //std::cout << "Aufpunkt:";
  //std::cin >> a;
  //Vektor u; // Richtung der Rotationsachse
  //std::cout << "Richtung:";
  //std::cin >> u;

  //std::cout << "Massentraegheitsmoment fuer einen Zylindermantel"
            //<< " mit a = " << a << " und u = " << u << ": " << J << std::endl;
             