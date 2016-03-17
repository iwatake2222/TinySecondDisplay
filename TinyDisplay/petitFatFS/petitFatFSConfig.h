/*
 * petitFatFSConfig.h
 *
 * Created: 2016-03-05 10:34:22 AM
 *  Author: user
 */ 


#ifndef PETITFATFSCONFIG_H_
#define PETITFATFSCONFIG_H_

/* communication settings */
//#define FATFS_MCC_USE_GPIO
//#define FATFS_MCC_USE_SIO

/* io settings */
#ifdef FATFS_MCC_USE_GPIO
#define FATFS_MMC_CS_PORT PORTC
#define FATFS_MMC_CK_PORT PORTC
#define FATFS_MMC_MOSI_PORT PORTC
#define FATFS_MMC_MISO_PORT PORTC
#define FATFS_MMC_CS_DDR DDRC
#define FATFS_MMC_CK_DDR DDRC
#define FATFS_MMC_MOSI_DDR DDRC
#define FATFS_MMC_MISO_DDR DDRC
#define FATFS_MMC_CS_BIT 3
#define FATFS_MMC_CK_BIT 2
#define FATFS_MMC_MOSI_BIT 1
#define FATFS_MMC_MISO_BIT 0

#define FATFS_MCC_GPIO_CK_WAIT 2

#endif


#endif /* PETITFATFSCONFIG_H_ */