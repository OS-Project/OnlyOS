# Adapted by Thibault PIANA & Alan Gardin
# First modification : 20/10/2015
# Last modification : 22/10/2015

ROOT=../
FILE_NAME = lib_hal.a

DEVICE=am335x
EVM=beaglebone

include ${ROOT}/makedefs

SOURCE=${HAL_SRC}/dmtimer.c	 \
       ${HAL_SRC}/uart_irda_cir.c   \
       ${HAL_SRC}/ecap.c	    \
       ${HAL_SRC}/ehrpwm.c	  \
       ${HAL_SRC}/mcspi.c	   \
       ${HAL_SRC}/mcasp.c	   \
       ${HAL_SRC}/mdio.c	    \
       ${HAL_SRC}/phy.c	     \
       ${HAL_SRC}/cpsw.c	    \
       ${HAL_SRC}/hsi2c.c	   \
       ${HAL_SRC}/gpio_v2.c	 \
       ${HAL_SRC}/watchdog.c	\
       ${HAL_SRC}/edma.c	    \
       ${HAL_SRC}/rtc.c	     \
       ${HAL_SRC}/raster.c	  \
       ${HAL_SRC}/gpmc.c	    \
       ${HAL_SRC}/elm.c	     \
       ${HAL_SRC}/tsc_adc.c	 \
       ${HAL_SRC}/hs_mmcsd.c	\
       ${HAL_SRC}/mailbox.c	 \
#       ${HAL_SRC}/usb.c	     \
#       ${HAL_SRC}/cppi41dma.c       \
       ${HAL_SRC}/dcan.c
#       ${HAL_SRC}/usbphyGS70.c

all: debug release

debug:
	mkdir -p Debug
	$(CC) $(CFLAGS) -g $(SOURCE)
	$(AR) $(ARFLAGS) Debug/${FILE_NAME} *.o*
	@mv *.o* Debug/
	@mkdir -p ${HAL_BIN}/Debug
	@cp Debug/${FILE_NAME} ${HAL_BIN}/Debug/${FILE_NAME}

release:
	mkdir -p Release
	$(CC) $(CFLAGS) -g -O2 $(SOURCE)
	$(AR) $(ARFLAGS) Release/${FILE_NAME} *.o*
	@mv *.o* Release/
	@mkdir -p ${HAL_BIN}/Release
	@cp Release/${FILE_NAME} ${HAL_BIN}/Release/${FILE_NAME}

clean:
	@rm -rf Debug Release ${HAL_BIN}/Debug ${HAL_BIN}/Release


