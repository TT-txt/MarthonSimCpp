#include "inOut.hpp"

using namespace std;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//CHECKING INPUTS IN TXT

bool participantTxt(const string &filename, vector<coureur> &retour){
    ifstream file(filename);
    string line;
    if(!file.is_open()){
        cout << "ERREUR DE FICHIER COUREURS";
        return false;
    }
    string mNom;
    float mMasse, mTaille, mPoidsChaussures, mExVMoyenne, mNbSemainePrep;
    int i = 0; //counting infos
    //alors, oui c'est moche mais bon je sais déjà pas comment j'ai réussi à faire fonctionner ça donc je m'en contente
    while (getline(file, line)){
        if(line[0] == '{' || line[0] == '}'){
            i = 0;
            continue;
        }
        switch (i) {
            case 0:
                mNom.clear(); //resoud des problèmes
                //alors, on pourrait utiliser les fonctions de algorithm, mais elles marchent pas, donc pas envie
                for(string::iterator it = line.begin(); it != line.end(); ++it){
                    if(*it != ' ') mNom.push_back(*it);
                }
                ++i;
                break;
            case 1:
                mMasse = stof(line);
                ++i;
                break;
            case 2:
                mTaille = stof(line);
                ++i;
                break;
            case 3:
                mPoidsChaussures = stof(line);
                ++i;
                break;
            case 4:
                mExVMoyenne = stof(line);
                ++i;
                break;
            case 5:
                mNbSemainePrep = stof(line);
                i = 0;
                coureur *aled = new coureur(mNom, mMasse, mTaille, mPoidsChaussures, mExVMoyenne, mNbSemainePrep, 0, 0, 0);
                retour.push_back(*aled);
                break;
        }
    }
    file.close();
    return true;
}
//recup' des étapes
bool sousEtapeTxt(const string &filename, vector<etapeParcours> &etapes){
    ifstream file(filename);
    string line;
    if(!file.is_open()){
        cout << "ERREUR DE FICHIER ETAPE";
        return false;
    }
    float deniv, dist, direction;
    bool ravit;
    int i = 0; //counting infos
    //alors, oui c'est encore moche mais bon je sais déjà pas comment j'ai réussi à faire fonctionner ça donc je m'en contente
    while (getline(file, line)){
        if(line[0] == '{' || line[0] == '}'){
            i = 0;
            continue;
        }
        switch (i) {
            case 0:
                deniv = stof(line);
                ++i;
                break;
            case 1:
                dist = stof(line);
                ++i;
                break;
            case 2:
                direction = stof(line);
                ++i;
                break;
            case 3:
                ravit = stoi(line);
                i = 0;
                etapeParcours *etape = new etapeParcours(deniv, dist, direction, ravit);
                etapes.push_back(*etape);
                break;
        }
    }
    sort(etapes.begin(), etapes.end(), [](etapeParcours &e1, etapeParcours &e2){
        return e1.getDistance() - e2.getDistance();
    });
    file.close();
    return true;
}

string getTime(float seconds){
    if(seconds < 0) return "Erreur";
    string retour = "";
    string sS, sM, sH;
    int s = (int) seconds;
    int m = seconds / 60;
    int h = m / 60;
    m = (int) m % 60;
    s = (int) s % 60;
    if(s == 0) sS = "00";
    else if(s < 10) sS = "0" + to_string(s);
    else sS = to_string(s);
    if(m == 0) sM = "00";
    else if(m < 10) sM = "0" + to_string(m);
    else sM = to_string(m);
    if(h == 0) sH = "00";
    else if(h < 10) sH = "0" + to_string(h);
    else sH = to_string(h);
    retour += sH + ":" + sM + ":" + sS;
    return retour;
}

