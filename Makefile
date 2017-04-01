# Alan Gardin
# 01/04/2017

SUBDIRS = boot

all: $(SUBDIRS)

$(SUBDIRS):
	cd $@ && $(MAKE)

clean:
