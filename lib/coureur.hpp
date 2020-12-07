#ifndef __COUREUR__
#define __COUREUR__
#include <iostream>
#include <string>
#include <random>
#include "etape.hpp"
class coureur{
    private:
        std::string nom; //logique
        float masse; //kg
        float taille; //m
        float poidsChaussures; //g
        float nbSemainePrep; //float pour plus de précision
        float hydra; //en L
        float distanceOuDeshydra; //verifier pour abandon
        float dParcourue; //en km
        unsigned short dansEtape; //pour savoir ou est le coureur
        float vitesseBase; //utile, on rentre l'ex vitesse moyenne à la base dedans
        float vitesseAct; //en km/h
        float vitesseHydra; //en km/h
        float exVitesse; //en km/h
        bool abandon;
        unsigned short positionFinale;
        //float dopage; //pourcentage
    public:
        coureur();
        coureur(std::string, float, float, float, float, float, float, float, float);
        //GETTER
        string getNom();
        float getStat(char);
        bool getAbandon();
        unsigned short getDansEtape();
        unsigned short getPositionFinale();
        //setter
        void setDistance(float);
        bool setEtape(unsigned short);
        void setPositionFinale(unsigned short);
        bool setHydra(float distance);
        void setAbandon();
        //debug
        void print();
        //Calcul Vitesse etc
        void calculVitesseBase(); //on l'execute seulement au début
        float calculVitesseEtape(float, float); //a executer à chaque changement d'étape
        float impactHydra(float); //utile dans le calcul en dessous
        float calculVitesse(float); //calcul permanant
        void ravit(); //TODO
};
#endif
