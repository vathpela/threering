LIBTARGETS = libthreering.so
PCTARGETS = threering.pc
TARGETS = $(LIBTARGETS) $(PCTARGETS)
TOPDIR ?= ..

include $(TOPDIR)/Make.defaults

all : $(TARGETS)

threering.pc : threering.pc.in
	sed -e "s,@@VERSION@@,$(VERSION),g" \
	    -e "s,@@LIBDIR@@,$(libdir),g" \
		$^ > $@

libthreering.o : threering.h ../include/threering.h util.h

include $(TOPDIR)/Make.rules

clean :
	@rm -vf $(TARGETS) *.o

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
