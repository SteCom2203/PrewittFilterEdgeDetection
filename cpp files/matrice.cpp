//
//  matrice.cpp
//  filtre de prewitt
//
//  Created by Steve AGBOKOU on 24/03/2023.
//

#include "matrice.h"

// ================================== Constructeurs =======================================
CMatrice::CMatrice()
    :m_nL(0),m_nC(0),m_pMatrice(NULL) // aucun tableau créé, tous les nombres rendus nuls
{
}

CMatrice::CMatrice (int nL, int nC)
    :m_nL(nL),m_nC(nC),m_pMatrice(NULL) // on ne crée pas de tableau avant vérification de l'odre
{
    
    if (m_nL > 0)
    {
       m_pMatrice = new tpe* [m_nL];
       if (m_pMatrice != NULL)
       {
           for (int i = 0; i < m_nL; ++i)
           {
                   m_pMatrice[i] = new tpe [m_nC];
           }
       }
    }
    
    if (m_pMatrice != NULL)
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if (m_pMatrice[i] != NULL)
            {
                for (int j = 0; j < m_nC; ++j)
                    m_pMatrice[i] [j] = (int) ((rand() /(double) RAND_MAX) * 256); // remplissage aléatoire avec des valeurs entre 0 et 255
            }
        }
    }
}

CMatrice::CMatrice(int nL, int nC, tpe** pMat)
    :m_nL(nL),m_nC(nC),m_pMatrice(NULL)
{
   if (m_nL > 0)
   {
       m_pMatrice = new tpe* [m_nL];
       if (m_pMatrice != NULL)
       {
           for (int i = 0; i < m_nL; ++i)
                m_pMatrice[i] = new tpe [m_nC];
       }
   }
    
    if ((m_pMatrice != NULL) && (pMat != NULL))
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if ( (m_pMatrice[i] != NULL) && (pMat[i] != NULL) )
            {
                for (int j = 0; j < m_nC; ++j)
                    m_pMatrice[i] [j] = pMat[i] [j];
            }
        }
    }
}


CMatrice::CMatrice(const CMatrice& mat)
    :m_nL(mat.m_nL),m_nC(mat.m_nC),m_pMatrice(NULL)
{
    if (m_nL > 0)
    {
       m_pMatrice = new tpe* [m_nL];
       if (m_pMatrice != NULL)
       {
           for (int i = 0; i < m_nL; ++i)
           {
                   m_pMatrice[i] = new tpe [m_nC];
           }
       }
    }
    
    if ( (mat.m_pMatrice != NULL) && (m_pMatrice != NULL) )
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if ( (mat.m_pMatrice[i] != NULL) && (m_pMatrice[i] != NULL) )
            {
                for (int j = 0; j < m_nC; ++j)
                    m_pMatrice[i][j] = mat.m_pMatrice[i][j] ;
            }
        }
    }
}

// ================================== Destructeur =======================================
CMatrice::~CMatrice()
{
    if (m_pMatrice != NULL) // vérification afin d'éviter de supprimer un tableau inexistant
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if (m_pMatrice[i] != NULL )
                delete [] m_pMatrice[i] ; // suppression des tableaux de tpe
        }
        delete [] m_pMatrice; // suppression du tableau contenant les tableaux de tpe
    }
}

// ================================== Opérateurs =======================================

