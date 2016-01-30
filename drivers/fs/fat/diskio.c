/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
/*
 * Modified by PIANA Thibault, adapted from Starterware lib
 */
#include "hal/mmcsd/hs_mmcsd.h"
#include "hw_types.h"


/* Include mmcsdlib */
#include "libs/mmcsdlib/mmcsd_proto.h"
#include "libs/mmcsdlib/hs_mmcsdlib.h"

/* Drivers */
#include "drivers/fs/fat/diskio.h"
#include "drivers/fs/fat/ff.h"

typedef struct _fatDevice
{
    /* Pointer to underlying device/controller */
    void *dev;

    /* File system pointer */
    FATFS *fs;

    /* state */
    unsigned int initDone;

}fatDevice;


#define DRIVE_NUM_MMCSD     0
#define DRIVE_NUM_MAX      2

/*
 * MMC0 = SD
 * MMC1 = eMMc
 */

fatDevice fat_devices[DRIVE_NUM_MAX];
/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_initialize(
        BYTE bValue)                /* Physical drive number (0) */
{
    unsigned int status;

    if (DRIVE_NUM_MAX <= bValue)
        return STA_NODISK;

    if ((DRIVE_NUM_MMCSD == bValue) && (fat_devices[bValue].initDone != 1)) {
        mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[bValue].dev;

        /* SD Card init */
        status = MMCSDCardInit(card->ctrl);

        if (status == 0) /* Card Init Failed */
            return STA_NOINIT;
        else
        {
            /* Set bus width */
            if (card->cardType == MMCSD_CARD_SD)
                MMCSDBusWidthSet(card->ctrl);

            /* Transfer speed */
            MMCSDTranSpeedSet(card->ctrl);
        }

        fat_devices[bValue].initDone = 1;
    }

    return 0;
}

/*-----------------------------------------------------------------------*/
/* Returns the current status of a drive                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
        BYTE drv)                   /* Physical drive number (0) */
{
    return 0;
}

/*-----------------------------------------------------------------------*/
/* This function reads sector(s) from the disk drive                     */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
        BYTE drv,               /* Physical drive number (0) */
        BYTE* buff,             /* Pointer to the data buffer to store read data */
        DWORD sector,           /* Physical drive number (0) */
        BYTE count)             /* Sector count (1..255) */
{
    if (drv == DRIVE_NUM_MMCSD)
    {
        mmcsdCardInfo *card = fat_devices[drv].dev;

        /* READ BLOCK */
        if (MMCSDReadCmdSend(card->ctrl, buff, sector, count) == 1)
            return RES_OK;
    }

    return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* This function writes sector(s) to the disk drive                     */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE == 1
    DRESULT disk_write (
        BYTE ucDrive,           /* Physical drive number (0) */
        const BYTE* buff,       /* Pointer to the data to be written */
        DWORD sector,           /* Start sector number (LBA) */
        BYTE count)             /* Sector count (1..255) */
    {
        if (ucDrive == DRIVE_NUM_MMCSD)
        {
            mmcsdCardInfo *card = fat_devices[ucDrive].dev;
            /* WRITE BLOCK */
            if(MMCSDWriteCmdSend(card->ctrl,(BYTE*) buff, sector, count) == 1)
                return RES_OK;
        }

        return RES_ERROR;
    }
#endif /* _USE_WRITE */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
        BYTE drv,               /* Physical drive number (0) */
        BYTE ctrl,              /* Control code */
        void *buff)             /* Buffer to send/receive control data */
{
    return RES_OK;
}

/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support a real time clock.          */

DWORD get_fattime (void)
{
    return    ((2016UL-1980) << 25) // Year = 2016
              | (1UL << 21)           // Month = January
              | (1UL << 16)           // Day = 1
              | (12U << 11)           // Hour = 12
              | (0U << 5)            // Min = 0
              | (0U >> 1)             // Sec = 0
            ;
}
