//
//  matrice_int.h
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 14/04/2023.
//

#ifndef matrice_int_h
#define matrice_int_h

#include "filtre.h"
typedef int itp; // nouveau nom pour le type int lié à la classe CMatInt

class CMatInt
{
private:
    int m_nLi; // lignes
    int m_nCo;// colonnes
    itp** m_pMat;
    
public:
    //constructeurs
    CMatInt(); // constructeur sans paramètres
    CMatInt(int, int);// constructeur à paramètres
    CMatInt(const CMatrice&); // constructeur copie
    
    //destructeur
    ~CMatInt();
    
    //opérateurs
    itp& operator () (int, int);
    CMatInt operator += (CMatInt&);
    CMatInt operator + (CMatInt&);//opérateur d'addition
    void Affiche(); // pour afficher la matrice (utile seulement pour les tests)
    
    //méthodes
    void Normaliser();
    friend class CMatrice; // pour que la classe CMatrice aie accès aux données membres
    
};
#endif /* matrice_int_h */
