#!/usr/bin/perl -w

# convert a ppm raw file into a 4 frame sprite anim for Videopac
# prints source to stdout
# image size 44 x 8 pixel, colordepth 24bpp, only 2 colors used
# written by Soeren Gust, sgust@ithh.informationstheater.de
# not very good commented, sorry.
# $Id: ppmtosprite.pl,v 1.3 2003/07/19 12:55:16 sgust Exp $

use strict;

open(FILE, $ARGV[0]) or die "Can't open file";

my ($filetype, $size, $color) = ("#", "#", "#");

while($filetype =~ /^#/) { chomp($filetype = <FILE>); }
if ($filetype ne "P6") { die "Wrong filetype"; }

while($size =~ /^#/) { chomp($size = <FILE>); }
if ($size ne "44 8") { die "Wrong size"; }

while($color =~ /^#/) { chomp($color = <FILE>); }
if ($color ne "255") { die "Wrong colordepth"; }

$/ = \3;

my @bitmap;
my $temp;

for my $y (0..7) {
	for my $x (0..43) {
		$temp = <FILE>;
		if (unpack("H6", $temp) eq "2538b0") {
			$bitmap[$y] .= '0';
		} else {
			$bitmap[$y] .= '1';
		}
	}
}

for my $i (0..3) {
	print "\t; Frame $i\n";
	for my $y (0..7) {
		print "\tdb\t", substr($bitmap[$y], $i*12, 8), "b\n";
	}
}
