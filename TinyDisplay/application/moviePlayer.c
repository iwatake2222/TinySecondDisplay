/*
 * moviePlayer.c
 *
 * Created: 2016-03-05 10:22:32 AM
 *  Author: take-iwiw
 */ 
#include <avr/io.h>
#include "../myCommon.h"
#include <util/delay.h>
#include "../myLibraries/myStdio.h"
#include "../myLibraries/myTimer.h"
#include "../myLibraries/myVideo.h"
#include "../color/colorRGB.h"
#include "../petitFatFS/ff.h"

/*** Internal Const Values ***/
#define WIDTH  128
#define HEIGHT 128

/*** Internal Static Variables ***/
static FATFS FatFs;
static FIL Fil;

/*** Internal Function Declarations ***/
static void drawFile(char* filename);
static void drawFileLineBuff(char* filename);
static uint8_t getNextFile(DIR *dir, char *filename);
static uint8_t getNextDir(DIR *dir, char *dirname);
static uint8_t isSkip();

/*** External Function Defines ***/
void moviePlayerInit()
{
	f_mount(0, "", 0);
	f_mount(&FatFs, "", 0);		/* Give a work area to the default drive */		
}

void moviePlayerLoop()
{
	DIR dirRoot;
	char dirname[14];
	uint8_t ret = f_opendir(&dirRoot, "/");
	if(ret != 0) printDec(ret);
	while(getNextDir(&dirRoot, dirname) > 0) {
		//printPos("          ", 0, 0);
		//printPos(dirname, 0, 0);
		f_chdir(dirname);
		DIR dir;
		char filename[14];
		f_opendir(&dir, "");
		while(getNextFile(&dir, filename) > 0) {
			printPos("          ", 0, 0);
			printPos(filename, 0, 0);
			drawFileLineBuff(filename);
			//drawFile(filename);
			//getchar();
			if(isSkip() != 0) break;	
		}
		f_closedir(&dir);
		f_chdir("/");
	}
	f_closedir(&dirRoot);
}

/*** Internal Function Definitions ***/
static uint8_t isSkip()
{
	char key;
	uint8_t isInput = getcharTry(&key);
	if(isInput != 0) {
		if( key == 'n' ) return 1;
		if( key == 'p') getchar();
	}
	return 0;
	
}

static void drawFile(char* filename)
{
	uint8_t ret = f_open(&Fil, filename, FA_READ ) ;
	if(ret != FR_OK) {
		printDec(ret);
		return;
	}
	setVideoArea(0, 0, WIDTH, HEIGHT);
	startFrame();
	for(uint16_t y = 0; y < WIDTH*HEIGHT; y++){
		uint8_t buffer[2];
		UINT bw;
		f_read(&Fil, buffer, 2, &bw);
		drawPixel(buffer[0], buffer[1]);
	}
	f_close(&Fil);
	uint8_t time = stopFrame();
	printDecPos(1000/time, 0, 1);
}

static void drawFileLineBuff(char* filename)
{
	uint8_t ret = f_open(&Fil, filename, FA_READ ) ;
	if(ret != FR_OK) {
		printDec(ret);
		return;
	}
	setVideoArea(0, 0, WIDTH, HEIGHT);
	startFrame();
	for(uint8_t y = 0; y < HEIGHT; y++){
		uint8_t *buffer = getLineBuffer();
		UINT bw;
		f_read(&Fil, buffer, WIDTH*2, &bw);
		//drawLineBuffer(1);
	}
	f_close(&Fil);
	uint8_t time = stopFrame();
	printDecPos(1000/time, 0, 1);
	//getchar();
}

static uint8_t getNextFile(DIR *dir, char *filename)
{
	while(1){
		FILINFO fno;
		uint8_t res = f_readdir(dir, &fno);
		if (res != FR_OK || fno.fname[0] == 0) return 0;
		if (fno.fname[0] == '.') continue;

		if (fno.fattrib & AM_DIR) {
			continue;
		} else {
			memcpy(filename, fno.fname, 14);
			return 1;
		}
	}
}

static uint8_t getNextDir(DIR *dir, char *dirname)
{
	while(1){
		FILINFO fno;
		uint8_t res = f_readdir(dir, &fno);
		if (res != FR_OK || fno.fname[0] == 0) return 0;
		if (fno.fname[0] == '.') continue;

		if ( (fno.fattrib & AM_DIR) && ( (fno.fattrib & AM_SYS) != AM_SYS) ) {
			memcpy(dirname, fno.fname, 14);
			return 1;
		} else {
			continue;
		}
	}
}