// ---------------------------------- Opérateurs internes -------------------------------
CMatrice CMatrice::operator = (const CMatrice& mat)
{
    if (this != &mat) // pour éviter d'affecter une matrice à elle-même
    {
        if ((m_nL != mat.m_nL) || ((m_nL != mat.m_nL) && (mat.m_nC != m_nC)))
        {// nombre de colonnes ou ordre différents
            m_nL = mat.m_nL;
            if (m_pMatrice != NULL)
            {
                for (int i = 0; i < m_nL; ++i)
                {
                    if (m_pMatrice[i] != NULL )
                        delete [] m_pMatrice[i] ;
                }
                delete [] m_pMatrice;
            }
            
            
            m_pMatrice = new tpe* [m_nL];
            
            m_nC = mat.m_nC;
            
            if (m_pMatrice != NULL)
            {
                for (int i = 0; i < m_nL; ++i)
                    m_pMatrice[i] = new tpe [m_nC];
            }
            
        } else if ( (m_nL == mat.m_nL) && (m_nC != mat.m_nC))
        {//uniquement le nombre de lignes différent
            m_nC = mat.m_nC;
            
            if (m_pMatrice != NULL)
            {
                for (int i = 0; i < m_nL; ++i)
                {
                    if (m_pMatrice[i] != NULL )
                        delete [] m_pMatrice[i];
                }
                delete [] m_pMatrice;
            }
            
            
            if (m_pMatrice != NULL)
            {
                for (int i = 0; i < m_nL; ++i)
                    m_pMatrice[i] = new tpe [m_nC];
            }
        }
        
        if ( (mat.m_pMatrice != NULL) && (m_pMatrice != NULL) )
        {
            for (int i = 0; i < m_nL; ++i)
            {
                if ( (mat.m_pMatrice[i] != NULL) && (m_pMatrice[i] != NULL) )
                    for (int j = 0; j < m_nC; ++j)
                        m_pMatrice[i] [j] = mat.m_pMatrice[i][j] ;
            }
            
        }
        
    }
    
    return (*this);
}

CMatrice CMatrice::operator *= (const CMatrice& mat)
{
    CMatrice res(m_nC, mat.m_nL);
    if(m_nC == mat.m_nL)
    {
        
        if ((m_pMatrice != NULL) && (mat.m_pMatrice != NULL) )
        {
            int somme = 0;
            for (int i = 0; i < m_nL; ++i)
            {
                if ((m_pMatrice[i] != NULL) && (mat.m_pMatrice[i] != NULL))
                {
                    for (int j = 0; j < mat.m_nC; ++j)
                    {
                        for (int k = 0; k < m_nC; ++k)
                        {
                            somme += m_pMatrice[i] [k] * mat.m_pMatrice[k] [j];
                        }
                        res(i,j) = somme;
                        somme = 0;
                    }
                }
            }
        }
    }
    return res;
}

CMatrice CMatrice::operator * (const CMatrice& mat)
{
    return CMatrice (*this) *= mat;
}

CMatrice CMatrice::operator +(const CMatrice& mat)
{
    if ( (mat.m_nL == m_nL) && (mat.m_nC == m_nC) )
    {
        CMatInt add (m_nL, m_nC);
        if ( (m_pMatrice != NULL) && (mat.m_pMatrice != NULL) && (add.m_pMat != NULL))
        {
            for (int i = 0; i < m_nL; ++i)
            {
                if  ( (m_pMatrice[i] != NULL) && (mat.m_pMatrice[i] != NULL) && (add.m_pMat[i] != NULL))
                     for (int j = 0; j < m_nC; ++j)
                     {
                         add(i,j) = (int) mat.m_pMatrice[i] [j] + (int) m_pMatrice[i] [j];
                     }
            }
        }
        add.Normaliser();
        return CMatrice () = add;
    } else
        return CMatrice();

}

tpe& CMatrice::operator () (int nL, int nC) // l'opérateur & à la fin permet de pouvoir modifier la valeur
{
    return (m_pMatrice[nL][nC]);
}

