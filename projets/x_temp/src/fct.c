// -*- coding: utf-8 -*-

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

#include "headers/fct.h"

void videBuffer(void){
    int c;
    while ((c =getchar()) != '\n' && c != EOF);
  
    
}

void activeAffichageUTF8DansLaConsole(void){

    system("chcp 65001 > nul"); //definit la console en UTF-8 en Changent la code page de la console
    SetConsoleOutputCP(CP_UTF8);// Force l'affichage correct des caractères UTF-8 

}




