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

#ifndef _FCT_H_
#define _FCT_H_

#define BUFFER_SIZE 256
#define NOM_FICHIER_TAMPON ".dirListProjets.txt"


void activeAffichageUTF8DansLaConsole(void);

void creeProjet(const char* nomProjet);
void creeMakeFile(const char * nomProjet);
void videBuffer(void);
bool nomProjetExiste(const char * nomProjet);
void VSCode(const char * nomProjet);
bool listerLesDossierDansProjet(void);
int creeDossier(const char * chemin);
int copierFichier(const char * source,  const char * destination);
int supprimmerFichier(const char * chemin );

bool nomDeProjetEstPermit(const char * nomProjet);



#endif //_FCT_H_
