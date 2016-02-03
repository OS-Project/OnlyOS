/*
 * Created by Thibault PIANA, adapted from starterware
 */
#include "hal/armv7a/cache.h"
#include "hal/mmcsd/hs_mmcsd.h"
#include "soc_AM335x.h"

#include "drivers/fs/fat/ff.h"
#include "drivers/fs/fs.h"

#include <stdio.h>



/*****************************************************************************
Defines the size of the buffers that hold the path, or temporary data from
the memory card.  There are two buffers allocated of this size.  The buffer
size must be large enough to hold the longest expected full path name,
including the file name, and a trailing null character.
******************************************************************************/
#define PATH_BUF_SIZE   512

/* Defines size of the buffers that hold temporary data. */
#define DATA_BUF_SIZE   64 * (2 * 512)
/*****************************************************************************
Defines the size of the buffer that holds the command line.
******************************************************************************/
#define CMD_BUF_SIZE    512

/*****************************************************************************
Current FAT fs state.
******************************************************************************/
static FATFS g_sFatFs;  //__attribute__ ((aligned (SOC_CACHELINE_SIZE)));

static DIR g_sDirObject;
static FILINFO g_sFileInfo;

static FIL g_sFileObject;  //__attribute__ ((aligned (SOC_CACHELINE_SIZE)));
static FIL fileObjectWrite;  //__attribute__ ((aligned (SOC_CACHELINE_SIZE)));


/*****************************************************************************
This buffer holds the full path to the current working directory.  Initially
it is root ("/").
******************************************************************************/
static char g_cCwdBuf[PATH_BUF_SIZE] = "/";

/*****************************************************************************
A temporary data buffer used for write file paths
******************************************************************************/
static char g_cWrBuf[PATH_BUF_SIZE] = "/";

/*****************************************************************************
A temporary data buffer used when manipulating file paths, or reading data
from the memory card.
******************************************************************************/
static char g_cTmpBuf[PATH_BUF_SIZE];// __attribute__ ((aligned (SOC_CACHELINE_SIZE)));

/*****************************************************************************
A temporary data buffer used for reading data from or writing data
to the memory card.
******************************************************************************/
static char g_cDataBuf[DATA_BUF_SIZE];// __attribute__ ((aligned (SOC_CACHELINE_SIZE)));

/*****************************************************************************
The buffer that holds the command line.
******************************************************************************/
static char g_cCmdBuf[CMD_BUF_SIZE];

int Cmd_ls()
{
    printf("Begin : ok\n");
    unsigned long ulTotalSize;
    unsigned long ulFileCount;
    unsigned long ulDirCount;
    FRESULT fresult;
    FATFS *pFatFs;
    printf("Initialisation : ok\n");
    /*
    ** Open the current directory for access.
    */
    printf("Open %s\n", g_cCwdBuf);
    fresult = f_opendir(&g_sDirObject, g_cCwdBuf);
    /*
    ** Check for error and return if there is a problem.
    */
    if(fresult != FR_OK)
        return(fresult);

    printf("Open dir : ok\n");
    ulTotalSize = 0;
    ulFileCount = 0;
    ulDirCount = 0;

    /*
    ** Enter loop to enumerate through all directory entries.
    */
    while(1)
    {
        /*
        ** Read an entry from the directory.
        */
        fresult = f_readdir(&g_sDirObject, &g_sFileInfo);

        /*
        ** Check for error and return if there is a problem.
        */
        if(fresult != FR_OK)
            return(fresult);
        printf("Read dir : ok \n");
        /*
        ** If the file name is blank, then this is the end of the listing.
        */
        if(!g_sFileInfo.fname[0])
            break;

        /*
        ** If the attribute is directory, then increment the directory count.
        */
        if(g_sFileInfo.fattrib & AM_DIR)
            ulDirCount++;

            /*
            ** Otherwise, it is a file.  Increment the file count, and add in the
            ** file size to the total.
            */
        else
        {
            ulFileCount++;
            ulTotalSize += g_sFileInfo.fsize;
        }

        /*
        ** Print the entry information on a single line with formatting to show
        ** the attributes, date, time, size, and name.
        */
        printf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9u  %s\n",
               (g_sFileInfo.fattrib & AM_DIR) ? 'D' : '-',
               (g_sFileInfo.fattrib & AM_RDO) ? 'R' : '-',
               (g_sFileInfo.fattrib & AM_HID) ? 'H' : '-',
               (g_sFileInfo.fattrib & AM_SYS) ? 'S' : '-',
               (g_sFileInfo.fattrib & AM_ARC) ? 'A' : '-',
               (g_sFileInfo.fdate >> 9) + 1980,
               (g_sFileInfo.fdate >> 5) & 15,
               g_sFileInfo.fdate & 31,
               (g_sFileInfo.ftime >> 11),
               (g_sFileInfo.ftime >> 5) & 63,
               g_sFileInfo.fsize,
               g_sFileInfo.fname);
    }

    /*
    ** Print summary lines showing the file, dir, and size totals.
    */
    printf("\n%4u File(s),%10u bytes total\n%4u Dir(s)",
           ulFileCount, ulTotalSize, ulDirCount);

    /*
    ** Get the free space.
    */
    fresult = f_getfree("/", (DWORD *)&ulTotalSize, &pFatFs);

    /*
    ** Check for error and return if there is a problem.
    */
    if(fresult != FR_OK)
        return(fresult);

    /*
    ** Display the amount of free space that was calculated.
    */
    printf(", %10uK bytes free\n",
           ulTotalSize * pFatFs->sects_clust / 2);

    /*
    ** Made it to here, return with no errors.
    */
    return(0);
}