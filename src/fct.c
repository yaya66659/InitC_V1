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
#include<stdbool.h>
#include<windows.h>
#include <shellapi.h>

#include "headers/fct.h"

void videBuffer(void)
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
void activeAffichageUTF8DansLaConsole(void){

    system("chcp 65001 > nul"); //definit la console en UTF-8 en Changent la code page de la console
    SetConsoleOutputCP(CP_UTF8);// Force l'affichage correct des caractères UTF-8 

}

void VSCode(const char * nomProjet){

    char cmdVSCode[BUFFER_SIZE];
   snprintf(cmdVSCode, sizeof(cmdVSCode),"projets\\%s", nomProjet);
    printf("Ouvertur dans VSCode %s\n", cmdVSCode);
    ShellExecuteA(
            NULL,
            "open",
            "code",
            cmdVSCode,
            NULL,
            SW_SHOW
    );
}

bool listerLesDossierDansProjet(void){

    WIN32_FIND_DATA findData;
    HANDLE hFind;

    FILE * fic  = NULL;
    char monFic[BUFFER_SIZE] = NOM_FICHIER_TAMPON;
    fic  = fopen(monFic,  "w");
    if(fic == NULL)
    {
        printf("Erreur: ouvertur %s en ecriture\n", monFic);
         return false;
                   

    }

    hFind = FindFirstFileA("projets\\*", &findData);

  

    

    if(hFind == INVALID_HANDLE_VALUE )
    {
        printf("erreur : impossible d'ouvrire le dossier 'projets'\n");
        fclose(fic);
        return false;
        
    }


    do{

            if(strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0  ){

                if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                   fprintf(fic, "%s\n", findData.cFileName);                  
                }
            }

    }while(FindNextFileA(hFind, &findData));


   
    FindClose(hFind);
    fclose(fic);

return true;
}

bool nomProjetExiste(const char * nomProjet)
{
    char monFic[BUFFER_SIZE] = NOM_FICHIER_TAMPON;
    char nomProjetExistant[BUFFER_SIZE] =" " ;
    
    if(!listerLesDossierDansProjet())
    {
        printf("Erreur listDossierDansProjets");
        exit(EXIT_FAILURE);
    }
   
    FILE * fic  = NULL;

    fic  = fopen(monFic, "r");
    if(fic == NULL)
    {
        printf("erreure ouverture fic dir");
        exit(EXIT_FAILURE);
    }
    

    while(fscanf(fic, "%s\n", nomProjetExistant) == 1)
    {       
        if(strcmp(nomProjet, nomProjetExistant) == 0)
        {
            fclose(fic);
            if(supprimmerFichier(monFic) == 0){
                
                exit(EXIT_FAILURE);
            
            }
            
            return true;
        }
       
     }
   

    fclose(fic);

    if(supprimmerFichier(monFic) == 0){
        exit(EXIT_FAILURE);
    }
    
    return false;
}


 


