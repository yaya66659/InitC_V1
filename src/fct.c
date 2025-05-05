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
#include <stdbool.h>
#include <windows.h>
#include <shellapi.h>
#include <time.h>

#include "headers/fct.h"

void videBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie)
{

    SetConsoleOutputCP(CP_UTF8); // Force l'affichage correct des caractères UTF-8

    if (activerUTF8pourLaSaisie)
    {
        SetConsoleCP(CP_UTF8); // UTF8 Pour la saisie
    }
}

void VSCode(const char *nomProjet)
{

    char cmdVSCode[BUFFER_TEXTE_MAX];
    snprintf(cmdVSCode, sizeof(cmdVSCode), "projets\\%s", nomProjet);
    printf("Ouverture dans VSCode %s\n", cmdVSCode);
    ShellExecuteA(
        NULL,
        "open",
        "code",
        cmdVSCode,
        NULL,
        SW_SHOW);
}

bool creeProjet(const char *nomProjet)
{
    /********DEFINITION D4UN NOM TEMPORAIRE POUR L PROJET****************/
    char tempName[BUFFER_TEXTE_MAX];
    snprintf(tempName, sizeof(tempName), "%s%s_temp", DEBUT_NOM_PROJET_TEMPORAIRE, nomProjet);

    char cheminTemp[BUFFER_TEXTE_MAX];
    snprintf(cheminTemp, sizeof(cheminTemp), "projets\\%s", tempName);

    char chemin[BUFFER_TEXTE_MAX];

    /*****************CREATION DES DOSSIER ET SOUS DOSSIER  */
    if (creeDossier(cheminTemp) != 1)
    {

        printf("Erreur creation %s\n", cheminTemp);
        return false;
    }

    snprintf(chemin, sizeof(chemin), "%s\\bin", cheminTemp);
    if (creeDossier(chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur création %s\n", chemin);
        return false;
    }

    snprintf(chemin, sizeof(chemin), "%s\\src", cheminTemp);
    if (creeDossier(chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur création %s\n", chemin);
        return false;
    }

    snprintf(chemin, sizeof(chemin), "%s\\obj", cheminTemp);
    if (creeDossier(chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur création %s\n", chemin);
        return false;
    }
    snprintf(chemin, sizeof(chemin), "%s\\src\\headers", cheminTemp);
    if (creeDossier(chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur création %s\n", chemin);
        return false;
    }

    /**********COPIE DES FICHIER MODEL**************** */
    snprintf(chemin, sizeof(chemin), "%s\\src\\main.c", cheminTemp);
    if (copierFichier("model\\main.c", chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur copie %s\n", chemin);
        return false;
    }

    snprintf(chemin, sizeof(chemin), "%s\\src\\fct.c", cheminTemp);
    if (copierFichier("model\\fct.c", chemin) != 1)
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur copie %s\n", chemin);
        return false;
    }

    /*******ÉCRITURE PERSONNALISER DE FCT_H********** */

    if (!ecritSecurisationsFctH(cheminTemp, nomProjet))
    {
        supprimerDossierRecursif(cheminTemp);
        printf("Erreur écriture fct.h chemin : %s\n", chemin);
        return false;
    }

    /*****Renommage du nom de projet temporaire***** */

    char cheminFinal[BUFFER_TEXTE_MAX];
    snprintf(cheminFinal, sizeof(cheminFinal), "projets\\%s", nomProjet);

    if (!MoveFileA(cheminTemp, cheminFinal))
    {
        DWORD err = GetLastError();
        printf("Erreur renommage '%s' ver '%s' : %lu\n", cheminTemp, cheminFinal, err);
        supprimerDossierRecursif(cheminTemp);
        return false;
    }

    return true;
}

bool creeMakeFile(const char *nomProjet)
{
    FILE *ficMakefile = NULL;
    int retFprintfMakeFile = 0;
    char cheminFicMakefile[BUFFER_CHEMIN_MAX];

    snprintf(cheminFicMakefile, sizeof(cheminFicMakefile), "projets\\%s\\Makefile", nomProjet);
    ficMakefile = fopen(cheminFicMakefile, "w");
    if (ficMakefile == NULL)
    {
        printf("Erreur creation du Makefile ficMakefile =NULL\n");
        return false;
    }

    if (fprintf(ficMakefile, "CC = gcc\n") < 0 || fprintf(ficMakefile, "EXEC = bin/%s\n", nomProjet) < 0 || fprintf(ficMakefile, "SRC = $(wildcard src/*.c)\n") < 0 || fprintf(ficMakefile, "OBJ = $(patsubst src/%%.c,obj/%%.o,$(SRC))\n") < 0 || fprintf(ficMakefile, "\n") < 0 || fprintf(ficMakefile, "#Compilation\n") < 0 || fprintf(ficMakefile, "all: $(EXEC)\n\n") < 0 || fprintf(ficMakefile, "$(EXEC): $(OBJ)\n") < 0 || fprintf(ficMakefile, "\t$(CC) -o $@ $^\n") < 0 || fprintf(ficMakefile, "\n") < 0 || fprintf(ficMakefile, "obj/%%.o: src/%%.c\n") < 0 || fprintf(ficMakefile, "\t$(CC) -c $< -o $@\n") < 0 || fprintf(ficMakefile, "\n") < 0 || fprintf(ficMakefile, "clean :\n") < 0 || fprintf(ficMakefile, "\tfor %%%%f in (obj\\*.o)do del /F /Q \"%%%%f\"\n") < 0 || fprintf(ficMakefile, "\n") < 0 || fprintf(ficMakefile, "cleanall : clean\n") < 0 || fprintf(ficMakefile, "\tdel /F /Q bin\\%s.exe", nomProjet) < 0)
    {
        printf("Erreur écriture Makefile du projet : %s\n", nomProjet);
        fclose(ficMakefile);
        supprimerFichier(cheminFicMakefile);
        return false;
    }

    fclose(ficMakefile);
    return true;
}

int creeDossier(const char *chemin)
{
    if (!CreateDirectoryA(chemin, NULL))
    {
        DWORD err = GetLastError();
        if (err == ERROR_ALREADY_EXISTS)
        {
            return 1;
        }
        else
        {
            printf("Erreur: creation du dossier '%s' : %lu\n", chemin, err);
            return 0;
        }
    }

    return 1;
}
int copierFichier(const char *source, const char *destination)
{
    if (!CopyFileA(source, destination, FALSE))
    {
        DWORD err = GetLastError();
        printf("Erreur copie %s vers %s : %lu\n", source, destination, err);
        return 0;
    }
    return 1;
}

int supprimerFichier(const char *chemin)
{
    if (!DeleteFileA(chemin))
    {
        DWORD err = GetLastError();
        printf("erreur suppression fichier '%s' : %lu\n", chemin, err);
        return 0;
    }
    return 1;
}
int supprimerDossierRecursif(const char *cheminDossier)
{
    char chemin[BUFFER_CHEMIN_MAX];
    WIN32_FIND_DATAA ffd;
    HANDLE hFind;

    /*Préparer le chemin de recherche*/
    snprintf(chemin, sizeof(chemin), "%s\\*", cheminDossier);
    hFind = FindFirstFileA(chemin, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Erreur: impossible d'accéder à %s\n", cheminDossier);
        return 0;
    }

    do
    {
        /*Ignorer "." et ".."*/
        if (strcmp(ffd.cFileName, ".") != 0 && strcmp(ffd.cFileName, "..") != 0)
        {
            // Construire le chemin complet
            char cheminComplet[BUFFER_CHEMIN_MAX];
            int retSnprintf = 0;
            retSnprintf = snprintf(cheminComplet, sizeof(cheminComplet), "%s\\%s", cheminDossier, ffd.cFileName);

            if (retSnprintf >= sizeof(cheminComplet) || retSnprintf < 0)
            {
                printf("Erreur buffer overflow sur cheminComplet: %s avec cheminDossier %s\n", cheminComplet, cheminDossier);
                FindClose(hFind);
                return 0;
            }

            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                /* C'est un sous-dossier : rappel de la fonction recursive pour suppression */
                if (supprimerDossierRecursif(cheminComplet) != 1)
                {
                    printf("Erreur appel fonction supprimer Dossier sur chemin : %s\n", cheminComplet);
                    FindClose(hFind);
                    return 0;
                }
            }
            else
            {
                /* C'est un fichier*/
                if (!DeleteFileA(cheminComplet))
                {
                    printf("Erreur suppression fichier %s\n", cheminComplet);
                    FindClose(hFind);
                    return 0;
                }
            }
        }

    } while (FindNextFileA(hFind, &ffd));

    FindClose(hFind);

    /*Supprimer le dossier lui-même*/
    if (!RemoveDirectoryA(cheminDossier))
    {
        printf("Erreur suppression dossier %s\n", cheminDossier);
        return 0;
    }

    return 1;
}
bool nomDeProjetEstPermit(const char *nomProjet)
{

    if (strncmp(DEBUT_NOM_PROJET_TEMPORAIRE, nomProjet, strlen(DEBUT_NOM_PROJET_TEMPORAIRE)) == 0 || strstr(nomProjet, "_temp") != NULL)
    {

        printf("Nom de projet Non valide 'temporary_%s_temp' (mot-clé temporaire: temporary_xxxx_temp)\n", nomProjet);
        return false;
    }

    return true;
}

bool ecritSecurisationsFctH(const char *cheminProjetTemp, const char *nomProjet)
{
    char cheminFichierFctH[BUFFER_CHEMIN_MAX];

    time_t timestampActuel;
    struct tm *infosLocal;

    /*On récupère le timestamp actuel*/
    time(&timestampActuel);

    /*convertir en heure locale*/
    infosLocal = localtime(&timestampActuel);

    snprintf(cheminFichierFctH, sizeof(cheminFichierFctH), "%s/src/headers/fct.h", cheminProjetTemp);

    /*On crée le fichier fct.h dans le projet et on ouvre en écriture*/
    FILE *ficFctH = NULL;
    ficFctH = fopen(cheminFichierFctH, "w");
    if (ficFctH == NULL)
    {
        printf("Erreur ouverture fichier %s en mode 'w'\n ", cheminFichierFctH);
        return false;
    }

    /*ÉCRITURES EN TÊTE DE SÉCURISATIONS INCLUSIONS MULTIPLE*/
    if (fprintf(ficFctH, "#ifndef FCT_%02d%02d%d_%s_H\n", infosLocal->tm_mday, infosLocal->tm_mon + 1, infosLocal->tm_year + 1900, nomProjet) < 0 || fprintf(ficFctH, "#define FCT_%02d%02d%d_%s_H\n", infosLocal->tm_mday, infosLocal->tm_mon + 1, infosLocal->tm_year + 1900, nomProjet) < 0)
    {

        printf("Erreur écriture dans fichier %s de #ifndef et #define\n", cheminFichierFctH);
        fclose(ficFctH);
        supprimerFichier(cheminFichierFctH);
        return false;
    }

    /*ÉCRITURE INCLUSION STDBOOL*/
    if (fprintf(ficFctH, "\n#include <stdbool.h>\n") < 0)
    {
        printf("Erreur écriture dans fichier %s de #include <stdbool.h>\n", cheminFichierFctH);
        fclose(ficFctH);
        supprimerFichier(cheminFichierFctH);
        return false;
    }

    /*ÉCRITURE DEFINITION DE BUFFER SIZE*/
    if (fprintf(ficFctH, "\n#define BUFFER_TEXTE_MAX 256\n") < 0 || fprintf(ficFctH, "#define BUFFER_CHEMIN_MAX 512\n") < 0)
    {
        printf("Erreur écriture dans fichier %s de BUFFER_TEXTE_MAX et BUFFER_CHEMIN_MAX\n", cheminFichierFctH);
        fclose(ficFctH);
        supprimerFichier(cheminFichierFctH);
        return false;
    }

    /*ÉCRITURES DEFINITIONS DE FONCTIONS DE BASES*/
    if (fprintf(ficFctH, "\nvoid videBuffer(void);\n") < 0 || fprintf(ficFctH, "void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie);\n") < 0)
    {
        printf("Erreur écriture dans fichier %s de definitions de fonctions\n", cheminFichierFctH);
        fclose(ficFctH);
        supprimerFichier(cheminFichierFctH);
        return false;
    }

    /*ÉCRITURES FERMETURE DE IFNDEF AVEC ENDIF*/
    if (fprintf(ficFctH, "\n#endif /*FCT_%02d%02d%d_%s_H*/", infosLocal->tm_mday, infosLocal->tm_mon + 1, infosLocal->tm_year + 1900, nomProjet) < 0)
    {
        printf("Erreur écriture dans fichier %s de #endif\n", cheminFichierFctH);
        fclose(ficFctH);
        supprimerFichier(cheminFichierFctH);
        return false;
    }

    fclose(ficFctH);

    return true;
}
bool nomDeProjetExiste(const char *nomProjet)
{
    char chemin[BUFFER_CHEMIN_MAX];
    snprintf(chemin, sizeof(chemin), "projets\\%s", nomProjet);

    /*on vérifie que le chemin existe pas */
    DWORD attrib = GetFileAttributesA(chemin);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        return true; /*il y a pas de projet du même nom*/
    }
    else
    {
        DWORD err = GetLastError();
    }
    return false; /*il y a un projet du même nom*/
}
bool nomDeProjetInterdit(const char *nomProjet)
{
    /*Liste des nom de projet réservée au système*/
    const char nomsInterdits[BUFFER_CHEMIN_MAX] = "CON PRN AUX NUL COM1 COM2 COM3 COM4 COM5 COM6 COM7 COM8 COM9 LPT1 LPT2 LPT3 LPT4 LPT5 LPT6 LPT7 LPT8 LPT9";
    char buffer[BUFFER_TEXTE_MAX];
    int x = 0;
    size_t len  = strlen(nomsInterdits);

    for (int i = 0; i <= len; i++)
    {
        if (nomsInterdits[i] == ' ' || nomsInterdits[i] == '\0')
        {
            buffer[x] = '\0';
            if (strcmp(nomProjet, buffer) == 0)
            {
                printf("Nom de projet %s INTERDIT (réservé au système)\n", nomProjet);
                return true;
            }

            x = 0;
            buffer[0] = '\0';
        }
        else
        {
            if (x < BUFFER_TEXTE_MAX - 1)
            {
                buffer[x++] = nomsInterdits[i];
            }
        }
    }

    return false;
}

bool symboleInterditDansNomDeProjet(const char *nomProjet)
{
    const char caracteresInterdits[BUFFER_TEXTE_MAX] = "< > : \" / \\ | ? *";
    char buffer[BUFFER_TEXTE_MAX];
    int x = 0;
    size_t len  = strlen(caracteresInterdits);

    for (int i = 0; i <= len; i++)
    {

        if (caracteresInterdits[i] == ' ' || caracteresInterdits[i] == '\0')
        {
            buffer[x] = '\0';
            if (strstr(nomProjet, buffer) != NULL)
            {

                printf("Un caractère interdit est present dans le nom du projet : '%s' (< > : \" / \\ | ? *)\n", nomProjet);
                return true;
            }
            x = 0;
            buffer[0] = '\0';
        }
        else
        {
            buffer[x++] = caracteresInterdits[i];
        }
    }

    return false;
}
