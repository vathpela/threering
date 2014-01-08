TOPDIR ?= ..

include $(TOPDIR)/Make.defaults

all clean :

include $(TOPDIR)/Make.rules

install :
	$(INSTALL) -d -m 755 $(INSTALLROOT)$(INCDIR)
	for x in *.h ; do \
		$(INSTALL) -m 644 $$x $(INSTALLROOT)$(INCDIR) ; \
	done

.PHONY : all clean install
