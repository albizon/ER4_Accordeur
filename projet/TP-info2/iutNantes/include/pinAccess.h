#ifndef __PIN_ACCESS_H__
#define __PIN_ACCESS_H__

//nom du port
#define PORTA 0
#define PORTB 1

//mode
#define DISABLE        0
#define OUTPUT         1
#define INPUT          2
#define INPUT_PULLUP   3
#define INPUT_PULLDOWN 4

//configuration d'une broche du micro-controleur
// - port est soit PORTA, soit PORTB
// - numBit est le numéro de bit (0 à 31)
// - mode est le mode de la broche (DISABLE, OUTPUT, ...)
void pinMode(unsigned char port, 
             unsigned char numBit,
             unsigned char mode);

//affectation de l'état d'une broche déjà configurée
// état heut si 'value' est différent de 0
// état bas si value est nul
void digitalWrite(unsigned char port, 
                  unsigned char numBit,
                  unsigned int value);

//inverse l'etat d'une broche configuree:
// 0 => 1
// 1 => 0
void digitalToggle(unsigned char port, 
                  unsigned char numBit);

//lecture de l'état d'une broche déjà configurée
//renvoie:
// - 0xFF en cas d'erreur (mauvais port/numero de bit)
// - 0 ou 1 suivant l'état du bit
unsigned char digitalRead(unsigned char port,
                          unsigned char numBit);

#endif
