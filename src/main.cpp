#include "../lib/coureur.hpp"
#include "../lib/etape.hpp"
#include "../lib/inOut.hpp"
#include <ctime>
#include <iomanip>
#include <SFML/Graphics.hpp>
#define C_FICHIERC false //lecture depuis fichier des coureurs, si false alors generation aleatoire
#define E_FICHIER false  //lecture depuis fichier des Etape, si false alors generation aleatoire
#define R_EXPORT true //exportation des fichiers sous /userfiles/resultats.txt

/* THINGS TO DO:
//TODO verifier l'hydra etc, mais normalement c'est enfin fix
//fix les couleurs des textes, lol
--------------------------------------------------------------------------
//mais en moins important
//ajouter classement dans les abandons
//TODO faire le readme

//NOTE:
//la generation aleatoire peut faire des parcours infaisables
//les coureurs peuvent être incapables de faire le marathon de base
*/

string printTime(string time){ //fun kilroy
    string result;
    result+= " __________\n";
    result+= "< " + time + " >\n";
    result+= " ----------\n";
    result+= "    \\\n";
    result+= "     \\\n";
    result+= "          ,,,\n";
    result+= "         (0 0)\n";
    result+= "  +---ooO-(_)-Ooo---+\n";
    result+= "  |                 |\n";
    return result;
}