// ---------------------------------- Opérateurs externes -------------------------------
CMatrice CMatrice::operator = (CMatInt& matint)
{
    if ( (m_nL != matint.m_nLi) || ((matint.m_nLi) && (matint.m_nCo != m_nC)))
    {
        m_nL = matint.m_nLi;
        if (m_pMatrice != NULL)
        {
            for (int i = 0; i < m_nL; ++i)
            {
                if (m_pMatrice[i] != NULL )
                    delete [] m_pMatrice[i] ;
            }
            delete [] m_pMatrice;
        }
        
        
        m_pMatrice = new tpe* [m_nL];
        
        m_nC = matint.m_nCo;
        
        if (m_pMatrice != NULL)
        {
            for (int i = 0; i < m_nL; ++i)
                m_pMatrice[i] = new tpe [m_nC];
        }
        
    } else if ( (m_nL == matint.m_nLi) && (m_nC != matint.m_nCo))
    {
        m_nC = matint.m_nCo;
        
        if (m_pMatrice != NULL)
        {
            for (int i = 0; i < m_nL; ++i)
            {
                if (m_pMatrice[i] != NULL )
                    delete [] m_pMatrice[i];
            }
            delete [] m_pMatrice;
        }
        
        
        if (m_pMatrice != NULL)
        {
            for (int i = 0; i < m_nL; ++i)
                m_pMatrice[i] = new tpe [m_nC];
        }
    }
    
    if ( (matint.m_pMat != NULL) && (m_pMatrice != NULL) )
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if ( (matint.m_pMat[i] != NULL) && (m_pMatrice[i] != NULL) )
                for (int j = 0; j < m_nC; ++j)
                {
                    if ( (matint(i,j) >= 0) && (matint(i,j) <= 255) )
                        m_pMatrice[i] [j] = matint(i,j) ;
                }
        }
    }
    
    return (*this);
}

CMatrice CMatrice::operator *= (CFiltre& f)
{
    CMatInt inter(m_nL, m_nC); // matrice à valeurs entières intermédiaires

    int nP = (f.m_nO + 1) / 2 - 1; // position du noyau (nP, nP) dans le filtre
    if ((f.m_pFiltre != NULL) && (inter.m_pMat != NULL))
    {
        for (int i = 0; i < inter.m_nLi; ++i) // lignes de la matrice résultat
        {
            if (m_pMatrice[i] != NULL)
            {
                for (int j = 0; j < m_nC; ++j) // colonnes de la matrice résultat
                {
                    for (int m = 0; m < nP + 1; ++m)
                    {
                        if (i == 0) // ligne du haut
                        {
                            // (i+nP) car on ne prend que les lignes du dessous
                            if ((j > 0) && (m != 0))
                            {
                                inter(i, j) += (int)(*this)(i + nP, j - m) * f(nP + nP, nP - m); //colonnes de gauche, ligne du bas
                                inter(i, j) += (int)(*this)(i, j - m) * f(nP, nP - m); // colonnes de gauche, ligne du coefficient
                            }
                            if ((j < m_nC - 1) || ((j == m_nC - 1) && m == 0))
                            {
                                inter(i, j) += (int)(*this)(i + nP, j + m) * f(nP + nP, nP + m);//colonnes de droite, ligne du bas
                                inter(i, j) += (int)(*this)(i, j + m) * f(nP, nP + m); //colonnes de droite, ligne du coefficient
                            }
                        }
                        else if ((j == 0) && (i + nP < m_nL)) //colonne extrême gauche
                        {
                            // on ne prend que les coefficients situés à droite

                            inter(i, j) += (int)(*this)(i, j + m) * f(nP, nP + m); //ligne du coefficient
                            if (i < (m_nL - 1))
                                inter(i, j) += (int)(*this)(i + nP, j + m) * f(nP + nP, nP + m); //ligne du bas
                            if ((i > 0))
                                inter(i, j) += (int)(*this)(i - nP, j + m) * f(nP - nP, nP + m); // ligne du haut
                        }
                        else if (j == m_nC - 1) // colonnes extrême droite && (i+nP < m_nL)
                        {
                            inter(i, j) += (int)(*this)(i, j - m) * f(nP, nP - m);
                            if (i <= (m_nL - 1))
                            {
                                if (i + 1 < m_nL) // on prend en charge le coefficient du coin bas droit
                                    inter(i, j) += (int)(*this)(i + nP, j - m) * f(nP + nP, nP - m); // ligne du bas
                                inter(i, j) += (int)(*this)(i - nP, j - m) * f(nP - nP, nP - m); // ligne du haut
                            }
                        }
                        else if (i == m_nL - 1) // ligne du bas
                        {
                            // on ne prend que les lignes du dessus
                            if ((j > 0) && (m != 0))// la colonne du milieu n'est prise qu'une seule fois)
                            {
                                inter(i, j) += (int)(*this)(i - nP, j - m) * f(nP - nP, nP - m);
                                inter(i, j) += (int)(*this)(i, j - m) * f(nP, nP - m);
                            }
                            if (j < (m_nC - 1))
                            {
                                inter(i, j) += (int)(*this)(i - nP, j + m) * f(nP - nP, nP + m);
                                inter(i, j) += (int)(*this)(i, j + m) * f(nP, nP + m);
                            }
                        }
                        else if ((i > 0) && (j > 0) && (j < m_nC) && (i < m_nL))
                        {
                            inter(i, j) += (*this)(i - nP, j - m) * f(nP - nP, nP - m); //ligne haute, colonnes gauche
                            if (m != 0) // pour éviter de prendre deux fois les coefficients de la colonne du milieu
                            {
                                inter(i, j) += (*this)(i - nP, j + m) * f(nP - nP, nP + m);//ligne haute, colonnes droites
                                inter(i, j) += (*this)(i + nP, j + m) * f(nP + nP, nP + m);//ligne basse, colonnes gauches
                            }
                            inter(i, j) += (*this)(i + nP, j - m) * f(nP + nP, nP - m); //ligne basse, colonnes droites

                            inter(i, j) += (int)(*this)(i, j + m) * f(nP, nP + m);//ligne du coefficient, colonnes droites
                            inter(i, j) += (int)(*this)(i, j - m) * f(nP, nP - m);//ligne du coefficient, colonnes gauches
                        }
                    }
                    inter(i, j) = abs(inter(i, j));  //valeur absolue car c'est la distance à zéro qui exprime le contour, pas le signe
                }
            }
        }
    }

    inter.Normaliser();
    (*this) = inter;
    return (*this);
}

