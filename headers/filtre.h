//
//  filtre.h
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 11/04/2023.
//

#ifndef filtre_h
#define filtre_h

//importation de bibliothèques
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>
using namespace std;

class CMatrice; // déclaration préalable de la class CMatrice pour qu'elle puisse accéder aux données membres de la classe CFiltre

typedef int ftpe; // nom supplémentaire au type int

class CFiltre
{
private:
    int m_nO; // ordre de la matrice, elle est donc toujours carrée
    ftpe** m_pFiltre;
    
public:
    
    //constructeurs
    CFiltre (); //sans paramètres
    CFiltre(int, const char); // à paramètre entier et à chaîne de caractères pour une initialisation directe
    
    //destructeur
    ~CFiltre();
    
    //opérateur
    ftpe& operator() (int,int);
    friend class CMatrice; // pour pouvoir accéder aux membres de filtre depuis CMatrice
};
#endif /* filtre_h */
