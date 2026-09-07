//
//  matrice.h
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 24/03/2023.
//

#ifndef matrice_h
#define matrice_h


#include "matrice_int.h"

typedef unsigned char tpe; // nouveau nom pour le type unsigned char, pour facilement changer de type s'il le faut

class CMatrice
{
private:
    int m_nL;
    int m_nC;
    tpe** m_pMatrice;
    
public:
    
    //constructeurs
    CMatrice(); // constructeur sans paramètres
    CMatrice(int, int); // constructeur à initialisation aléatoire
    CMatrice(int, int, tpe**); // constructeur à initialisation avec tableau pour faire des tests plus facilement
    CMatrice(const CMatrice&);
    
    //destructeur
    ~CMatrice();
    
    //opérateurs internes
    CMatrice operator = (const CMatrice&); // affectation
    CMatrice operator *= (const CMatrice&);
    CMatrice operator * (const CMatrice&); // multiplication
    CMatrice operator + (const CMatrice&);
    
    tpe& operator () (int, int);

    //opérateurs externes
    CMatrice operator *= (CFiltre&); // pas de const car sinon l'opérateur () ne fonctionne plus
    CMatrice operator * (CFiltre&);
    CMatrice operator = (CMatInt&);
        
    //opérateurs de flux écran
    friend ostream& operator << (ostream&, const CMatrice&); // flux de sortie
    friend istream& operator >> (istream&, CMatrice&); // flux d'entrée
    
    //opérateurs de flux disque
    friend ofstream& operator << (ofstream&, CMatrice&); // flux de sortie
    friend ifstream& operator >> (ifstream&, CMatrice&); // flux d'entrée
    
    //méthodes
    CMatrice ContourHorizontal(const char* pC); // détection des contours horizontaux
    CMatrice ContourVertical(const char* pC); // détection des contours verticaux

    void Mire(int nN);
  
    void Image();
};

#endif /* matrice_h */
