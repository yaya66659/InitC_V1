#ifndef _FCT_H_
#define _FTC_H_

#define _SIZE_T_ 255


typedef enum{
FAUX,
VRAI
}booleen;


void creeProjet(char* nomProjet);
void creeMakeFile(char * nomProjet);
void videBuffer();
booleen nomProjetExiste(char * nomProjet);
void copieFichierC(char * nomProjet);
void copieFichierH(char * nomProjet);
void VSCode(char * nomProjet);



#endif //_FCT_H_