CMatrice CMatrice::operator * (CFiltre& f)
{
    return CMatrice (*this) *= f;
} 


// ---------------------------------- Opérateurs de flux écran  -------------------------------

ostream& operator << (ostream& os, const CMatrice& mat) // flux sortant
{
    os << endl;
    if (mat.m_pMatrice != NULL)
    {
        for (int i = 0; i < mat.m_nL; ++i)
        {
            if (mat.m_pMatrice[i] != NULL)
            {
                for (int j = 0; j< mat.m_nC; ++j)
                {
                    os << (int) mat.m_pMatrice[i][j];
                    
                    // pour harmoniser l'affichage de la matrice
                    if ((int) mat.m_pMatrice[i][j] < 10)
                        os << "   ";
                    else if ( ( (int) mat.m_pMatrice[i][j] >= 10) && ( (int) mat.m_pMatrice[i][j] < 100) )
                        os << "  ";
                    else if ((int) mat.m_pMatrice[i][j] >= 10)
                        os << " ";
                        
                }
                os << endl;
            }
        }
    }
    return os;
}

istream& operator >> (istream& is , CMatrice& mat) // flux entrant
{
    cout << " * Saisie d'une matrice * " << endl;
    int nL = 0;
    do
    {
        cout << "Saisissez le nombre de lignes :";
        is >> nL;
    } while(nL < 0);
    
    int nC = 0;
    do
    {
        cout << "Saisissez le nombre de colonnes :";
        is >> nC;
    } while(nC < 0);
    
    
    if ( (nL != mat.m_nL) || ((nL != mat.m_nL) && (mat.m_nC != nC)) ) //nombre de lignes différentes ou tout différent
    {
        mat.m_nL = nL ;
        if (mat.m_pMatrice != NULL)
        {
            for (int i = 0; i < mat.m_nL; ++i)
            {
                if (mat.m_pMatrice[i] != NULL )
                    delete [] mat.m_pMatrice[i] ;
            }
            delete [] mat.m_pMatrice; //suppression de l'ancien tableau
        }
          
        mat.m_pMatrice = new tpe* [mat.m_nL]; //création d'un nouveau tableau
        
        mat.m_nC = nC;
        
        if (mat.m_pMatrice != NULL)
        {
            for (int i = 0; i < mat.m_nL; ++i)
                mat.m_pMatrice[i] = new tpe [mat.m_nC];
        }
        
    } else if ( (mat.m_nL == nL) && (nC != mat.m_nC))
    {
        mat.m_nC = nC;
        
        if (mat.m_pMatrice != NULL)
        {
            for (int i = 0; i < mat.m_nL; ++i)
            {
                if (mat.m_pMatrice[i] != NULL )
                    delete [] mat.m_pMatrice[i];
            }
            delete [] mat.m_pMatrice;
        }
        
        if (mat.m_pMatrice != NULL)
        {
            for (int i = 0; i < mat.m_nL; ++i)
                mat.m_pMatrice[i] = new tpe [mat.m_nC];
        }
    }

    if (mat.m_pMatrice != NULL)
    {
        string result = ""; // chaîne de caractère concaténable
        char pChar[3]; // chaîne de caractère permettant de récupérer des valeurs

       
        for (int i = 0; i < mat.m_nL; ++i)
        {

            if (mat.m_pMatrice[i] != NULL)
                for (int j = 0; j < mat.m_nC; ++j)
                {
                    cout << "Saisissez le coefficient de la " << i + 1 << "e ligne";
                    cout << " de la " << j + 1 << "e colonne :";
                    is.getline(pChar, 3); // on prend les valeurs saisies par l'utilisateur

                    for (int k = 0; k < strlen(pChar); ++k)
                        result += pChar[k]; // on concatène les valeurs de la chaîne de caractère

                    if (result != "") mat(i, j) = stoi(result); // on stocke le tout dans le coefficient correspondant pour la matrice

                    result = "";
                    is.ignore(); // nettoyer le buffer
                 
                }
        }
        
    }
    
    return is;
}

