TOPDIR ?= ..
PYCFLAGS = $(shell python3-config --cflags)
PYLDLAGS = $(shell python3-config --ldlags)
PYEXT = $(shell python3-config --extension-suffix)
LIBTARGETS = threering$(PYEXT)
TARGETS = $(LIBTARGETS)
SITEPKGS=$(shell python3-config --configdir | sed 's/config.*/site-packages/')

include $(TOPDIR)/Make.defaults

all : $(TARGETS)

VERSION = 0.1

threering$(PYEXT) : threering.c dso.c
	$(CC) $(CFLAGS) $(PYCFLAGS) $(PYLDFLAGS) $(LDFLAGS) \
		-Wl,-soname="$@.$(VERSION)" \
		-o $@ $^ -L$(TOPDIR)/lib -lthreering

%.so : %.so.$(VERSION)
	@echo -n
	@ln -vfs $< $@

include $(TOPDIR)/Make.rules

clean :
	@rm -vf *.o *.so *.so.*

install :
	$(INSTALL) -d -m 755 $(INSTALLROOT)$(SITEPKGS)
	for x in $(LIBTARGETS) ; do \
		$(INSTALL) -m 755 $$x $(INSTALLROOT)$(SITEPKGS) ; \
	done

.PHONY : all clean install
