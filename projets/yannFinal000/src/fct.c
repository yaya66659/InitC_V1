// -*- coding: utf-8 -*-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#include "headers/fct.h"

void videBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; /*Vide le buffer clavier*/
}

void activeAffichageUTF8DansLaConsole(bool activerUTF8pourLaSaisie)
{

    SetConsoleOutputCP(CP_UTF8); /* Force l'affichage correct des caractères UTF-8*/
    SetConsoleCP(CP_UTF8);       /* Force l'affichage UTF-8* Pour la saisie*/
}