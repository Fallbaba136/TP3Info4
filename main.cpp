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

void rajouterEnfant(noeud* racine, string nomPersonne)
{
    if (racine == NULL) return;
    if (racine->nom == nomPersonne)
    {
        createArbre(&racine);
    }
    noeud* cible = NULL;
    for (int i = 0; i < racine->nbr_fils; i++)
    {
        if (racine->tab[i]->nom == nomPersonne)
        {
            cible = racine->tab[i];
            break;
        }
       
    }
    if (cible != NULL)
    {
        noeud** newTab = new noeud*[cible->nbr_fils + 1];
        for (int j = 0; j < cible->nbr_fils + 1; j++)
        {
            newTab[j] = cible->tab[j];
            noeud* newEnfant = new noeud;
            createArbre(&newEnfant);
            newTab[cible->nbr_fils] = newEnfant;
        }
        delete [] cible->tab;
        cible->tab = newTab;
        cible->nbr_fils++;
    }
    else
    {
        for (int i = 0; i < racine->nbr_fils; i++)
        {
            rajouterEnfant(racine->tab[i], nomPersonne);
        }
    }
   
   
}




int main() {
    // Création d'un arbre de profondeur 3
    noeud* arbre = NULL;
    createArbre(&arbre);
    
    // Affichage de l'arbre
    cout << "Arbre créé :" << endl;
    afficheNoeud(arbre, 0);
    
    // Tests des cousins
    cout << "\n--- TESTS COUSINS ---" << endl;
    cout << "Cousins d'un nœud sans cousin :" << endl;
    afficherCousins(arbre, "nom_sans_cousin");
    
    cout << "Cousins d'un nœud avec plusieurs cousins :" << endl;
    afficherCousins(arbre, "nom_avec_cousins");
    
    cout << "Cousins d'un nœud inexistant :" << endl;
    afficherCousins(arbre, "nom_inexistant");
    
    // Tests des frères
    cout << "\n--- TESTS FRÈRES ---" << endl;
    cout << "Frères d'un nœud sans frère :" << endl;
    afficheFreres(arbre, "nom_sans_frere");
    
    cout << "Frères d'un nœud avec plusieurs frères :" << endl;
    afficheFreres(arbre, "nom_avec_freres");
    
    // Test ajout d'enfant
    cout << "\n--- AJOUT D'ENFANT ---" << endl;
    rajouterEnfant(arbre, "nom_parent");
    afficheNoeud(arbre, 0);
    
    return 0;
}