int main(){
    //variables necessaires:
    vector<coureur> participants;
    vector<etapeParcours> etape;
    if(C_FICHIERC){
        if(!participantTxt("../userFiles/participants.txt", participants)) return -1; //le .. est necessaire pour aller chercher
    }
    else{
        if(!participantGen(12, participants)) return -1;
    }
    if(E_FICHIER){
        if(!sousEtapeTxt("../userFiles/Etape.txt", etape)) return -1;
    }
    else{
        if(!sousEtapeGen(50, etape)) return -1;
    }
    sf::Font font;
    if (!font.loadFromFile("../fonts/FiraCode-Light.ttf")) return EXIT_FAILURE;

    //Vrai prog, pas debug
    sf::RenderWindow marathon(sf::VideoMode(1080, 720), "La course");
    //calcul vbase
    parcours parc(etape, RandomFloat(0, 20), RandomFloat(0, 360));
    //0,5 * Vitesse_du_coureur (km/h)/5km
    for(vector<coureur>::iterator it = participants.begin(); it != participants.end(); ++it){
         it->calculVitesseBase();
         it->calculVitesseEtape(etape[0].getVitVent(parc.getData('v'), parc.getData('d')), etape[0].getDeniv());
         it->setHydra(etape[1].getDistance());
         //it->print(); //DEBUG
    }
    //DEBUG
    /*cout << "affichage des stats des etapes" << endl;
    int tmppp = 0;
    for(auto tmp = etape.begin(); tmp != etape.end(); ++tmp){
        cout << "etape " << tmppp << "{" << endl;
        tmp->print();
        cout << "}" << endl;
        ++tmppp;
    }*/
    //sf strings declaration
    sf::Clock stopwatch;
    sf::Clock dureDistance;
    sf::Text timer;
    timer.setFont(font);
    timer.setCharacterSize(12);
    timer.setFillColor(sf::Color(191, 201, 202));
    timer.setPosition(930, 585);
    sf::Text nom("", font, 12);
    nom.setFillColor(sf::Color(191, 201, 202));
    sf::Text vitesse("", font, 12);
    sf::Text distance("", font, 12);
    sf::Text statitisques1("vitesse actuelle: ", font, 12);
    statitisques1.setFillColor(sf::Color(191, 201, 202));
    sf::Text statitisques2(" km/h, distanceParcourue: ", font, 12);
    statitisques2.setFillColor(sf::Color(191, 201, 202));
    //creation de la palette de couleur
    int colorGetter;
    vector<sf::Color> couleurs = {
        sf::Color(46, 204, 113), //vert
        sf::Color(52, 152, 219), //bleu
        sf::Color(155, 89, 182), //violet
        sf::Color(211, 84, 0), //orange
        sf::Color(241, 196, 15) // jaune
    };
    //screen on!
    while (marathon.isOpen()){
        sf::Time elapsed = dureDistance.restart();
        marathon.clear(sf::Color(23, 32, 42));
        sf::Event event;
        while (marathon.pollEvent(event)){
            if (event.type == sf::Event::Closed) marathon.close();
        }
        //quand nouvelle étape: calcul propre
        timer.setString(printTime(getTime(stopwatch.getElapsedTime().asSeconds())));
        //tout le temps: calcul vitesse selon hydra et entrainement
        //float ratioX = 930 / participants.size();
        float ratioY = 700 / participants.size();
        for(unsigned int i = 0; i < participants.size(); ++i){
            colorGetter = i;
            if(participants[i].getStat('d') >= 42.195 && participants[i].getPositionFinale() == 0 && !participants[i].getAbandon()){
                participants[i].setDistance(42.195);
                //calcul de la position d'arrivée:
                unsigned short pos = 0;
                for(auto it = participants.begin(); it != participants.end(); ++it){
                    if(pos < it->getPositionFinale()) pos = it->getPositionFinale();
                }
                ++pos;
                participants[i].setPositionFinale(pos);
            }
            if(participants[i].getAbandon() || participants[i].getStat('d') < 42.195){
                //calcul vitesse du coureur de l'étape et etape dans laquelle il est
                for(unsigned short j = participants[i].getDansEtape() + 1; j < etape.size(); ++j){ //on itere entre l'étape dans laquelle est le coureur et le reste
                    if(participants[i].getStat('d') < etape[j].getDistance()){ //si le participant est
                        int zoof = j - 1;
                        unsigned int etapeActuelle;
                        if(zoof >= 0) etapeActuelle = zoof; //calcul de l'index de l'étape
                        else etapeActuelle = 0; //pour éviter des erreurs
                        if(participants[i].setEtape(etapeActuelle)){
                            //si le participant change d'étape alors on calcule sa vitesse de base pour cette etape
                            participants[i].calculVitesseEtape(parc.getEtape(participants[i].getDansEtape()).getVitVent(parc.getData('v'), parc.getData('d')), parc.getEtape(participants[i].getDansEtape()).getDeniv());
                            //et on le ravitaille si possible
                            if(etape[j].getRavit()) participants[i].ravit();
                            //on break car on en a fini pour ce participant
                        }
                        break;
                    }
                }
            }
            colorGetter+=participants[i].getDansEtape();
            colorGetter%=couleurs.size();
            //note changer le timer, et acceler la course on remplace le 3600 par un nombre plus petit, 3600 ici indique le temps reel.
            if(!(participants[i].getAbandon()) && participants[i].getStat('d') < 42.195){
                participants[i].calculVitesse((stopwatch.getElapsedTime().asSeconds()) / 3600);
                //calcul de la distance parcourue:
                participants[i].setDistance(participants[i].getStat('h') * elapsed.asSeconds() / 3600);
            }
            else participants[i].setAbandon();
            nom.setString(participants[i].getNom());
            stringstream vitesseStream;
            stringstream distanceStream;
            float vitesseTmp = participants[i].getStat('h');
            float distanceTmp = participants[i].getStat('d');
            vitesseStream << fixed << setprecision(2) << vitesseTmp;
            if(participants[i].getPositionFinale() != 0)
                distanceStream << "Arrive en "  << participants[i].getPositionFinale() << " eme position";
            else if(!participants[i].getAbandon())
                distanceStream << fixed << setprecision(3) << distanceTmp << " km et est dans l'etape " << participants[i].getDansEtape();
            else{ //abandon
                distanceStream.clear();
                distanceStream << "abandon, "<< participants[i].getNom() << " a abandonne au km " << fixed << setprecision(3) << distanceTmp << " dans l'etape " << participants[i].getDansEtape();
                participants[i].setPositionFinale(0);
            }
            //colors
            if(vitesseTmp <= 10) vitesse.setFillColor(sf::Color(236, 112, 99));
            else if(vitesseTmp > 10 && vitesseTmp < 20) vitesse.setFillColor(sf::Color(40, 180, 99));
            else vitesse.setFillColor(sf::Color(220, 118, 51));
            //ajout de la position
            nom.setPosition(5, ratioY * i);
            statitisques1.setPosition(5, ratioY * i + 40);
            statitisques2.setPosition(statitisques1.getLocalBounds().width + vitesse.getLocalBounds().width,ratioY * i + 40);
            //rectangle
            sf::RectangleShape rectangle;
            if(participants[i].getStat('d') < 42.195) rectangle.setSize(sf::Vector2f(participants[i].getStat('d') * 800 / 42.195, ratioY * 1/3));
            else rectangle.setSize(sf::Vector2f(800, ratioY * 1/3));
            rectangle.setPosition(0, ratioY * i + 20);
            rectangle.setFillColor(couleurs[colorGetter]);
            //Drawing
            vitesse.setString(vitesseStream.str());
            distance.setString(distanceStream.str());
            if(!participants[i].getAbandon()){
                vitesse.setPosition(statitisques1.getLocalBounds().width, ratioY * i + 40);
                distance.setPosition(statitisques1.getLocalBounds().width + vitesse.getLocalBounds().width + statitisques2.getLocalBounds().width ,ratioY * i + 40);
                if(participants[i].getPositionFinale() <= 0) marathon.draw(statitisques1);
                marathon.draw(statitisques2);
                marathon.draw(vitesse);
            }
            else{
                distance.setFillColor(sf::Color(236, 112, 99));
                distance.setPosition(5, ratioY * i + 40);
            }
            marathon.draw(nom);
            marathon.draw(distance);
            marathon.draw(rectangle);
        }
        //updating
        marathon.draw(timer);
        marathon.display();
    }
    //exportation
    if(R_EXPORT) exportR("../userFiles/resultats.txt", participants, etape);
    return 0;
}
