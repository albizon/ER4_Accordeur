#ifndef __REDIRECT_PRINTF_H__
#define __REDIRECT_PRINTF_H__


#define PRINTF_OLED   1
#define PRINTF_SERIAL 2


/** Cette fonction permet de rediriger la sortie d'une appel a printf
 *  vers:
 * -> l'afficheur OLED (defaut)
 * -> la liaison série (virtuelle via USB)
 * config prend pour valeur PRINTF_OLED ou PRINTF_SERIAL
 */
void redirectPrintf(unsigned int config);

#endif /* __REDIRECT_PRINTF_H__ */