// ---------------------------------- Opérateurs de flux disque -------------------------------

ofstream& operator << (ofstream& ofs, CMatrice& mat) // flux sortant
{
    if (mat.m_pMatrice != NULL)
    {
        for (int i = 0; i < mat.m_nL; ++i)
        {
            if (mat.m_pMatrice[i] != NULL)
            {
                for (int j = 0; j< mat.m_nC; ++j)
                {
                    ofs << (int)mat(i,j) ;
                    if (j < (mat.m_nC -1)) ofs << ";"; // séparation par des points virgules à cause du format .csv
                }
            }
            ofs << endl;
        }
    }
    return ofs;
}

ifstream& operator >> (ifstream& ifs, CMatrice& mat)
{
    if (ifs) // vérifier que le fichier est ouvert
    {
        int nL = 0; // entrée du nombre de lignes

        int nC = 0; // entrée du nombre de colonnes

        char pChar[1024]; // chaîne de caractère qui stocke les données 
        ifs.getline(pChar, 1024); // on prend toute la ligne des valeurs de dimension

        string result = ""; // variable permettant de concaténer les valeurs de pChar

        int iterate = 0; //itérateur pour les boucles while

        while (pChar[iterate] != ';') // on prend les valeurs jusqu'au point virgule
        {
            result += pChar[iterate]; // concaténation
            ++iterate;
        }
        if (result != "") nL = stoi(result); // ces valeurs sont donc le nombre de lignes

        ++iterate; // on laisse tomber le point virgule
        result = "";

        while (iterate < strlen(pChar) - 1) // on prend les valeurs jusqu'à la fin de la chaîne
        {
            result += pChar[iterate]; // concaténation
            ++iterate;
        }
        if (result != "") nC = stoi(result);

        if ((nL != mat.m_nL) || ((nL != mat.m_nL) && (mat.m_nC != nC))) //nombre de lignes différentes ou tout différent
        {
            mat.m_nL = nL;
            if (mat.m_pMatrice != NULL)
            {
                for (int i = 0; i < mat.m_nL; ++i)
                {
                    if (mat.m_pMatrice[i] != NULL)
                        delete[] mat.m_pMatrice[i];
                }
                delete[] mat.m_pMatrice; //suppression de l'ancien tableau
            }


            mat.m_pMatrice = new tpe * [mat.m_nL]; // création d'un nouveau tableau

            mat.m_nC = nC;

            if (mat.m_pMatrice != NULL)
            {
                for (int i = 0; i < mat.m_nL; ++i)
                    mat.m_pMatrice[i] = new tpe[mat.m_nC];
            }
        }
        else if ((mat.m_nL == nL) && (nC != mat.m_nC)) // seules les colonnes sont différentes
        {
            mat.m_nC = nC;

            if (mat.m_pMatrice != NULL) // on vérifie que le tableau existe
            {
                for (int i = 0; i < mat.m_nL; ++i)
                {
                    if (mat.m_pMatrice[i] != NULL)
                        delete[] mat.m_pMatrice[i];
                }
                delete[] mat.m_pMatrice;
            }

            if (mat.m_pMatrice != NULL)
            {
                for (int i = 0; i < mat.m_nL; ++i)
                    mat.m_pMatrice[i] = new tpe[mat.m_nC];
            }
        }

        //ifs.ignore(); // nécessaire pour vider le buffer sous macOs

        if (mat.m_pMatrice != NULL)
        {
            for (int i = 0; i < mat.m_nL; ++i)
            {
                if (mat.m_pMatrice[i] != NULL)
                {
                    for (int j = 0; j < mat.m_nC; ++j)
                    {
                        if (j < mat.m_nC - 1)
                            ifs.getline(pChar, 1024, ';');
                        else
                            ifs.getline(pChar, 1024, '\n');
                
                        result = "";
                        for (int k = 0; k < strlen(pChar); ++k)
                        {
                            result = result + pChar[k]; // add character of the str1 into result
                        }
                        if (result != "")
                            mat(i, j) = stoi(result);
                    }
                }
            }
        }
    }
    return ifs;
}

