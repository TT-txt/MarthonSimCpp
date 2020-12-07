#ifndef __ETAPE__
#define __ETAPE__

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

class etapeParcours{
    private:
        float deniv;
        float dist; //DISTANCE DEPUIS LE DEPART, ET ANNONCE LE DEBUT et en KM
        float direction; //
        bool aRavitaillement;
    public:
        etapeParcours(): deniv(0), dist(1000), direction(0), aRavitaillement(true) {}
        etapeParcours(float de, float di, float dir, bool ravit): deniv(de), dist(di), direction(dir), aRavitaillement(ravit) {}
        float getVitVent(float, float);
        float getDistance();
        float getDir();
        float getDeniv();
        bool getRavit();
        void print(); //debuging
};

class parcours{ //on considère les parcours complet
    private:
        vector<etapeParcours> parc;
        float vitVent; // m/s, de
        float directionVent; //nombre entre 0 et 360 °, il peut changer de maniere aleatoire
    public:
        parcours(): vitVent(0), directionVent(0) {}
        parcours(vector<etapeParcours> etapes, float vi, float dir): parc(etapes), vitVent(vi), directionVent(dir) {}
        void print(); //DEBUGING
        //getter
        etapeParcours getEtape(unsigned int);
        vector<etapeParcours> getParc();
        float getData(char c);
};


#endif
