//
// Created by thibault on 28/12/15.
//

/*
#include "drivers/fs/fat/diskio.h"
#include "drivers/fs/fat/ff.h"
#include "drivers/fs/fat/ff_conf.h"
#include "drivers/fs/fat/integer.h"
*/

#include "hal/mmcsd/hs_mmcsd.h"
#include "soc_AM335x.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Test du système de fichier :\n");

    char * data = malloc(sizeof(char) * 3000);

    printf("Allocation : Ok\n");
    HSMMCSDDataGet(SOC_MMCHS_0_REGS, data, 3000);
    printf(data);

    return 0;
}

