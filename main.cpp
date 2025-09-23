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
        cout << racine->nom;
        if (prof != 0)
        {
            cout << "\t";
        }
        for (int i = 0; i < racine->nbr_fils; i++)
        {
            afficheNoeud(racine->tab[i], prof + 1);
        }
       
    }
}

//recher





































int main(int argc, const char * argv[])
{
    noeud* newNoeud = NULL;
    createArbre(&newNoeud);
    afficheNoeud(newNoeud, 4);
    
    
    
    return 0;
}
