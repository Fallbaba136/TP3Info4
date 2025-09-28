#include <iostream>
#include <string>
using namespace std;

//CONSTRUCTION D'UN ARBRE

struct noeud
{
    string nom;
    int nbr_fils;
    noeud** tab;
};
void createArbre(noeud** racine)
{
    noeud* newNode = new noeud;
    cout << "Entrer le nom de la personne : ";
    cin >> newNode->nom;
    cout << "Saisissez le nombre d'enfant : ";
    cin >> newNode->nbr_fils;
    *racine = newNode;
    newNode->tab = new noeud*[newNode->nbr_fils];
    for (int i = 0; i < newNode->nbr_fils; i++)
    {
        newNode->tab[i] = NULL;
    }
    if (newNode->nbr_fils == 0) return;
    else{
        for (int i = 0; i < newNode->nbr_fils; i++)
        {
            createArbre(&(*racine)->tab[i]);
        }
    }
    
}

//AFFICHAGE DES ARBRES
void afficheNoeud(noeud* racine, int prof)
{
    if (racine == NULL) return;
    else
    {
        if (prof != 0)
        {
            for (int i = 0; i < prof; i++)
            {
                cout << "\t";
            }
            
        }
        cout << racine->nom << endl;
        for (int i = 0; i < racine->nbr_fils; i++)
        {
            afficheNoeud(racine->tab[i], prof + 1);
        }
       
    }
}

//recherche dans un arbre
//recherche d'un ancetre
noeud* rechercheParent(noeud* racine, string nom)
{
    if (racine == NULL) return NULL;
    if (racine->nom == nom) return racine;
    else
    {
        for (int i = 0; i < racine->nbr_fils; i++)
        {
            if (racine->tab[i]->nom == nom)
            {
                return racine;
            }
            else
            {
                noeud* result = rechercheParent(racine->tab[i], nom);
                if (result != NULL)
                {
                    return result;
                }
                
            }
        }
        return NULL;
    }
}
noeud* rechercheGrandParent(noeud* racine, string nom)
{
    if (racine == NULL) return NULL;
    if (racine->nom == nom) return NULL;
   
        for (int i = 0; i < racine->nbr_fils; i++)
        {
            if (racine->tab[i]->nom == nom)
            {
                cout << "pas de grand parent " << endl;
                return NULL;
            }
                noeud* result = rechercheGrandParent(racine->tab[i], nom);
                if (result != NULL)
                {
                    return result;
                }
        }

    return NULL;
}
// recherche des caracteristique

void afficherCousins(noeud* racine, string nom)
{
    if (racine != NULL)
    {
        noeud* result = rechercheGrandParent(racine, nom);
        if (result == NULL) return;
        for (int i = 0; i < result->nbr_fils; i++)
        {
            for (int j = 0; j < (result->tab[i])->nbr_fils; j++)
            {
                if (
                    ((result->tab[i])->tab[j])->nom != nom)
                {
                    cout << ((result->tab[i])->tab[j])->nom << endl;
                }
            }
        }
    }
}

void afficheFreres(noeud* racine, string nom)
{
    if (racine != NULL)
    {
        noeud* result = rechercheParent(racine, nom);
        if (result == NULL) return;
        for (int i = 0; i < result->nbr_fils; i++)
        {
            if (result->tab[i]->nom != nom)
            {
                cout << (result->tab[i])->nom << endl;
            }
        }
    }
}






int main(int argc, const char * argv[])
{
    string nom;
    cout << " veuiller entrer le nom du parent : ";
    cin >> nom;
    noeud* newNoeud = NULL;
    createArbre(&newNoeud);
    afficheNoeud(newNoeud, 0);
    noeud* result1 = rechercheGrandParent(newNoeud, nom);
    if (result1 != NULL)
    {
        cout <<"le parent recherche est dans l'adresse " << result1 << endl;
    }
    else
    {
        cout << "le parent recherche n'est pas dans l'arbre " << endl;
    }
    
    return 0;
}
