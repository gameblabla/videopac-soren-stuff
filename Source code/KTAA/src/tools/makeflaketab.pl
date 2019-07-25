#!/usr/bin/perl
#
# output a snow flake table for the ice level
# uses uninitialized variables, really bad coding

# $Id: makeflaketab.pl,v 1.1 2003/09/30 05:22:42 sgust Exp $

use strict;

# number of snow flakes
my $flakes = 43;
my @field;

printf "; automatically generated flakes.h\n; \$Id\$\n";

my $i = 0;

while($i < $flakes) {
	my $x = 1+ int rand 38;
	my $y = 32 + int rand 15;
	if ($field[40*$y+$x] + $field[40*$y+$x+1] + $field[40*$y+$x+40] + $field[40*$y+$x+41] == 0) {
		# mark direct used fields
		$field[40*$y+$x] = $field[40*$y+$x+1] = $field[40*$y+$x+40] = $field[40*$y+$x+41] = 1;
		# mark surrounding fields, no diagonals
		$field[40*$y+$x-40] = $field[40*$y+$x-39] = $field[40*$y+$x+80] = $field[40*$y+$x+81] = 1;
		$field[40*$y+$x-1] = $field[40*$y+$x+2] = $field[40*$y+$x+39] = $field[40*$y+$x+41+42] = 1;
		printf "\tdb\t0%02xh,0%02xh", $x, $y;
		if (rand() > 0.75) { print " | 080h\n" } else { print "\n"; }
		$i++;
	}
}
printf "\tdb\t0\n";
