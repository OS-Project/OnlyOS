/*
    * Created by Thibault on 16/01/2016.
*/

#include "kernel/kernel.h"
#include "kernel/config.h"
#include "drivers/fs/fs.h"
#include "drivers/fs/fat/ff.h"

#include <stdlib.h>
#include <stdio.h>


int klaunch()
{
    FATFS mmc_sd;

    printf("Mount SD card : \n");
    f_mount(0, &mmc_sd);

    printf("Show root directory : \n");
    int result = Cmd_ls();

    printf("Result : %d", result);
    return 0;
}