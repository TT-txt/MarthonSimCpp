#ifndef __InOut__
#define __InOut__
#include "coureur.hpp"
#include "etape.hpp"
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

float RandomFloat(float, float);
//recup' des coureurs via un txt;
bool participantTxt(const string &, vector<coureur> &);
//recup' des étapes
bool sousEtapeTxt(const string &, vector<etapeParcours> &);
//convert seconds to h:m:s
string getTime(float);
//generatation de participants random
bool participantGen(unsigned int , vector<coureur> &);
//generation etape
bool sousEtapeGen(unsigned int, vector<etapeParcours> &);
//export
void exportR(const string &, vector<coureur> &, vector<etapeParcours> &);
#endif
