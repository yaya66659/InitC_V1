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

#ifndef H_FCT__04052025__YPI
#define H_FCT__04052025__YPI

#include <stdbool.h>

#define TAILLE_FORMAT_NOM_PROJET 30
#define BUFFER_TEXTE_MAX 256
#define BUFFER_CHEMIN_MAX 512

#define DEBUT_NOM_PROJET_TEMPORAIRE "temporary_"


void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie);
bool creeProjet(const char *nomProjet);
bool creeMakeFile(const char *nomProjet);
void videBuffer(void);
int supprimerDossierRecursif(const char *cheminDossier);
void VSCode(const char *nomProjet);
int creeDossier(const char *chemin);
int copierFichier(const char *source, const char *destination);
int supprimerFichier(const char *chemin);
bool nomDeProjetEstPermit(const char *nomProjet);
bool ecritSecurisationsFctH(const char *cheminProjetTemp, const char *nomProjet);
bool nomDeProjetExiste(const char *nomProjet);
bool nomDeProjetInterdit(const char *nomProjet);
bool symboleInterditDansNomDeProjet(const char *nomProjet);
#endif /* H_FCT__04052025__YPI*/
