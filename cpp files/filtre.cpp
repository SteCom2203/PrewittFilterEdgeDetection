//
//  filtre.cpp
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 11/04/2023.
//

#include "filtre.h"

// ================================== Constructeurs =======================================

CFiltre::CFiltre ()
    :m_nO(0),m_pFiltre(NULL)
{
    
}


CFiltre::CFiltre(int nO, const char cV) // à paramètre entier
    :m_nO(nO),m_pFiltre(NULL)
{
    if (m_nO > 0) // pour éviter des erreurs
        {
           m_pFiltre = new ftpe* [m_nO]; // création du tableau de tableaux d'entiers
           if (m_pFiltre != NULL)
           {
               for (int i = 0; i < m_nO; ++i)
               {
                       m_pFiltre[i] = new ftpe [m_nO]; // création des tableaux d'entiers
               }
           }
        }
        
        if (cV == 'x') // pour faciliter la création du filtre horizontal
        {
            if (m_pFiltre != NULL)
            {
                for (int i = 0; i < m_nO; ++i)
                {
                    if (m_pFiltre[i] != NULL)
                    {
                        for (int j = 0; j < m_nO; ++j)
                        {
                            if (i == 0)
                            {
                                m_pFiltre[i] [j] =  -1; // ligne du haut
                            } else if (i == 1)
                            {
                                m_pFiltre[i] [j]= 0; // ligne du milieu
                            } else if (i == 2)
                            {
                                m_pFiltre[i] [j] = 1; // ligne du bas
                            }
                        }
                    }
                }
            }
        } else if(cV == 'y')// pour faciliter la création du filtre vertical
        {
            if (m_pFiltre != NULL)
            {
                for (int i = 0; i < m_nO; ++i)
                {
                    if (m_pFiltre[i] != NULL)
                    {
                        for (int j = 0; j < m_nO; ++j)
                        {
                            if (j == 0)
                            {
                                m_pFiltre[i] [j] =  -1; // colonne gauche
                            } else if (j == 1)
                            {
                                m_pFiltre[i] [j]= 0; // colonne du milieu
                            } else if (j == 2)
                            {
                                m_pFiltre[i] [j] = 1; // colonne droite
                            }
                        }
                    }
                }
            }
        }
}
    
// ================================== Destructeur =======================================

CFiltre::~CFiltre()
{
    if (m_pFiltre != NULL) // pour éviter de supprimer un tableau inexistant
    {
        for (int i = 0; i < m_nO; ++i)
        {
            if (m_pFiltre[i] != NULL ) // pour éviter de supprimer un tableau inexistant
                delete [] m_pFiltre[i] ;
        }
        delete [] m_pFiltre;
    }
}

// ================================== Opérateur =======================================
ftpe& CFiltre::operator () (int i, int j)
{
    return m_pFiltre [i] [j];
}

