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
#include <string.h>
#include "headers/fct.h"

void videBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
void VSCode(char * nomProjet){

    char cmdVSCode[_SIZE_T_] = "code . projets\\";
    strcat(cmdVSCode, nomProjet);
    printf("%s\n", cmdVSCode);
    system(cmdVSCode);

}
booleen nomProjetExiste(char * nomProjet)
{
    char cmdListProjetDIR[_SIZE_T_] = "dir /B projets > .dirListProjets.txt";
    char nomProjetExistant[_SIZE_T_] =" ";
    system(cmdListProjetDIR);
    FILE * fic  = NULL;
    fic  = fopen(".dirListProjets.txt", "r");
    if(fic == NULL)
    {
        printf("erreure ouverture fic dir");
        exit(EXIT_FAILURE);
    }
    

    while(!feof(fic))
    {
        fscanf(fic, "%s\n", nomProjetExistant);
        if(!strcmp(nomProjet, nomProjetExistant))
        return VRAI;
        
    }
    return FAUX;

    fclose(fic);
}
void copieFichierC(char * nomProjet){

   char cmdCOPYc[_SIZE_T_] = "copy model\\*.c projets\\";
   strcat(cmdCOPYc, nomProjet);
   strcat(cmdCOPYc, "\\src");
   printf("%s\n", cmdCOPYc);
   system(cmdCOPYc);


}

void copieFichierH(char * nomProjet){

    char cmdCOPYh[_SIZE_T_] = "copy model\\*.h projets\\";
    strcat(cmdCOPYh, nomProjet);
    strcat(cmdCOPYh, "\\src\\headers\\");
    printf("%s\n", cmdCOPYh);
    system(cmdCOPYh);
 
 
 }
 


void creeProjet(char* nomProjet)
{
   char cmdCreeProjet[_SIZE_T_] = "mkdir projets\\";
    strcat(cmdCreeProjet, nomProjet);

    char cmdcreeArboSRC[_SIZE_T_] = "mkdir projets\\";
    strcat(cmdcreeArboSRC, nomProjet);
    strcat(cmdcreeArboSRC, "\\src");

    char cmdcreeArboOBJ[_SIZE_T_] = "mkdir projets\\";
        strcat(cmdcreeArboOBJ, nomProjet);
strcat(cmdcreeArboOBJ, "\\obj");

    char cmdcreeArboBIN[_SIZE_T_] = "mkdir projets\\";
    strcat(cmdcreeArboBIN, nomProjet);
    strcat(cmdcreeArboBIN, "\\bin");

    
    char cmdcreeArboSRCHeader[_SIZE_T_] = "mkdir projets\\";
    strcat(cmdcreeArboSRCHeader, nomProjet);
    strcat(cmdcreeArboSRCHeader, "\\src\\headers");



    printf("%s\n", cmdCreeProjet);
    system(cmdCreeProjet);
    printf("%s\n", cmdcreeArboSRC);
    system(cmdcreeArboSRC);
    printf("%s\n", cmdcreeArboOBJ);
    system(cmdcreeArboOBJ);    
    printf("%s\n", cmdcreeArboBIN);
    system(cmdcreeArboBIN);
    printf("%s\n", cmdcreeArboSRCHeader);
    system(cmdcreeArboSRCHeader);


    copieFichierC(nomProjet);
    copieFichierH(nomProjet);

    VSCode(nomProjet);

    
}



void creeMakeFile(char * nomProjet){
    FILE * ficMakefile = NULL;
   char cheminFicMakefile[_SIZE_T_] ="projets\\";
   strcat(cheminFicMakefile, nomProjet);
   strcat(cheminFicMakefile, "\\Makefile" ); 
    ficMakefile = fopen(cheminFicMakefile, "w");
    if(ficMakefile == NULL)
    {
        printf("Erreure creation du Makefile ficMakefile =NULL\n");
        exit(EXIT_FAILURE);
    }

    char printMakefile[1000] = "CC = gcc\nEXEC = bin/";
    strcat(printMakefile, nomProjet);
    strcat(printMakefile, "\nSRC = $(wildcard src/*.c)\nOBJ = $(patsubst src/%.c,obj/%.o,$(SRC))\n\n# Compilation\nall: $(EXEC)\n\n$(EXEC): $(OBJ)\n\t$(CC) -o $@ $^\n\nobj/%.o: src/%.c\n\t$(CC) -c $< -o $@\n\nclean :\n\tfor %%f in (obj\\*.o)do del /F /Q \"%%f\"\n\ncleanall : clean\n\tdel /F /Q bin\\");
    strcat(printMakefile, nomProjet);
    strcat(printMakefile, ".exe");


    fprintf(ficMakefile, "%s",printMakefile);

    fclose(ficMakefile);

}