void CMatrice::Mire(int nN)
{
    if (m_nC != nN) // changer les colonnes si la donnée membre est différente du paramètre
    {
        if (m_pMatrice != NULL)
        {
            for (int i = 0; i < m_nL; ++i)
            {
                if (m_pMatrice[i] != NULL)
                    delete[] m_pMatrice[i];
            }
            delete[] m_pMatrice;
        }

        m_pMatrice = new tpe * [m_nL];
        m_nC = nN;

    }

    if (m_pMatrice != NULL)
    {
        for (int i = 0; i < m_nL; ++i)
            m_pMatrice[i] = new tpe[m_nC];
    }

    int nCouleur = 0;
    if (nN > 0) nCouleur = floor(255 / (nN - 1)); // pour avoir un pas entre les valeurs

    if ((m_pMatrice != NULL))
    {
        for (int i = 0; i < m_nL; ++i)
        {
            if (m_pMatrice[i] != NULL)
            {
                for (int j = 0; j < m_nC; ++j)
                {
                    if (j == m_nC - 1)
                        m_pMatrice[i][j] = 255; // pour éviter les valeurs arrondies qui n'atteignent pas 255
                    else
                        m_pMatrice[i][j] = j * nCouleur;
                }
            }
        }

    }

}

void CMatrice::Image()
{
    COLORREF color(RGB(255, 255, 255));
    HWND hWND = GetConsoleWindow();
    HDC hDC = GetDC(hWND);

    SetConsoleTitle(TEXT("Polytech Orleans"));
    for (int j = 0; j < m_nL; j++)
    {
        for (int i = 0; i < m_nC; i++)
        {
            SetPixel(hDC, i, j, color);
        }
    }

    for (int j = 0; j < m_nL; j++)
    {
        for (int i = 0; i < m_nC; i++)
        {
            int nCouleur = (*this)(j, i);
            SetPixel(hDC, i, j, RGB(nCouleur, nCouleur, nCouleur));
        }
    }

    ReleaseDC(hWND, hDC);
    cin.ignore();
}


CMatrice CMatrice::ContourHorizontal(const char* pC)
{
    CFiltre H(3, 'x');
    CMatrice res(*this);
    res *= H;

    //sauvegarde du tableau sous Excel
    ofstream fs(pC, ios::out);
    fs << res;
    fs.close();
    
    return res;
}

CMatrice CMatrice::ContourVertical(const char* pC)
{
    CFiltre V(3, 'y');
    CMatrice res(*this);
    res *= V;

    //sauvegarde du tableau sous Excel
    ofstream fs(pC, ios::out);
    fs << res;
    fs.close();

    return res;
}