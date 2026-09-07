//
//  matrice_int.cpp
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 14/04/2023.
//

#include "matrice_int.h"

// ================================== Constructeurs =======================================
CMatInt::CMatInt()
    :m_nLi(0),m_nCo(0),m_pMat(NULL) // aucun tableau créé, tous les nombres sont nuls
{
}

CMatInt::CMatInt (int nL, int nC)
    :m_nLi(nL),m_nCo(nC),m_pMat(NULL)
{
    
    if (m_nLi > 0) // éviter un bug en cas d'erreur
    {
       m_pMat = new itp* [m_nLi];
       if (m_pMat != NULL)
       {
           for (int i = 0; i < m_nLi; ++i)
           {
                   m_pMat[i] = new itp [m_nCo];
           }
       }
    }
    
    if (m_pMat != NULL)
    {
        for (int i = 0; i < m_nLi; ++i)
        {
            if (m_pMat[i] != NULL)
            {
                for (int j = 0; j < m_nCo; ++j)
                    m_pMat[i] [j] = 0;
            }
        }
    }
}

// ================================== Destructeur =======================================
CMatInt::~CMatInt()
{
    if (m_pMat != NULL)
    {
        for (int i = 0; i < m_nLi; ++i)
        {
            if (m_pMat[i] != NULL )
                delete [] m_pMat[i] ;
        }
        delete [] m_pMat;
    }
}

// ================================== Opérateurs =======================================

itp& CMatInt::operator () (int nL, int nC)
{
    return m_pMat [nL] [nC];
}

CMatInt CMatInt:: operator += (CMatInt& mat)
{
    if ((m_nLi == mat.m_nLi) && (m_nCo) == mat.m_nCo)
    {
        if ((m_pMat != NULL) && (mat.m_pMat != NULL))
        {
            for (int i = 0; i < mat.m_nLi; ++i)
            {
                if ((m_pMat[i] != NULL) && (mat.m_pMat[i] != NULL))
                {
                    for (int j = 0; j < mat.m_nCo; ++j)
                        (*this)(i,j) += mat(i,j);
                }
            }
        }
    }
    return (*this);
}

CMatInt CMatInt::operator +(CMatInt& mat)
{
    return CMatInt (*this) += mat;
}


// ================================== Méthodes =======================================

void CMatInt::Normaliser()
{
    int nMax = 0;
    int nMin = 0;

    if (m_pMat != NULL)
    {
        for (int i = 0; i < m_nLi; ++i)
        {
            if (m_pMat[i] != NULL)
            {
                for (int j = 0; j < m_nCo; ++j)
                {
                    // détermination des valeurs maximum et minimum de la matrice
                    if ( (i == 0) && j == 0)
                    {
                        nMax = (*this)(i,j);
                        nMin = (*this)(i,j);
                    }
                    else
                    {
                        if ((*this)(i,j) > nMax)
                            nMax = (*this)(i,j);
                        if ((*this)(i,j) < nMin)
                            nMin = (*this)(i,j);
                    }
                }
            }
        }
    }
    
    int nDelta = nMax - nMin;
    if (m_pMat != NULL)
    {
        for (int i = 0; i < m_nLi; ++i)
        {
            if (m_pMat[i] != NULL)
            {
                for (int j = 0; j < m_nCo; ++j)
                {
                    (*this) (i,j) = ((*this)(i,j)-nMin) * 255 / nDelta; // application de la formule de normalisation
                }
            }
        }
    }
}

void CMatInt::Affiche()
{
    if (m_pMat != NULL)
    {
        for (int i = 0; i < m_nLi; ++i)
        {
            if (m_pMat[i] != NULL)
            {
                for (int j = 0; j< m_nCo; ++j)
                {
                    cout <<  m_pMat[i][j];
                    
                    // pour harmoniser l'affichage de la matrice
                    if (m_pMat[i][j] >= 0)
                    {
                        if (m_pMat[i][j] < 10)
                            cout << "   ";
                        else if ( ( (int) m_pMat[i][j] >= 10) && ( (int) m_pMat[i][j] < 100) )
                            cout << "  ";
                        else if ((int) m_pMat[i][j] >= 10)
                            cout << " ";
                    } else if (m_pMat[i][j] < 0)
                    {
                        if (m_pMat[i][j] < 10)
                            cout << " ";
                        else if ( ( (int) m_pMat[i][j] >= 10) && ( (int) m_pMat[i][j] < 100) )
                            cout << " ";
                        else if ((int) m_pMat[i][j] >= 10)
                            cout << "  ";
                    }
                        
                }
                cout << endl;
            }
        }
    }
}
