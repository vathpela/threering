TOPDIR = $(shell echo $$PWD)

include $(TOPDIR)/Make.defaults

SUBDIRS = lib
VERSION = 0.1

all : $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@ TOPDIR=$(TOPDIR) SRCDIR=$(TOPDIR)/$@/ ARCH=$(ARCH)

clean :
	@for x in $(SUBDIRS) ; do $(MAKE) -C $${x} TOPDIR=$(TOPDIR) SRCDIR=$(TOPDIR)/$$x/ ARCH=$(ARCH) $@ ; done

install :
	@for x in $(SUBDIRS) ; do $(MAKE) -C $${x} TOPDIR=$(TOPDIR) SRCDIR=$(TOPDIR)/$$x/ ARCH=$(ARCH) $@ ; done

.PHONY: $(SUBDIRS) clean install

include $(TOPDIR)/Make.rules

GITTAG = $(VERSION)

test-archive:
	@rm -rf /tmp/libthreering-$(VERSION) /tmp/libthreering-$(VERSION)-tmp
	@mkdir -p /tmp/libthreering-$(VERSION)-tmp
	@git archive --format=tar $(shell git branch | awk '/^*/ { print $$2 }') | ( cd /tmp/libthreering-$(VERSION)-tmp/ ; tar x )
	@git diff | ( cd /tmp/libthreering-$(VERSION)-tmp/ ; patch -s -p1 -b -z .gitdiff )
	@mv /tmp/libthreering-$(VERSION)-tmp/ /tmp/libthreering-$(VERSION)/
	@dir=$$PWD; cd /tmp; tar -c --bzip2 -f $$dir/libthreering-$(VERSION).tar.bz2 libthreering-$(VERSION)
	@rm -rf /tmp/libthreering-$(VERSION)
	@echo "The archive is in libthreering-$(VERSION).tar.bz2"
	
archive:
	git tag $(GITTAG) refs/heads/master
	@rm -rf /tmp/libthreering-$(VERSION) /tmp/libthreering-$(VERSION)-tmp
	@mkdir -p /tmp/libthreering-$(VERSION)-tmp
	@git archive --format=tar $(GITTAG) | ( cd /tmp/libthreering-$(VERSION)-tmp/ ; tar x )
	@mv /tmp/libthreering-$(VERSION)-tmp/ /tmp/libthreering-$(VERSION)/
	@dir=$$PWD; cd /tmp; tar -c --bzip2 -f $$dir/libthreering-$(VERSION).tar.bz2 libthreering-$(VERSION)
	@rm -rf /tmp/libthreering-$(VERSION)
	@echo "The archive is in libthreering-$(VERSION).tar.bz2"