void creeProjet(const char* nomProjet)
{
        /********DEFINITION D4UN NOM TEMPORAIRE POUR L PROJET****************/
    char tempName[BUFFER_SIZE];
    snprintf(tempName, sizeof(tempName), "temporary_%s_temp", nomProjet);

    char cheminTemp[BUFFER_SIZE];
    snprintf(cheminTemp, sizeof(cheminTemp), "projets\\%s", tempName);


   char chemin[BUFFER_SIZE];

   /*****************CR2ETION DES DOSSIER ET SOUS DOSSIER  */
    if(creeDossier(cheminTemp) != 1){
        printf("Erreure creation %s\n", cheminTemp);
        exit(EXIT_FAILURE);

    }

    snprintf(chemin, sizeof(chemin),"%s\\bin", cheminTemp );
    if(creeDossier(chemin) != 1){
        printf("Erreure créetion %s\n", chemin);
        exit(EXIT_FAILURE);

    }

    snprintf(chemin, sizeof(chemin),"%s\\src", cheminTemp );
    if(creeDossier(chemin) != 1){
        printf("Erreure créetion %s\n", chemin);
        exit(EXIT_FAILURE);

    }
    
    snprintf(chemin, sizeof(chemin),"%s\\obj", cheminTemp);
    if(creeDossier(chemin) != 1){
        printf("Erreure créetion %s\n", chemin);
        exit(EXIT_FAILURE);

    }
     snprintf(chemin, sizeof(chemin),"%s\\src\\headers", cheminTemp);
     if(creeDossier(chemin) != 1){
        printf("Erreure créetion %s\n", chemin);
        exit(EXIT_FAILURE);

    }
    
    /**********COPIEE DES FICHIER MODEL**************** */
    snprintf(chemin, sizeof(chemin),"%s\\src\\main.c", cheminTemp);
   if(copierFichier("model\\main.c", chemin) != 1){
    printf("Erreure copie %s\n", chemin);
    exit(EXIT_FAILURE);

}

   snprintf(chemin, sizeof(chemin),"%s\\src\\fct.c", cheminTemp);
   if(copierFichier("model\\fct.c", chemin) != 1){
    printf("Erreure copie %s\n", chemin);
    exit(EXIT_FAILURE);

}

   snprintf(chemin, sizeof(chemin),"%s\\src\\headers\\fct.h", cheminTemp);
   if(copierFichier("model\\fct.h", chemin) != 1){
    printf("Erreure copie %s\n", chemin);
    exit(EXIT_FAILURE);

}
/*****Rennomage du nom de projet temporaire***** */
//printf("Debug voir le fichier temp %s avant renomage en %s\n", cheminTemp, nomProjet);
//getchar();
char cheminFinal[BUFFER_SIZE];
snprintf(cheminFinal, sizeof(cheminFinal), "projets\\%s", nomProjet);

if(!MoveFileA(cheminTemp, cheminFinal)){
    DWORD err = GetLastError();
    printf("Erreure renommage '%s' ver '%s' : %lu\n", cheminTemp, cheminFinal, err);
    exit(EXIT_FAILURE);
}
    
 //printf("Debug : Fichier temp renommer\n") ; 

  

    
}

void creeMakeFile(const char * nomProjet){
    FILE * ficMakefile = NULL;
    int retFprintfMakeFile = 0;
   char cheminFicMakefile[BUFFER_SIZE];

   char printMakefile[10000];
   snprintf(printMakefile, sizeof(printMakefile),"CC = gcc\nEXEC = bin/%s\nSRC = $(wildcard src/*.c)\nOBJ = $(patsubst src/%%.c,obj/%%.o,$(SRC))\n\n# Compilation\nall: $(EXEC)\n\n$(EXEC): $(OBJ)\n\t$(CC) -o $@ $^\n\nobj/%%.o: src/%%.c\n\t$(CC) -c $< -o $@\n\nclean :\n\tfor %%%%f in (obj\\*.o)do del /F /Q \"%%%%f\"\n\ncleanall : clean\n\tdel /F /Q bin\\%s.exe", nomProjet, nomProjet);

   snprintf(cheminFicMakefile, sizeof(cheminFicMakefile), "projets\\%s\\Makefile", nomProjet);
    ficMakefile = fopen(cheminFicMakefile, "w");
    if(ficMakefile == NULL)
    {
        printf("Erreure creation du Makefile ficMakefile =NULL\n");
        exit(EXIT_FAILURE);
    }

 
   
   retFprintfMakeFile =  fprintf(ficMakefile, "%s",printMakefile);

   if(retFprintfMakeFile <0)
   {
    printf("Debug : Erreur makefile  non ecrit!\n");
     fclose(ficMakefile);
     exit(EXIT_FAILURE);
   }
    
    fclose(ficMakefile);

}

int creeDossier(const char * chemin){
    if(!CreateDirectoryA(chemin, NULL)){
        DWORD err = GetLastError();
        if(err == ERROR_ALREADY_EXISTS){
            return 1;
        }
        else{
            printf("Erreur: creation du dossier '%s' : %lu\n", chemin, err);
            return 0;
        }

    }

    return 1;
}
int copierFichier(const char * source,  const char * destination){
    if(!CopyFileA(source, destination, FALSE))
    {
        DWORD err = GetLastError();
        printf("Erreur copie %s vers %s : %lu\n", source , destination,  err);
        return 0;
    }
    return 1;
}

int supprimmerFichier(const char * chemin ){
    if(!DeleteFileA(chemin)){
        DWORD err = GetLastError();
        printf("erreure suppression fichier '%s' : %lu\n", chemin, err);
        return 0;
    }
    return 1;
    
}

bool nomDeProjetEstPermit(const char * nomProjet){

    if(strncmp("temporary_", nomProjet, 10) == 0 && strstr("_temp", nomProjet) != NULL){
          
                printf("Nom de projet Non valide 'temporary_%s_temp' (mot-clé temporaire: temporary_xxxx_temp)\n", nomProjet);
                return false;
           
        
    }
 
    return true;
}