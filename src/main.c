/*
 * Ce fichier fait partie de InitC_V1.
 *
 * InitC_V1 est un logiciel libre : vous pouvez le redistribuer et/ou le modifier
 * selon les termes de la licence GNU General Public License publiée par
 * la Free Software Foundation, soit la version 3 de la licence,
 * soit (à votre choix) toute version ultérieure.
 *
 * InitC_V1 est distribué dans l’espoir qu’il sera utile,
 * mais SANS AUCUNE GARANTIE ; sans même la garantie implicite
 * de COMMERCIALISATION ou D’ADAPTATION À UN OBJET PARTICULIER.
 * Voir la Licence Publique Générale GNU pour plus de détails.
 *
 * Vous devriez avoir reçu une copie de la Licence Publique Générale GNU
 * avec InitC_V1. Si ce n’est pas le cas, voir <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers/fct.h"
int main(int argc, char *argv[])
{

    activeAffichageUTF8DansLaConsole(false);
    int retScanf = 0;
    int retScanf2 = 0;
    bool er1 = false;
    bool er2 = false;

    char messageErreur1[BUFFER_TEXTE_MAX] = "Nom du projet incorrecte ou déjà existant\n";
    char messageErreur2[BUFFER_TEXTE_MAX] = "Erreur saisir O pour oui N pour non(O/N|o/n)\n";

    char makefile = ' ';
    char nomProjet[BUFFER_TEXTE_MAX];
    printf("\t\tInitC\n");

    printf("Crée votre projet console en C rapidement .\n");

    while (1)
    {

        if (er1)
        {
            printf("%s", messageErreur1);
        }
        printf("Nom du Projet: ");

        retScanf = scanf("%[A-Za-z0-9_-]255s", nomProjet);
        videBuffer();

        if (retScanf == 1 && !nomDeProjetExiste(nomProjet) && nomDeProjetEstPermit(nomProjet))
        {

            printf("le projet %s sera crée\n", nomProjet);
            if (!creeProjet(nomProjet))
            {
                printf("Erreur creation projet : %s\n", nomProjet);
                return 1;
            }
            break;
        }
        else
        {
            er1 = true;
        }
    }

    while (1)
    {
        printf("Vous-les vous un MakeFile dans votre Projet %s, O pour oui N pour non(O/N|o/n\n", nomProjet);
        if (er2)
            printf("%s", messageErreur2);

        printf(">");
        retScanf2 = scanf("%1[ONon]c", &makefile);
        videBuffer();

        if (retScanf2 == 1)
        {
            break;
        }
        else
        {
            er2 = true;
        }
    }

    switch (makefile)
    {
    case 'O':
    case 'o':
        printf("creation du Makefile\n");
        if (!creeMakeFile(nomProjet))
        {
            printf("Erreur creation Makefile pour projet : %s\n", nomProjet);
            return 1;
        }
        break;

    case 'N':
    case 'n':
        printf("Pas de Makefile pour ce projet\n");
        break;

    default:
        printf("Erreur switch makefile");
        break;
    }
    /*************OUVERTURE DANS VSCODE********* */
    printf("ouverture du projet %s dans VSCode(Si disponible dans variable environnement PATH)\n", nomProjet);

    VSCode(nomProjet);

    printf("Fin de la création saisir ENTER pour quitter");
    getchar();

    return 0;
}
