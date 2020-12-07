#include "coureur.hpp"
#include <cmath>
using namespace std;

//Constructor
coureur::coureur(){ //utilisation des nombres moyens
    nom = "anonyme";
    taille = 1.756;
    masse = 77.4; //kg
    poidsChaussures = 190; //grammes
    vitesseBase = 10; //km/h
    exVitesse = 10;
    hydra = 0;
    dParcourue = 0;
    dansEtape = 0;
    vitesseAct = 0;
    abandon = false;
    distanceOuDeshydra = -1;
    positionFinale = 0;
}
coureur::coureur(string mNom, float ma, float ta, float pc, float ex, float nb, float hy = 0, float d = 0, float mVact = 0){
    nom = mNom;
    taille = ta;
    masse = ma;
    poidsChaussures = pc;
    vitesseBase = ex;
    exVitesse = ex;
    nbSemainePrep = nb;
    hydra = hy;
    dParcourue = d;
    dansEtape = 0;
    vitesseAct = mVact;
    abandon = false;
    distanceOuDeshydra = -1;
    positionFinale = 0;
}

void coureur::print(){ //DEBUG
    cout << this->nom << endl;
    cout << "\t" << this->masse << endl;
    cout << "\t" << this->taille << endl;
    cout << "\thydra : " << this->hydra << endl;
}

string coureur::getNom(){
    return this->nom;
}

bool coureur::getAbandon(){
    return this->abandon;
}

float coureur::getStat(char c){
    if(c == 'v') return this->vitesseBase; //vitesse
    else if(c == 'd') return this->dParcourue; //distance
    else if(c == 'f') return this->vitesseAct;
    else if(c == 'h') return this->vitesseHydra;
    else return 0;
}

unsigned short coureur::getDansEtape(){
    return this->dansEtape;
}

unsigned short coureur::getPositionFinale(){
    return this->positionFinale;
}

void coureur::setDistance(float d){
    if(d > 0) this->dParcourue +=d;
    //if(d > this->dParcourue) this->dParcourue = d;
}

bool coureur::setEtape(unsigned short d){
    if(d > this->dansEtape){
         this->dansEtape = d;
         return true;
    }
    return false;
}

void coureur::setPositionFinale(unsigned short b){
    this->positionFinale = b;
}

bool coureur::setHydra(float distance){
    if(vitesseAct != 0) this->hydra = 0.5 * this->vitesseBase / distance;
    return true;
}

void coureur::setAbandon(){
    this->vitesseAct = 0;
    this->vitesseBase = 0;
    this->vitesseHydra = 0;
    this->abandon = true;
}

//TOCHECK W/ NEW STUFF
float coureur::impactHydra(float heures){ //renvoie la perte de capacité en %
    this->vitesseHydra = this->vitesseAct;
    if(this->abandon) return 0;
    float perte;
    float tmp = this->hydra / 0.5 * heures; //application de la formule
    if(tmp <= 0.4 && this->dParcourue - this->distanceOuDeshydra >= 2){ //abandon
        abandon = true;
        return 0;
    }
    else if( tmp <= 0.4 && this->distanceOuDeshydra <= 0) this->distanceOuDeshydra =  this->dParcourue;
    else this->distanceOuDeshydra = 0;
    //need to check if 0.4 for distance
    if(tmp <= 0.9 && tmp >= 0.4){ //verification des conditions énoncées
        /*on applique le tableau de proportionnalité suivant
        +-------------+-----+-----+-----+
        | hydratation | 0.4 | tmp | 0.9 |
        +-------------+-----+-----+-----+
        | pourcentage | 20% | ?%  | 1%  |
        +-------------+-----+-----+-----+   */
        perte = ((20 * tmp) / 0.4) * this->vitesseAct * pow(10, -2);
        this->vitesseHydra = this->vitesseAct - perte;
        return perte;
    }
    return 1;
}

void coureur::calculVitesseBase(){ //Chaussures, et TODO: chercher si autres
    float impactPoids = this->poidsChaussures / 100;
    if(impactPoids >= 1) this->vitesseBase-= this->vitesseBase*(1.1 * impactPoids) * pow(10, -2);
}

///TOCHECK
float coureur::calculVitesseEtape(float vitesseVent, float deniv = 0){
    if(this->abandon){
        this->vitesseBase = 0;
        this->vitesseAct = 0;
        return 0;
    }
    //impact vitesse vent:
    float pAir = 1.292;
    //ligne suivante inutilisé
    float ptMax = (0.5 * pAir * 0.137 * this->taille * (this->exVitesse / 3.6)) + (this->exVitesse / 3.6) * this->masse * 0.98;
    float pa = 0.5 * pAir * 0.137 * this->taille * ((this->vitesseBase / 3.6) * ((this->vitesseBase / 3.6) + pow(vitesseVent / 3.6, 2)));
    if(vitesseVent > 0) pa = -pa;
    float pr = ptMax - pa;
    //note, on remarquera la factorisation de la formule au dessus
    //float pt = pr + pa;
    this->vitesseAct = pr / (this->masse * 0.98) * 3.6;
    //CALCUL impact deniv:
    if(deniv >= 0){
        /*On utilise ce tableau de proportionnalité:
        +----------------+------+---------+
        | perte vitesse  |  1%  |   ?%   |
        +----------------+------+--------+
        | pente          | 1.5% | deniv |
        +----------------+------+-------+     */
        this->vitesseAct-= this->vitesseAct * (deniv / 1.5) * pow(10, -2);

    }
    else{
        /*On utilise ce tableau de proportionnalité:
        +---------------+-------+---------+
        | gain vitesse  | 0.35% |     ?% |
        +---------------+-------+--------+
        | pente         | 1.5%  | deniv |
        +---------------+-------+-------+     */
        this->vitesseAct+= this->vitesseAct * ((deniv * 0.35) / 1.5) * pow(10, -2);
    }
    return this->vitesseAct;
}

//l'impact des chaussures se calcule au début,
float coureur::calculVitesse(float heures){ //vitesse vent en m/s
    //calcul avec l'impact de l'hydratation
    if(impactHydra(heures) == 0){
        this->vitesseAct = 0;
        this->vitesseBase = 0;
        this->vitesseHydra = 0;
        abandon = true;
        return 0;
    }
    //calcul de l'impact de l'entrainement:
    float distanceLimite = 42.195 * this->nbSemainePrep / 16;
    if(distanceLimite <= dParcourue && this->nbSemainePrep < 16)
        /*pour connaitre la baisse:
        +------------------+--------+-----------------+
        |    distance:     | 42.195 | this->dParcourue |
        +------------------+--------+-----------------+
        | % de la vitesse: |     80 |    ?            |
        +------------------+--------+-----------------+*/
        this->vitesseHydra = this->vitesseHydra * ((this->dParcourue * 80) / 42.195) * pow(10, -2);
    if(this->vitesseHydra <= 6.5 || this->vitesseAct <= 6.5) this->setAbandon();
    return this->vitesseHydra;
}

void coureur::ravit(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(5, 8);
    int proba = distrib(gen);
    this->hydra+= 1 / proba;
    return;
}
