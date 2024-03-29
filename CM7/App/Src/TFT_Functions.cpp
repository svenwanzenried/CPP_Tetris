#include "TFT_Functions.h"
#include "st7735.h"
#include "main.h"
#include <Adafruit_TFTShield18.h>


void setUpField()
{
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_DrawFastVLine(0x50, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastVLine(0x51, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastVLine(0x7E, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastVLine(0x7F, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x30, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x31, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x00, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x01, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x9E, 160, ST7735_WHITE);
	ST7735_DrawFastHLine(0x51, 0x9F, 160, ST7735_WHITE);
/*	for(uint8_t i = 0; i<10; i++)
	{
		for(uint8_t u = 0; u<20; u++)
		{
			ST7735_FillRectangle_mod(i*8,(u*8), 8, 8, ST7735_YELLOW);
			u++;
			ST7735_FillRectangle_mod(i*8, (u*8), 8, 8, ST7735_RED);
		}
	}*/

}

//
uint8_t writeTopLine(char *text, uint16_t color){
	uint8_t NrOfChar=0;
	while(*text)
	{
		NrOfChar++;
		text++;
	}
	text = text-NrOfChar;
	if(NrOfChar>10)
	{
		return 0x01;
	}
	else
	{
		ST7735_DrawString_wS(0x0004, 0x0004, text, color, 2 );
		return 0;
	}
}

//
uint8_t writeBtnMiddleLine(char *text, uint16_t color){
	uint8_t NrOfChar=0;
	while(*text)
	{
		NrOfChar++;
		text++;
	}
	text = text-NrOfChar;
	if(NrOfChar>10)
	{
		return 0x01;
	}
	else
	{
		ST7735_DrawString_wS(0x0004, 0x0022, text, color, 2 );
		return 0;
	}
}


// Max 8 chars
uint8_t writeState(char *text, uint16_t color)
{
	uint8_t NrOfChar=0;
	while(*text)
	{
		NrOfChar++;
		text++;
	}
	text = text-NrOfChar;
	if(NrOfChar>10)
	{
		return 0x01;
	}
	else
	{
		ST7735_DrawString_wS(0x0004, 0x0049, text, color, 2 );
		return 0;
	}
}

//
uint8_t writeFourthLine(uint32_t integer32, uint16_t color){
	char levelTxt[5] = {0,0,0,0,0};
	//uint32_t tmpLevel = 100000 / moveDownCnt;
	//if(tmpLevel < 100){
	//	ST7735_FillRectangle(0x0019, 0x0060, 0x0020, 0x0018, ST7735_BLACK);
	//}
	if(integer32 < 10){
		sprintf(levelTxt, "000%d", integer32);
	}
	else if(integer32 < 100){
		sprintf(levelTxt, "00%d", integer32);
	}
	else if(integer32 < 1000){
		sprintf(levelTxt, "0%d", integer32);
	}
	else{
		sprintf(levelTxt, "%d", integer32);
	}
	ST7735_DrawString_wS(0x0004, 0x0070 , levelTxt, color, 2);
	return 0;
}

// Show score in game
uint8_t writeScore(uint32_t score, uint16_t color)
{
	char scoreTxt[10] = {0, 0, 0,0, 0, 0, 0, 0, 0, 0}; 							// Uint32_t gibt max. 10 stellen, topLine und botLine müssen 7 gross und
	char topLine[7] = {48,48,48,48,48,48,0}, botLine[7]={48,48,48,48,48,48,0};	// der letzte char 0 sein da DrawString auf 0 prüft und erst dann abbricht
	//char title[7]={83,99,111,114,101,58,0}; 	// Score:
	char title[7]={83,67,79,82,69,58,0};		// SCORE:
	sprintf(scoreTxt, "%d", score);

	for(uint8_t i=0; i<=5; i++)
	{
		botLine[5-i] = scoreTxt[9-i];
	}

	for(uint8_t i=0; i<=3; i++)
	{
		topLine[5-i] = scoreTxt[(9-(i+6))];
	}


	ST7735_DrawString_wS(0x0056, 0x0058, title, color, 1 );
	ST7735_DrawString_wS(0x0056, 0x0060, topLine, color, 1 );
	ST7735_DrawString_wS(0x0056, 0x0068, botLine, color, 1 );
}

uint8_t writeRanking(uint16_t *score){
	ST7735_FillScreen(ST7735_BLACK);
	uint16_t tmpScore;
	uint16_t col;
	uint16_t yPixel = 4;
	char scoreTxt[8] = {0,0,0,0,0,0,0,0};
	for(uint8_t i = 0; i<10;i++){
		switch (i) {
			case 0:
				col = ST7735_YELLOW;
				break;
			case 1:
				col = ST7735_WHITE;
				break;
			case 2:
				col = ST7735_ORANGE;
				break;
			default:
				col = ST7735_BLUE;
				break;
		}

		if(*score<10){
			sprintf(scoreTxt, "%d. 000%d", i, *score);
		}
		else if(*score<100){
			sprintf(scoreTxt, "%d. 00%d", i, *score);
		}
		else if(*score<1000){
			sprintf(scoreTxt, "%d. 0%d", i, *score);
		}
		else{
			sprintf(scoreTxt, "%d. %d", i, *score);
		}

		ST7735_DrawString_wS(0x0004, yPixel, scoreTxt, col, 1 );
		score++;
		yPixel+=8;
	}
}

uint8_t writeLn(char *text, uint16_t color, uint8_t yPixel){
	uint8_t NrOfChar=0;
	while(*text)
	{
		NrOfChar++;
		text++;
	}
	text = text-NrOfChar;
	if(NrOfChar>10)
	{
		return 0x01;
	}
	else
	{
		ST7735_DrawString_wS(0x0004, yPixel, text, color, 2 );
		return 0;
	}
}

void setPreview(uint8_t block)
{
	uint16_t setFields = 0, color=0, x=0, y=0;

	switch(block){

	case 0: setFields = 0x0000;		// Empty
			color = ST7735_BLACK;
			x = 0x0056;
			y = 0x0008;
			break;
	case 1: setFields = 0x0F00;		// I
			color = ST7735_CYAN;
			x = 0x0056;
			y = 0x0008;
			break;
	case 2: setFields = 0x0660;		// O
			color = ST7735_YELLOW;
			x = 0x0056;
			y = 0x0008;
			break;
	case 3: setFields = 0x0360;		// S
			color = ST7735_GREEN;
			x = 0x005A;
			y = 0x0008;
			break;
	case 4: setFields = 0x0630;		// Z
			color = ST7735_RED;
			x = 0x005A;
			y = 0x0008;
			break;
	case 5: setFields = 0x0710;		// J
			color = ST7735_BLUE;
			x = 0x005A;
			y = 0x0008;
			break;
	case 6: setFields = 0x0740;		// L
			color = ST7735_ORANGE;
			x = 0x005A;
			y = 0x0008;
			break;
	case 7: setFields = 0x0720;		// T
			color = ST7735_MAGENTA;
			x = 0x005A;
			y = 0x0008;
			break;



	}

	drawPreview(x, y, setFields, color);

}

void drawPreview(uint16_t x, uint16_t y, uint16_t setFields, uint16_t color)
{
	if(color != ST7735_CYAN && color !=ST7735_YELLOW)
	{
		ST7735_FillRectangle((0x0056), (0x0018), 0x0004, 0x0008, ST7735_BLACK);
	}
	for(uint8_t i = 0; i<=3; i++)
	{
		for(uint8_t u = 0; u<=3; u++)
		{
			if(setFields & 0x0001)
			{
				ST7735_FillRectangle((x + (u*8)), (y + (i*8)), 0x0008, 0x0008, color);
			}
			else
			{
				ST7735_FillRectangle((x + (u*8)), (y + (i*8)), 0x0008, 0x0008, ST7735_BLACK);
			}
			setFields = setFields >> 1;
		}
	}
}


void drawField(uint8_t * fieldData){

	static uint8_t oldFieldData[200] = { 0 };
	uint8_t counter = 0;
	uint16_t color=0;

	for(uint8_t i = 0; i<=19; i++)
	{
		for(uint8_t u = 0; u<=9; u++)
		{

			if((*fieldData) != (oldFieldData[counter]))
			{
				color = getColor(*fieldData);
				ST7735_FillRectangle((0x0000 + (u*8)), (0x0000 + (i*8)), 0x0008, 0x0008, color);
				oldFieldData[counter]=*fieldData;
			}
			counter++;
			fieldData++;
		}
	}
}

uint16_t getColor(uint8_t color)
{
	uint16_t retColor;

	switch(color){

	case 1: 	retColor = ST7735_CYAN;
				break;
	case 2:		retColor = ST7735_YELLOW;
				break;
	case 3:		retColor = ST7735_GREEN;
				break;
	case 4:		retColor = ST7735_RED;
				break;
	case 5:		retColor = ST7735_BLUE;
				break;
	case 6:		retColor = ST7735_ORANGE;
				break;
	case 7:		retColor = ST7735_MAGENTA;
				break;
	case 8: 	retColor = ST7735_LIGHTGREEN;
				break;
	case 9:		retColor = ST7735_WHITE;
				break;
	default:	retColor = ST7735_BLACK;
				break;

	}

	return retColor;
}