bool participantGen(unsigned int nbParticipant, vector<coureur> &liste){
    vector<string> names = {
        "Louis", "Hugo", "Samuel", "Eloise", "Adelie", "Gabriel", "Manon", "Max", "Michael", "Json", "Jason", "Cecile", "Camille", "Axel", "Petunia", "Axel", "Karim", "Nathalie","Megumin","Martin","Adel","Ines","Emma",
        "Louis","Pierre","Chloé","Antoine","Colin","Maxence","Pascal","Vivien"
        ,"Lyes","Valentin","Quentin", "Ivan" ,"Nikolai", "Boris", "Vladimir",
        "Pyotr", "Alexei", "Dmitri", "Sergei", "Viktor", "Roman", "Igor","Mikhail",
        "Vasily", "Pavel", "Fyodor", "Nikita", "Valery","Vladislav", "Leonid", "Maxim",
        "Yuri","Oleg", "Andrei", "Konstantin" ,"Vyacheslav" ,"Aleksandr", "Stanislav",
        "Anatoli" ,"Miroslav" ,"Artyom" ,"Bogdan", "Branislav", "Ilya", "Jaroslav",
        "Radomir", "Kirill", "Radoslav" ,"Lubomir", "Ratimir","Yegor", "Faraji", "Imamu"
        , "Jelani", "Jengo", "Jumaane", "Khamisi", "Kibwe", "Mosi", "Mwenye", "Sefu",
        "Simba", "Tendaji", "Zuberi", "Abasi", "Annan", "Azizi","Badru","Bakari","Bwana"
        , "Chane", "Chuma", "Enzi", "Faraji", "Hanisi", "Idi", "Issa", "Jabari", "Akani"
        , "Aluwanip", "Ayanda", "Bambanani", "Bheka", "Bhekithemba", "Bhekizizwe",
        "Butholezwe", "Dikotsi", "Dzingai", "Esaia", "Hangwani", "Humbe", "Kabelo",
        "Khathu", "Khumbu", "Kutlwano", "Kwanele", "Lentswe", "Lesebo", "Letswalo",
        "Lutendo", "Mahlubandile", "Makalo", "Mareka", "Masingita", "Moeketsi", "Molapo"
        , "Mosemotsane", "Motlalentwa", "Mothusi", "Msizi", "Mzwamadoda", "Nthofeela",
        "Oagile", "Paseka", "Phahamo", "Poloko", "Qukeza", "Refilwe", "Sanele", "S'bu",
        "Sehlolo", "Sekgolokhane", "Sibusiso", "Sizwe", "Teboho", "Thabiso", "Themba",
        "Thuso", "Tsebo", "T'sehla", "Tshawe", "Unathi", "Wandile", "Mbutu", "Kofi",
        "Asha", "Abla", "Adhra", "Adila", "Aeeshah", "Afiya", "Chausiku", "Eshe",
        "Furaha", "Imani", "Kamaria", "Marjani", "Mchumba", "Mwanajuma", "Nia", "Nuru",
        "Sanaa", "Sauda", "Subira", "Zuri", "Aizivaishe", "Anatswanashe", "Anodiwa",
        "Anokosha", "Awande", "Bokang", "Bongani", "Dikeledi", "Edzai", "Fikile", "Gugu"
        , "Kagiso", "Keneuwe", "Koketso", "Langalibalele", "Lerato", "Lindidwe",
        "Litsoanelo", "Lulama", "Majobo", "Maletsatsi", "Matshediso", "Mbali", "Mmaabo",
        "Mncedisi", "Mohau", "Moratuoa", "Muambiwa", "Nnyadzeni", "Nofoto", "Nthati",
        "Ntsebo", "Ntswaki", "Phathu", "Reneilwe", "Rudzani", "Shandu", "Sinethemba",
        "Sizani", "Thanduxolo", "Tshanduko", "Tungu", "Zinhle", "Anna", "Yelena",
        "Olga", "Oksana", "Tatyana", "Svetlana", "Nadya", "Yekaterina", "Irina",
        "Galina", "Miroslava", "Anastasia", "Vera", "Polina", "Lyudmila", "Elena",
        "Marina", "Darya", "Irma", "Ksenia", "Alexandra", "Nadesja", "Valentina",
        "Arina", "Alya", "Galenka", "Katya", "Ljuba", "Radmila", "Natacha", "Vlada",
        "Nadezhda", "Tatiana", "Sonia", "Mira", "Philippe", "Jean-Marie",
        "Marcel", "Francois", "Hubert", "Paul", "Michel", "Henri", "Marc",
        "Jean", "Maurice", "René", "Claude", "Yves", "Jacques", "Simon", "Olivier",
        "Joseph", "Robert", "Georges", "André", "Raymond", "Gaston", "Charles",
        "Thierry", "Guy", "Patrice", "Mathieu", "Jean-Francois", "Lucien", "Jean-Paul",
        "Daniel", "Thibault", "Luc", "Dominic", "Sébastien", "Hugo", "Manon",
        "Camille", "Clara", "Juliette", "Clémence", "Jeanne", "Charlotte",
        "Marie", "Nina", "Julia", "Elise", "Justine", "Yasmine", "Elina", "Andrea",
        "Eleonore", "Clarisse", "Fanny", "Selma", "Leila", "Veronique", "Sophie",
        "Helena", "Daphne", "Suzanne", "Melanie", "Bernadette", "Maud", "Angeline",
        "Celine", "Jessica", "Pauline", "Viviane", "Jeanette", "Bernard",
        "Dubois", "Durand", "Leroy", "Moreau", "Lambert", "Dupont", "Leclerc",
        "Laurent", "Renard", "Tremblay", "Gagnon", "Roy", "Bouchard", "Gauthier",
        "Morin", "Lavoie", "Fortin", "Gagne", "Duval", "Hébert", "Deville", "Gerard",
        "Duchaine", "Jauvin", "Gilbert", "Bergeron", "Paquette", "Pelletier", "Rémy"
        ,"Giroud", "Bosquet", "Lebouef", "Péllissier", "Deveraux", "Le Gall", "Le Roux",
        "de Castelnau", "de Montaignac", "John", "Brian", "Peter", "Adam", "James",
        "William", "Jacob", "Christopher", "Joshua", "Michael", "Ethan", "Joseph",
        "Matthew", "Anthony", "Daniel", "Ryan", "Samuel", "Kevin", "David", "Logan",
        "Carter", "Benjamin", "Andrew", "Henry", "Nicholas", "Gavin", "Owen", "Jack",
        "Wyatt", "Wayne", "Walter", "Charles", "Merritt", "Earl", "Alfred",
        "Vernon", "Edward", "Donald", "George", "Greg", "Thomas", "Robert",
        "Gene", "Glen", "Hugh", "Ronald", "Francis", "Stephen", "Jon", "Richard",
        "Mark", "Marcus", "Scott", "Duncan", "Douglas", "Keith", "Howard", "Russell",
        "Clayton", "Lee", "Steve", "Tom", "Clay", "Oliver", "Kenneth", "Ralph", "Andy"
        , "Tony", "Tyrone", "Lawrence", "Patrick", "Harry", "Alan", "Eugene", "Frank"
        , "Craig", "Jason", "Jonathan", "Harrison", "Connor", "Gaylord",
        "Sean", "Cooper", "Stanley", "Calhoun", "Neil", "Jeffrey", "Harold", "Raymond"
        , "Fred", "Marshall", "Silas", "Roy", "Jesse", "Ken", "Bruce", "Norris",
        "Horatio", "Clarence", "Lloyd", "Duane", "Mortimer", "Ben", "Ernest",
        "Warren", "Graham", "Marvin", "Orson", "Dennis", "Jackson", "Dwight", "Harlan",
        "Arthur", "Percival", "Montgomery", "Clyde", "Rodney", "Gerald",
        "Franklin", "Jake", "Horace", "Irving", "Seth", "Randolph", "Floyd", "Carl",
        "Brent", "Cliff", "Malcolm", "Timothy", "Wallace", "Pierce", "Edmund",
        "Gary", "Tony", "Nathan", "Eric", "Albert", "Robin", "Geoffrey", "Larry",
        "Ian", "Leonard", "Gordon", "Derek", "Maxwell", "Alec", "Bernard", "Stuart",
        "Rupert", "Dean", "Philip", "Ross", "Darren", "Melvin", "Justin",
        "Zack", "Elliot", "Simon", "Morgan", "Clark", "Xavier", "Jared", "Edgar",
        "Crispin", "Nelson", "Emmett", "Trevor", "Travis", "Lance", "Adrian",
        "Desmond", "Brendan", "Brett", "Ambrose", "Basil", "Kieran", "Conan",
        "Dermot", "Dudley", "Felix", "Finn", "Oscar", "Sidney", "Aaron", "Vincent",
        "Angus", "Grant", "Luke", "Miles", "Morton", "Randall", "Reginald",
        "Herbert", "Wesley", "Nigel", "Alexander", "Dominic", "Bradley", "Olivia",
        "Emily", "Sophie", "Jessica", "Alice", "Scarlett", "Daisy", "Eve"
        , "Phoebe", "Sienna", "Anna", "Mary", "Megan", "Elizabeth", "Amy", "Darcy",
        "Matilda", "Erin", "Lucy", "Grace", "Evelyn", "Amber", "Harriet", "Caitlyn",
        "Jasmine", "Madison", "Kate", "Eleanor", "Alexandra", "Sarah", "Martha",
        "Bethany", "Rebecca", "Victoria", "Gabriella", "Naomi", "Lauren", "Clara","Laura", "Kayla", "Nicole", "Skye", "Eliza", "Patricia", "Linda", "Barbara","Jennifer", "Maria","Susan", "Margaret", "Dorothy", "Lisa", "Nancy", "Helen","Sandra","Donna", "Carol", "Ruth", "Sharon", "Michelle", "Kimberly", "Deborah","Amelia", "Charlotte", "Isabella", "Ruby", "Addison", "Alyssa", "Abigail","Julia", "Samantha", "Brooklyn", "Ashley", "Natalie", "Brianna", "Hailey","Lillian", "Judith", "Alison",    "Amanda","Angela","Audrey","Beatrice","Brenda", "Bridget", "Caroline", "Cassandra","Charity", "Cecilia", "Anne","Clarissa", "Christabel", "Cheryl", "Cynthia","Cadence", "Cordelia", "Daphne","Deanna", "Denise", "Dolores", "Doreen","Drusilia", "Edith", "Edna","Eleonor", "Eileen", "Edwina", "Ellen", "Estelle","Ethel", "Felicity","Fiona", "Genevieve", "Gertie", "Gwen", "Gwendolyn","Henrietta", "Imogen","Iris", "Imelda", "Jacqueline", "Jane","Jenna","Joanna","Josephine","Julianne",   "Kathleen","Kierra","Kaylee", "Leah", "Lois"
    };
    if(nbParticipant == 0 || nbParticipant > names.size()) return false;
    srand(time(NULL));
    for(unsigned int i = 0; i < nbParticipant; ++i){
        coureur *aled = new coureur(names[i], RandomFloat(45, 120), RandomFloat(1.3, 2), RandomFloat(100, 300), RandomFloat(8, 20), RandomFloat(8, 16), 0, 0, 0);
        liste.push_back(*aled);
    }
    return true;
}

