# $Id: Makefile,v 1.33 2003/09/30 05:23:13 sgust Exp $

all: ktaa.rom

ktaa.rom: ktaa_b0.obj ktaa_b1.obj ktaa_b2.obj ktaa_b3.obj
	cat $^ >$@

%.obj: %.p
	p2bin $< $@ -r \$$400-\$$fff

%.p: %.a48
	asl -a -u -q -i .. $< -o $@

%.lst: %.a48
	asl -a -u -q -i .. $< -o /dev/null -l >$@

%.i: %.pnm
	perl tools/ppmtosprite.pl $< >$@

list: ktaa_b0.lst ktaa_b1.lst ktaa_b2.lst ktaa_b3.lst

clean:
	rm -f ktaa_b0.p ktaa_b1.p ktaa_b2.p ktaa_b3.p
	rm -f ktaa_b0.obj ktaa_b1.obj ktaa_b2.obj ktaa_b3.obj
	rm -f ktaa_b0.lst ktaa_b1.lst ktaa_b2.lst ktaa_b3.lst
	rm -f *.i *.inc

checkends: ktaa_b0.a48 ktaa_b1.a48 ktaa_b2.a48 ktaa_b3.a48 switchmb0.h switchmb1.h charset.h common.h targets.h
	-@grep -l [[:space:]]$$ $^

# dependencies
ktaa_b0.p: common.h charset.h switchmb0.h switchmb1.h targets.h ufo.i disc.i bomber.i antenna.i double.i boomerang.i
ktaa_b1.p: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc flakes.h
ktaa_b2.p: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc
ktaa_b3.p: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc

ktaa_b0.lst: common.h charset.h switchmb0.h switchmb1.h targets.h ufo.i disc.i bomber.i antenna.i double.i boomerang.i
ktaa_b1.lst: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc flakes.h
ktaa_b2.lst: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc
ktaa_b3.lst: common.h charset.h switchmb0.h switchmb1.h ktaa_b0.inc
