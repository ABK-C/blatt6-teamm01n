#include "Vektor.hh"
#include "Zylindermantel.hh"
#include "Vollzylinder.hh"
#include "Koerper.hh"
#include <iostream>
#include <memory>
#include <fstream>
#include <cmath>


std::ofstream fout("trägheit.txt");

double traegheit(Koerper* k, Vektor a , Vektor u) {

  const int N = 10000;
  double J = 0;
  //double m =  / N;
  for (int i = 0; i < N; ++i) {
    Vektor x = k->punkt();
    double r = (((x-a).Vektor::kreuz(u)).Vektor::betrag()) / (u.Vektor::betrag());
    J += r * r;
  }
  return J * k-> mass() / N;
}

std::unique_ptr<Koerper> Rechnen(double ZM_R, double ZM_L, double ZM_M, int i) {

  if (i==0) {std::unique_ptr<Koerper> k(new Zylindermantel(ZM_R, ZM_L, ZM_M)); return k;}
  if (i==1) {std::unique_ptr<Koerper> k(new Vollzylinder(ZM_R, ZM_L, ZM_M)); return k;}
}

//double J_an = ;

void Tabelle(std::unique_ptr<Koerper> k, Vektor a, Vektor u) {
  fout << k.get()-> mass() << " " << a << " " << u << " " << "|" << " " << (k.get()->analytisch() + (k.get()->mass()) * std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2)) << " " << traegheit(k.get(), a, u) << std::endl;
}

void Aufteilung(int i) {
  std::unique_ptr<Koerper> k(Rechnen(1, 1, 1, i));

  fout << "berechnet fuer " << k.get()-> name() << std::endl;

  Tabelle(Rechnen(1, 1, 1, i), Vektor(0,0,0), Vektor(0,0,1));
  Tabelle(Rechnen(1, 1, 2, i), Vektor(0,0,0), Vektor(0,0,1));
  Tabelle(Rechnen(2, 1, 1, i), Vektor(0,0,0), Vektor(0,0,1));
  Tabelle(Rechnen(1, 1, 1, i), Vektor(0,1,0), Vektor(0,0,1));
  Tabelle(Rechnen(1, 1, 2, i), Vektor(0,1,0), Vektor(0,0,1));
  Tabelle(Rechnen(2, 1, 1, i), Vektor(0,2,0), Vektor(0,0,1));

  fout << std::endl;
}


int main() {
  
  for (int i=0; i<2; ++i) {
    Aufteilung(i);
  }
  

  fout.close();

  return 0;

}

//Vektor a(0,0,0); // Punkt auf der Rotationsachse
  //Vektor u(0,0,1); // Richtung der Rotationsachse

  //alles(N,1,1,a,u,1);
  //alles(N,2,1,a,u,1);
  //alles(N,1,2,a,u,1);
  //a = Vektor(0,1,0);
  //alles(N,1,1,a,u,1);
  //alles(N,2,1,a,u,1);
  //a = Vektor(0,2,0);
  //alles(N,1,2,a,u,1);

//fout << ZM_R << " " << ZM_L << " " << ZM_M << " " << a << " " << u << " "
 //<< "|" << " " << JZMan << " " << J << " " << IVZan << " " << I << std::endl;

//double JZMan = (ZM_M * ZM_R * ZM_R) + (ZM_M * std::pow((((a).Vektor::kreuz(u)).Vektor::betrag() / u.Vektor::betrag()), 2));

//double I = 0;
  //m = M / N;
//int alles(double N, double M, double ZM_R, Vektor a, Vektor u, double ZM_L) {

  //std::unique_ptr<Zylindermantel> zm(new Zylindermantel(ZM_R, ZM_L));

  //double J = 0;     // Massentraegheitsmoment
  //double m = M / N; // Masse eines Massenpunktes
  //for (int i = 0; i < N; ++i) {
    //Vektor x = zm->punkt();
    // Abstand Punkt x und Gerade a + t*u
    // Vektor n = ...;//Normalenvektor x-a kreuz u
    //double r = (((x-a).Vektor::kreuz(u)).Vektor::betrag()) / (u.Vektor::betrag()); //|n|/|u|
    // std::cout << x << " :" << r << std::endl;
    // addiere Beitrag des Massenpunktes zum Traegheitsmoment
    //J += m * r * r;
  //}

  //const double M = 1;      // Masse des Zylindermantels
  //const double ZM_R = 1.0; // Radius der Zylindermantels
  //const double ZM_L = 1.0; // Laenge des Zylindermantels
  //std::cout << "Aufpunkt:";
  //std::cin >> a;
  
  //std::cout << "Richtung:";
  //std::cin >> u;

  //std::cout << "Massentraegheitsmoment fuer einen Zylindermantel"
            //<< " mit a = " << a << " und u = " << u << ": " << J << std::endl;
             