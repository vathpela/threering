LIBTARGETS = threeringmodule.so
TARGETS = $(LIBTARGETS)
TOPDIR ?= ..
PYCFLAGS = $(shell python3-config --cflags)
PYLDLAGS = $(shell python3-config --ldlags)

include $(TOPDIR)/Make.defaults

all : $(TARGETS)

threeringmodule.so.$(VERSION) : threeringmodule.o
	$(CC) $(CFLAGS) $(PYLDFLAGS) $(LDFLAGS) \
		-Wl,-soname="$@" -o $@ $^ -L$(TOPDIR)/lib -lthreering

threeringmodule.o : threeringmodule.c
	$(CC) $(CFLAGS) $(PYCFLAGS) -c -o $@ $(filter %.c,$^)

%.so : %.so.$(VERSION)
	@echo -n
	@ln -vfs $< $@

include $(TOPDIR)/Make.rules

clean :
	@rm -vf $(TARGETS) *.o *.so *.so.*

install :
	$(INSTALL) -d -m 755 $(INSTALLROOT)$(LIBDIR)
	for x in $(LIBTARGETS) ; do \
		$(INSTALL) -m 755 $$x $(INSTALLROOT)$(LIBDIR) ; \
	done
	$(INSTALL) -d -m 755 $(INSTALLROOT)$(PCDIR)
	for x in $(PCTARGETS) ; do \
		$(INSTALL) -m 0644 $$x $(INSTALLROOT)$(PCDIR) ; \
	done

.PHONY : all clean install
