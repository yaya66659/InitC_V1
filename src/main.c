#include<stdio.h>
#include<stdlib.h>

#include"headers/fct.h"
int main(int argc, char *argv[])
{
 int   retScanf = 0;
 int retScanf2 = 0;
    booleen er1 = FAUX;
    booleen er2 = FAUX;

 char messageErreure1[_SIZE_T_] = "Nom du projet incorecte ou deja existant\n";
 char messageErreure2[_SIZE_T_] = "Erreure saisir O pour oui N pour non(O/N|o/n)\n";


    char makefile = ' ';
        char  nomProjet[_SIZE_T_] = " ";
    printf("\t\tInitC\n");

    printf("Cree votre projet console en c rapidement en entrent le non de votre Projet:\n");

    while(1)
    {

            if(er1)
            {
                printf("%s", messageErreure1);
            }
            printf("Nom du Projet: ");

            retScanf = scanf("%255[A-Za-z0-9]s", nomProjet);
            videBuffer();

            if(retScanf == 1 && !nomProjetExiste(nomProjet))
            {
                er1 = FAUX;
                break;
            }           
            else
            {
                er1 = VRAI;
            }


    }
        printf("le projet %s sera cree\n", nomProjet );
    while(1)
    {
             printf("Vous-les vous un Make file dans votre Projet %s, O pour oui N pour non(O/N|o/n\n", nomProjet);
             if(er2)
             printf("%s", messageErreure2);

             printf(">");
             retScanf2 = scanf("%1[ONon]c", &makefile);
             videBuffer();

             if( retScanf2 == 1)
             {
                 er2 = FAUX;
                 break;
             }
             else
             {
                 er2 = VRAI;
             }



    }

    creeProjet(nomProjet);

    switch (makefile)
    {
    case 'O':
    case 'o':
        printf("creation du Makefile\n");
        creeMakeFile(nomProjet);
        break;
    
        case 'N':
        case 'n':
            printf("Pas de Makefile pour ce projet\n");
            break;
            
    
    default:
            printf("Erreure switch makefile");
        break;
    }




return 0;
}