/*
* Accordeur de Guitare
* Authors : METAYER Simon & BIZON Alexis
* Created Date : 23/01/17
* Version : 1.0
*/

#ifndef __DISPLAY_H__
#define __DISPLAY_H__


/*
* Overview : Affichage du titre du projet sur la première ligne de l'afficheur
* Author : METAYER Simon
* Params : none
* Return : none
*/
void displayTitle();


/*
* Overview : Convertie un code représentant la note en un texte contenant le nom de la note
* Author : BIZON Alexis
* Params :  const char: note ->Le code de la note;
            char*: str ->La chaine de caractères du nom de la note
* Return : none
*/
void noteToString(const char note, char* str);


/*
* Overview : Affiche la fréquence envoyée en paramètre
* Author : METAYER Simon
* Params :  float freq ->La fréquence à afficher
* Return : none
*/
void displayFrequence(float freq);


/*
* Overview : Affiche la note envoyée en paramètre
* Author : BIZON Alexis
* Params :  const char note ->La note à afficher
* Return : none
*/
void displayNote(const char note);


/*
* Overview : Affiche le degré ou l'octave envoyée en paramètre
* Author : BIZON Alexis
* Params :  char degre ->Le degré à afficher
* Return : none
*/
void displayDegre(char degre);


#endif