bool sousEtapeGen(unsigned int nbEtapes, vector<etapeParcours> &result){
    if(nbEtapes == 0) return false;
    float ratio = 42.195 / nbEtapes;
    for(unsigned int count = 0; count < nbEtapes; ++count){
        etapeParcours *tmp = new etapeParcours(RandomFloat(-10, 10), count * ratio, RandomFloat(0, 360), true);
        result.push_back(*tmp);
    }
    return true;
}

void exportR(const string &filename, vector<coureur> &participants, vector<etapeParcours> &etapes){//exportation des fichiers
    ofstream outputs;
    outputs.open(filename);
    if(!outputs.is_open()){
        cout << "ERREUR DE FICHIER ETAPE";
    }
    //ascii art
    outputs << "---------------------------------------------------------------------------" << endl;
    outputs << "d8888b. d88888b .d8888. db    db db      d888888b  .d8b.  d888888b .d8888. " << endl;
    outputs << "88  `8D 88'     88'  YP 88    88 88      `~~88~~' d8' `8b `~~88~~' 88'  YP " << endl;
    outputs << "88oobY' 88ooooo `8bo.   88    88 88         88    88ooo88    88    `8bo.   " << endl;
    outputs << "88`8b   88~~~~~   `Y8b. 88    88 88         88    88~~~88    88      `Y8b. " << endl;
    outputs << "88 `88. 88.     db   8D 88b  d88 88booo.    88    88   88    88    db   8D " << endl;
    outputs << "88   YD Y88888P `8888Y' ~Y8888P' Y88888P    YP    YP   YP    YP    `8888Y' " << endl;
    outputs << "---------------------------------------------------------------------------" << endl << endl;
    outputs << "---------------------------------------------------------------------------" << endl;
    sort(participants.begin(), participants.end(), [](coureur &e1, coureur &e2){
        return e1.getPositionFinale() - e2.getPositionFinale();
    });
    for(vector<coureur>::iterator it = participants.begin(); it != participants.end(); ++it){
        stringstream position;
        if(it->getPositionFinale() == 0) position << "a abandonne au km" << it->getStat('d');
        else position << it->getPositionFinale();
        outputs << "Nom: " << it->getNom() << endl << "\tposition: " << position.str() << endl;
    }
    outputs << "---------------------------------------------------------------------------" << endl << endl;
    outputs << "8888888b.                                                             888               888                                     " << endl;
    outputs << "888   Y88b                                                            888               888                                     " << endl;
    outputs << "888    888                                                            888               888                                     " << endl;
    outputs << "888   d88P .d88b.  .d8888b  888  888 88888b.d88b.   .d88b.        .d88888 888  888      888888 888d888 8888b.   .d8888b .d88b.  " << endl;
    outputs << "8888888P\" d8P  Y8b 88K      888  888 888 \"888 \"88b d8P  Y8b      d88\" 888 888  888      888    888P\"      \"88b d88P\"   d8P  Y8b " << endl;
    outputs << "888 T88b  88888888 \"Y8888b. 888  888 888  888  888 88888888      888  888 888  888      888    888    .d888888 888     88888888 " << endl;
    outputs << "888  T88b Y8b.          X88 Y88b 888 888  888  888 Y8b.          Y88b 888 Y88b 888      Y88b.  888    888  888 Y88b.   Y8b.     " << endl;
    outputs << "888   T88b \"Y8888   88888P\'  \"Y88888 888  888  888  \"Y8888        \"Y88888  \"Y88888       \"Y888 888    \"Y888888  \"Y8888P \"Y8888  " << endl;
    outputs << "---------------------------------------------------------------------------" << endl << endl;
    unsigned short count = 0;
    for(vector<etapeParcours>::iterator it = etapes.begin(); it != etapes.end(); ++it){
        outputs << "etape " << count << "{" << endl;
        outputs << "\tdeniv: " << it->getDeniv() << endl << "\tdistance: " << it->getDistance() << endl << "\tdirection: " << it->getDir() << endl;
        outputs << "}" << endl;
        ++count;
    }
}
