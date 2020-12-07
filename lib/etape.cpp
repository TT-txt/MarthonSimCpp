#include "etape.hpp"
using namespace std;
//TODO
//lire étape depuis fichier
//utiliser étape internet?!!!

void etapeParcours::print(){
    cout << "\tdeniv: " << this->deniv << endl << "\tdistance: " << this->dist << endl << "\tdirection: " << this->direction << endl;
}

float etapeParcours::getDistance(){
    return this->dist;
}

float etapeParcours::getDeniv(){
    return this->deniv;
}

float etapeParcours::getDir(){
    return this->direction;
}

//obtention de la vitesse du vent
float etapeParcours::getVitVent(float vitesse, float dirVent = 0){
    if(vitesse <= 0) vitesse = abs(vitesse); //pour éviter erreurs
    srand(time(NULL));
    int probaVitesse = rand() % 6; // 1 chance sur 5 que le vent change de vitesse
    int probaDirection = rand() % 6; //1 chance sur 5 que le vent change de direction
    if(probaVitesse <= 4) vitesse = rand() % 20; // vitesse aléatoire entre 0 et 19 km/h
    if(probaDirection <= 4) dirVent = rand() / (RAND_MAX / 360); //direction aleatoire entre 0 et 359 degres
    //troncage de la direction
    if(dirVent > 360) dirVent = (int)dirVent % 360; //si la direction est trop grande on fait le tour
    /*On prend comme boussole
            0
            ^
            |
            |
270<--------|--------> 90
            |
            |
            |
           180
    L'angle tetha est l'angle absolu entre la direction du vent et la direction de l'étape; et on considere un vent perpendiculaire à l'étape comme nul
    on se retrouve donc avec le triangle:
     A      Avec la distance AC la norme du vent, et l'angle ACB l'angle entre la direction de l'étape et la direction du vent
    |\      Pour obtenir donc la vitesse du vent on fait donc AC*sin(ACB)
    | \
    |__\
    B    C
    */
    float tetha = abs(dirVent - this->direction);
    if(tetha <= 45) vitesse*=sin(tetha); //trigo pour vent de dos
    else if(tetha >= 225 && tetha <= 135) vitesse*=sin(abs(tetha-180)); //demi tour donc -vitesse
    else vitesse = 0; //si vitesse perpendiculaire, ou dans les perpendiculaires on la considere comme nulle
    return vitesse;
}

bool etapeParcours::getRavit(){
    return this->aRavitaillement;
}

etapeParcours parcours::getEtape(unsigned int i){
    if(i <= this->parc.size()) return parc[i];
    else exit(EXIT_FAILURE); //TOFIX
}

vector<etapeParcours> parcours::getParc(){
    return this->parc;
}

float parcours::getData(char c){
    if(c == 'v') return this->vitVent;
    else if(c == 'd') return this->directionVent;
    else return 0;
}
