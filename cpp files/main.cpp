#include "matrice.h"

void SaisieInt(int&, int, int);
void Lecture(char*, CMatrice&);

void Test(CMatrice&);
int main(void)
{
    setlocale(LC_ALL, "fr-FR");

    cout << "=================== FILTRE DE PREWITT - DETECTION DE CONTOURS ===================" << endl << endl;

    cout << "-- Comment souhaitez-vous entrer votre image ? --" << endl;
    cout << "1 - Emplacement du fichier (type chemin\\chemin\\image.csv)" << endl;
    cout << "2 - Entrée manuelle des pixels de la matrice" << endl;
    cout << "3 - Matrice aléatoire" << endl;
    cout << "4 - Mire aléatoire" << endl;
    cout << "0 - Arrêter le programme" << endl;
    cout << endl << "!!!!!!!!!!!!!!" << endl <<endl;
    cout << "ATTENTION: Seul le format.csv, séparé par des virgules est accepté. Si vous choisissez le 2, vérifiez bien que";
    cout << " les dimensions de l'image sont sur la première ligne (nombre de lignes puis nombre de colonnes)." << endl;
    cout <<endl<<"!!!!!!!!!!!!!!" << endl;

    int nR = 0;
    cout << endl <<"Saisissez votre réponse :";
    SaisieInt(nR, 0, 4);

    int nLg = 0;
    int nCnnes = 0;

    CMatrice Im;

    switch (nR)
    {
    case 0:
        exit(0); //sortir du programme sans erreur
        break;

    case 1:
        char pChemin[1024];
        cout << "Saisissez l'emplacement du fichier :";
        cin.ignore();
        cin.getline(pChemin, 1024); // on lit l'emplacement du fichier

        Lecture(pChemin, Im); //utilisation d'une fonction car sinon il y a une erreur de déclaration
        Test(Im);
        break;

    case 2:
        cin >> Im;
        Test(Im);
        break;

    case 3:
        nLg = 0;
        nCnnes = 0;

        cout << "Quel est le nombre de colonnes de la matrice ?";
        SaisieInt(nCnnes, 0, 1200);

        cout << "Quel est le nombre de lignes de la matrice ?";
        SaisieInt(nLg, 0, 1200);

        Im = CMatrice(nLg, nCnnes);

        cin.ignore(); //vider le buffer
        Test(Im);
        break;
    case 4:
        nLg = 0;
        nCnnes = 0;

        cout << "Quel est le nombre de colonnes de la matrice ?";
        SaisieInt(nCnnes, 0, 1200);

        cout << "Quel est le nombre de lignes de la matrice ?";
        SaisieInt(nLg, 0, 1200);

        Im = CMatrice(nLg, nCnnes);
        Im.Mire(nLg);
        Test(Im);
        break;
    default:
        break;
    }

   
    
    system("PAUSE");
}


void SaisieInt(int& nI,int nB1, int nB2)
{
    cin >> nI; // saisie de la réponse
    if ((nI < nB1) || (nI > nB2)) // vérification
    {
        do
        {
            cout << "Réponse incorrecte, veuillez réessayer :";
            cin >> nI;
        } while (((nI < nB1) || (nI > nB2)));
    }
}

void Lecture(char* pC, CMatrice& Im)
{
    ifstream fe(pC, ios::in);
    fe >> Im;
    fe.close();
}

void Test(CMatrice& Im)
{
    cout << endl << "==================";
    cout << endl << "Voulez-vous afficher la matrice ? Répondre o/n" << endl;
    
    cin.clear();
    char pRep = ' ';
    cin.get(pRep);
    if (pRep == 'o')
    {
        cout << endl << "********** Affichage de la matrice *********";
        cout << Im << endl; // affichage de la matrice

    }
    else if ((pRep != 'o') && (pRep != 'n'))
    {
 
        do
        {
            cout << "Réponse incorrecte, veuillez réessayer :" << endl;
            cin.get(pRep); // saisie des valeurs

        } while ((pRep != 'o') && (pRep != 'n'));

        if (pRep == 'o')
        {
            cout <<endl <<"********** Affichage de la matrice *********" << endl;
            cout << Im << endl;
        }
    }

    cout << "Voulez-vous afficher votre image ? Répondre o/n" << endl;
    cin.ignore();
    pRep = ' ';
    cin.get(pRep);
    if (pRep == 'o')
    {
        cout << endl <<" ---->L'image source se trouve en haut à droite. " << endl;
        Im.Image();

    }
    else if ((pRep != 'o') && (pRep != 'n'))
    {
        do
        {
            cout << "Réponse incorrecte, veuillez réessayer :" << endl;
            cin.get(pRep);

        } while ((pRep != 'o') && (pRep != 'n'));

        if (pRep == 'o')
        {
            cout << endl << " ---->  L'image source se trouve en haut à droite. " << endl ;
            Im.Image();
        }
    }

    cout << "----- Note : Les tableaux de contours horizontaux et verticaux seront enregistrés dans deux fichiers .csv dans le dossier";
    cout << " de la solution.----" << endl << endl;

    CMatrice Res = Im.ContourHorizontal("horizontal.csv") + Im.ContourVertical("vertical.csv");

    cin.ignore();
    cout << "Voulez-vous afficher l'image finale ? Répondre o/n" << endl;

    pRep = ' ';
    cin.get(pRep);
    if (pRep == 'o')
    {
        cout << endl << " ----> L'image convoluée se trouve en haut à droite. " << endl;
        Res.Image();
        cin.ignore();
    }
    else if ((pRep != 'o') && (pRep != 'n'))
    {
        do
        {
            cout << "Réponse incorrecte, veuillez réessayer :" << endl;
            cin.get(pRep);

            cin.ignore();
        } while ((pRep != 'o') && (pRep != 'n'));

        if (pRep == 'o')
        {
            cout << endl << " ----> L'image convoluée se trouve en haut à droite. " << endl;
            Res.Image();
            cin.ignore();
        }
    }
}