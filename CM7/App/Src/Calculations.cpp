/*
 * Calculations.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Calculations.h"
#include "TFT_Functions.h"


Calculations::Calculations() {
	// TODO Auto-generated constructor stub

}

Calculations::~Calculations() {
	// TODO Auto-generated destructor stub
}

// returns a rdm value between 1..7
uint8_t Calculations::getRdmBlock(){
	uint32_t test;
	uint8_t test2;
 //   srand(HAL_GetTick());
    test = rand();
    test2 =((uint8_t)(test%7)) + 1;
    return (((uint8_t)(test%7)) + 1);
}

// returns a rdm value between 0..9
uint8_t Calculations::getRdmSpaceInNewLine(){ //uint16_t
   // srand(time(NULL));

/*    uint16 randomLine = 0;
    for(uint8_t i=0; i<=9; i++)
    {
    	randomLine = (rand()%2);
    	randomLine << 1;
    }
    return randomLine;*/

    return (rand()%9); // devide through RAND_MAX/7
}

