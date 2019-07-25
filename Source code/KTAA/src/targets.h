; Target macro declarations
;
; $Id: targets.h,v 1.58 2003/08/11 12:46:07 sgust Exp $

; Copyright (C) 2003 by Soeren Gust, sgust@ithh.informationstheater.de

; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

; You can always get the latest version at http://soeren.informationstheater.de

; This is written for asl, see <http://www.alfsembler.de>. I use several
; special features (macros, section) of asl, so using other assemblers
; requires a lot of porting.

; ROM access routines for target data

targetaccess macro level

gettarget_level label $

	section gettarget_level
	mov	a,r3
	movp	a,@a
	inc	r3
	ret
	endsection gettarget_level

copyetarget_level label $

	section copyetarget_level
	mov	a,r3
	movp	a,@a
	movx	@r0,a
	inc	r3
	inc	r0
	djnz	r2,copyetarget_level
	ret
	endsection copyetarget_level

copyitarget_level label $

	section copyitarget_level
	mov	a,r3
	movp	a,@a
	mov	@r0,a
	inc	r3
	dec	r0
	djnz	r2,copyitarget_level
	ret
	endsection copyitarget_level

	endm

; ROM structure for target drawing routine
;  1 byte target variable
;  1 byte destination (char/quad)
;  1 byte length
;  * byte data for target!=0
;  * byte data for target==0

; A single tree
; uses 2 chars
tree	macro target, x, ch
	db	target, ch, 8
	chrdef	x, (GROUNDLEVEL - 006h), yellow, 014h, 1
	chrdef	x, (GROUNDLEVEL - 010h), green, 031h, 2
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; 4 trees
; uses 2 quads
forest	macro target, x, quad
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 010h), green, 031h, 2
	chrdef	x, (GROUNDLEVEL - 010h), black, 00ch, 2

	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL - 010h), green, 031h, 2
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 2

	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL - 010h), green, 031h, 2
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 2

	db	target+3, quad+14, 2
	chrdef2	(GROUNDLEVEL - 010h), green, 031h, 2
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 2

	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 006h), yellow, 014h, 1
	chrdef	x, (GROUNDLEVEL - 006h), black, 00ch, 1

	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 006h), yellow, 014h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1

	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 006h), yellow, 014h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1

	db	target+3, quad+30, 2
	chrdef2	(GROUNDLEVEL - 006h), yellow, 014h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	endm

; 1 house
; uses 4 chars
house	macro target, x, ch, color
	db	target, ch, 16
	; left roof
	chrdef	x, (GROUNDLEVEL - 016h), color, 038h, 0
	; right roof
	chrdef	(x+8), (GROUNDLEVEL - 016h), color, 039h, 0
	; left base
	chrdef	x, (GROUNDLEVEL - 008h), color, 02fh, 0
	; right base
	chrdef	(x+8), (GROUNDLEVEL - 008h), color, 02fh, 0
	; empty space
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; 4 houses
; uses 4 quads
hgroup	macro target, x, quad, col1, col2, col3
	; roof 1
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 016h), col1, 038h, 0
	chrdef	x, (GROUNDLEVEL - 016h), black, 00ch, 0
	db	target, quad+16, 4
	chrdef	(x+8), (GROUNDLEVEL - 016h), col1, 039h, 0
	chrdef	(x+8), (GROUNDLEVEL - 016h), black, 00ch, 0

	; base 1
	db	target, quad+32, 4
	chrdef	x, (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	x, (GROUNDLEVEL - 008h), black, 00ch, 0
	db	target, quad+48, 4
	chrdef	(x+8), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	(x+8), (GROUNDLEVEL - 008h), black, 00ch, 0

	; space between 1 and 2
	db	eram_permtarg, quad+6, 2
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	db	eram_permtarg, quad+38, 2
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0

	; roof 2
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 016h), col2, 038h, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	db	target+1, quad+10, 2
	chrdef2	(GROUNDLEVEL - 016h), col2, 039h, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0

	; base 2
	db	target+1, quad+54, 2
	chrdef2	(GROUNDLEVEL - 008h), col2, 02fh, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	target+1, quad+42, 2
	chrdef2	(GROUNDLEVEL - 008h), col2, 02fh, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0

	; space between 2 and 3
	db	eram_permtarg, quad+26, 2
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	db	eram_permtarg, quad+58, 2
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0

	; roof 3
	db	target+2, quad+14, 2
	chrdef2	(GROUNDLEVEL - 016h), col3, 038h, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0
	db	target+2, quad+30, 2
	chrdef2	(GROUNDLEVEL - 016h), col3, 039h, 0
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 0

	; base 3
	db	target+2, quad+46, 2
	chrdef2	(GROUNDLEVEL - 008h), col3, 02fh, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	target+2, quad+62, 2
	chrdef2	(GROUNDLEVEL - 008h), col3, 02fh, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	endm

; several pyramids
; uses 4 quads, 4 chars
pyramid	macro target, x, quad, ch, color
	; base of big pyramid
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 008h), color, 038h, 0
	chrdef	x, (GROUNDLEVEL - 008h), black, 00ch, 0
	db	target, quad+32, 4
	chrdef	(x+8), (GROUNDLEVEL - 008h), color, 02fh, 0
	chrdef	(x+8), (GROUNDLEVEL - 008h), black, 00ch, 0
	db	target, quad+22, 2
	chrdef2	(GROUNDLEVEL - 008h), color, 02fh, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	target, quad+38, 2
	chrdef2	(GROUNDLEVEL - 008h), color, 039h, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0

	; small pyramid plus space
	db	eram_permtarg, quad+26, 2
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	target+1, quad+42, 2
	chrdef2	(GROUNDLEVEL - 008h), color, 038h, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	target+1, quad+30, 2
	chrdef2	(GROUNDLEVEL - 008h), color, 039h, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	db	eram_permtarg, quad+46, 2
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0

	; mid part of big pyramid, tricky quad cut off usage
	db	target, quad, 4
	chrdef	(x+2), (GROUNDLEVEL - 00ch), color, 038h, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 00ch), color, 039h, 4
	chrdef2	0f8h, black, 0, 0
	db	target, quad+10, 2
	chrdef2	(GROUNDLEVEL - 00ch), black, 00ch, 0
	chrdef2	0f8h, black, 0, 0
	db	target, quad+14, 2
	chrdef2	(GROUNDLEVEL - 00ch), black, 00ch, 5
	chrdef2	0f8h, black, 0, 0

	; 3 smaller pyramids, tricky quad cut off
	db	target+2, quad+48, 4
	chrdef	(x+64), (GROUNDLEVEL - 004h), color, 037h, (-1)
	chrdef	(x+64), (GROUNDLEVEL - 004h), black, 00ch, 0
	db	target+3, quad+54, 2
	chrdef2	(GROUNDLEVEL - 004h), color, 037h, (-2)
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 0
	db	target+4, quad+58, 2
	chrdef2	(GROUNDLEVEL - 004h), color, 037h, (-2)
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 0
	db	eram_permtarg, quad+62, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2

	; center/top part part of big pyramid
	db	target, ch, 12
	chrdef	(x+10), (GROUNDLEVEL - 00ch), color, 02fh, 5
	chrdef	(x+9), (GROUNDLEVEL - 01ah), color, 038h, 0
	chrdef	(x+15), (GROUNDLEVEL - 01ah), color, 039h, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0

	; top of small pyramid
	db	target+1, ch+12, 4
	chrdef	(x+44), (GROUNDLEVEL - 00ch), color, 00dh, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; island with 3 small houses and a tree
; uses 4 quads, 1 char
island macro target, x, quad, char, col1, col2, col3, col4
	; island around houses
	db	eram_permtarg, quad+32, 4
	chrdef x, (GROUNDLEVEL + 002h), col1, 038h, 5
	chrdef x, (GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+38, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+42, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+46, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5

	; island around houses
	db	eram_permtarg, quad+48, 4
	chrdef (x+8), (GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef (x+8), (GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+54, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+58, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	eram_permtarg, quad+62, 2
	chrdef2	(GROUNDLEVEL + 002h), col1, 02fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black,00ch, 5

	; last part of island
	db	eram_permtarg, char, 4
	chrdef (x+040h), (GROUNDLEVEL + 002h), col1, 039h, 5
	chrdef (x+040h), (GROUNDLEVEL + 002h), black, 00ch, 5

	; house bases, last quad tree base
	db	target, quad+16, 4
	chrdef	(x+8), (GROUNDLEVEL - 00ah), col2, 02fh, 1
	chrdef	(x+8), (GROUNDLEVEL - 00ah), black, 00ch, 1
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 00ah), col3, 02fh, 1
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 1
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 00ah), col4, 02fh, 1
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 1
	db	target+3, quad+30, 2
	chrdef2	(GROUNDLEVEL - 00ah), yellow, 014h, 1
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 1

	; house roofs, last quad used for cut-off and tree top
	db	target, quad, 4
	chrdef	(x+8), (GROUNDLEVEL - 014h), col2, 037h, (-1)
	chrdef	(x+8), (GROUNDLEVEL - 014h), black, 00ch, 0
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL - 014h), col3, 037h, (-1)
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 0
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL - 014h), col4, 037h, (-1)
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 0
	db	target+3, quad+14, 2
	chrdef2	(GROUNDLEVEL - 014h), green, 031h, 2
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 2
	endm

; mini submarine
; uses 3 chars
minisub macro target, x, char, col1
	db	target, char, 12
	chrdef x, (GROUNDLEVEL - 000h), col1, 038h, 4
	chrdef (x+8), (GROUNDLEVEL - 000h), col1, 039h, 4
	chrdef (x+7), (GROUNDLEVEL - 004h), col1, 027h, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; 4 hollow rockets
; uses 4 quads
; UNUSED, no hit table
rockets4 macro target, x, quad, col1, col2, col3, col4
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 002h), col1, 022h, 3
	chrdef	x, (GROUNDLEVEL - 002h), black, 00ch, 3
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL - 002h), col2, 022h, 3
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 3
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL - 002h), col3, 022h, 3
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 3
	db	target+3, quad+14, 2
	chrdef2	(GROUNDLEVEL - 002h), col4, 022h, 3
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 3
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 010h), col1, 015h, 0
	chrdef	x, (GROUNDLEVEL - 010h), black, 00ch, 0
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 010h), col2, 015h, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 010h), col3, 015h, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	target+3, quad+30, 2
	chrdef2	(GROUNDLEVEL - 010h), col4, 015h, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	target, quad+32, 4
	chrdef	x, (GROUNDLEVEL - 016h), col1, 026h, 4
	chrdef	x, (GROUNDLEVEL - 016h), black, 00ch, 4
	db	target+1, quad+38, 2
	chrdef2	(GROUNDLEVEL - 016h), col2, 026h, 4
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 4
	db	target+2, quad+42, 2
	chrdef2	(GROUNDLEVEL - 016h), col3, 026h, 4
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 4
	db	target+3, quad+46, 2
	chrdef2	(GROUNDLEVEL - 016h), col4, 026h, 4
	chrdef2	(GROUNDLEVEL - 016h), black, 00ch, 4
	db	target, quad+48, 4
	chrdef	x, (GROUNDLEVEL - 01eh), col1, 022h, 3
	chrdef	x, (GROUNDLEVEL - 01eh), black, 00ch, 3
	db	target+1, quad+54, 2
	chrdef2	(GROUNDLEVEL - 01eh), col2, 022h, 3
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	db	target+2, quad+58, 2
	chrdef2	(GROUNDLEVEL - 01eh), col3, 022h, 3
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	db	target+3, quad+62, 2
	chrdef2	(GROUNDLEVEL - 01eh), col4, 022h, 3
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	endm

; 3 filled rockets
; uses 4 quads
; UNUSED, no hit table
rockets3 macro target, x, quad, col1, col2, col3
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 002h), col1, 029h, 2
	chrdef	x, (GROUNDLEVEL - 002h), black, 00ch, 2
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL - 002h), col2, 029h, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 2
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL - 002h), col3, 029h, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 2
	db	eram_permtarg, quad+14, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 2
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 010h), col1, 02fh, 0
	chrdef	x, (GROUNDLEVEL - 010h), black, 00ch, 0
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 010h), col2, 02fh, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 010h), col3, 02fh, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	eram_permtarg, quad+30, 2
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 0
	db	target, quad+32, 4
	chrdef	x, (GROUNDLEVEL - 01eh), col1, 02fh, 0
	chrdef	x, (GROUNDLEVEL - 01eh), black, 00ch, 0
	db	target+1, quad+38, 2
	chrdef2	(GROUNDLEVEL - 01eh), col2, 02fh, 0
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 0
	db	target+2, quad+42, 2
	chrdef2	(GROUNDLEVEL - 01eh), col3, 02fh, 0
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 0
	db	eram_permtarg, quad+46, 2
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 0
	db	target, quad+48, 4
	chrdef	x, (GROUNDLEVEL - 028h), col1, 037h, 0
	chrdef	x, (GROUNDLEVEL - 028h), black, 00ch, 0
	db	target+1, quad+54, 2
	chrdef2	(GROUNDLEVEL - 028h), col2, 037h, 0
	chrdef2	(GROUNDLEVEL - 028h), black, 00ch, 0
	db	target+2, quad+58, 2
	chrdef2	(GROUNDLEVEL - 028h), col3, 037h, 0
	chrdef2	(GROUNDLEVEL - 028h), black, 00ch, 0
	db	eram_permtarg, quad+62, 2
	chrdef2	(GROUNDLEVEL - 028h), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 028h), black, 00ch, 2
	endm

; a church with 2 trees
; uses 3 quads, 3 chars
; UNUSED, no hit table
church macro target, x, char, quad, col1, col2, col3
	; lower part of church + tree
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef	x, (GROUNDLEVEL - 006h), black, 00ch, 1
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	db	target+1, quad+10, 2
	chrdef2	(GROUNDLEVEL - 006h), col3, 014h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	db	target+2, quad+14, 2
	chrdef2	(GROUNDLEVEL - 006h), col3, 014h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1

	; fill hole in lower part
	db	target, char, 4
	chrdef	(x+8), (GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef	(x+8), (GROUNDLEVEL - 006h), black, 00ch, 1

	; top part of church + tree
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 014h), col1, 02fh, 0
	chrdef	x, (GROUNDLEVEL - 014h), black, 00ch, 0
	db	target, quad+22, 2
	chrdef2	(GROUNDLEVEL - 014h), col1, 039h, 0
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 0
	db	target+1, quad+26, 2
	chrdef2	(GROUNDLEVEL - 014h), col2, 031h, 0
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 0
	db	target+2, quad+30, 2
	chrdef2	(GROUNDLEVEL - 014h), col2, 031h, 0
	chrdef2	(GROUNDLEVEL - 014h), black, 00ch, 0

	; fill hole in top part of church
	db	target, char+4, 4
	chrdef	(x+8), (GROUNDLEVEL - 014h), col1, 02fh, 0
	chrdef	(x+8), (GROUNDLEVEL - 014h), black, 00ch, 0

	; tower
	db	target, char+8, 4
	chrdef	x, (GROUNDLEVEL - 022h), col1, 02fh, 0
	chrdef	x, (GROUNDLEVEL - 022h), black, 00ch, 0

	; top of tower, needs bottom cut, so waste quad
	db	target, quad+32, 4
	chrdef	x, (GROUNDLEVEL - 02ch), col1, 037h, 0
	chrdef	x, (GROUNDLEVEL - 02ch), black, 00ch, 0
	db	eram_permtarg, quad+38, 2
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 0
	db	eram_permtarg, quad+42, 2
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 0
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 0
	db	eram_permtarg, quad+46, 2
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 02ch), black, 00ch, 2
	endm

; a castle with 3 towers
; uses 2 quad, 5 char
castle macro target, x, char, quad, col1
	; top of towers
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL - 010h), col1, 011h, 3
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 010h), col1, 011h, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+10, 2
	chrdef2	(GROUNDLEVEL - 010h), col1, 011h, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+14, 2
	chrdef2	(GROUNDLEVEL - 010h), black, 00ch, 5
	chrdef2	0f8h, black, 0, 0
	; towers
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 00ch), col1, 027h, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+22, 2
	chrdef2	(GROUNDLEVEL - 00ch), col1, 027h, 5
	chrdef2	0f8h, black, 0, 0
	db	target, quad+26, 2
	chrdef2	(GROUNDLEVEL - 00ch), col1, 027h, 5
	chrdef2	0f8h, black, 0, 0
	db	eram_permtarg, quad+30, 2
	chrdef2	(GROUNDLEVEL - 00ch), black, 00ch, 5
	chrdef2	0f8h, black, 0, 0
	; base walls
	db	target, char, 20
	chrdef	(x+2), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	(x+9), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	(x+16), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	(x+23), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	(x+29), (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; 1 car
; uses 2 quad, 6 char
; UNUSED, no hit table
car macro target, x, char, quad, col1
	; wheels
	db	target, quad, 4
	chrdef	(x+8), (GROUNDLEVEL - 004h), white, 031h, 2
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 004h), white, 031h, 2
	chrdef2	0f8h, black, 0, 0
	db	target, quad+10, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	chrdef2	0f8h, black, 0, 0
	db	target, quad+14, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	chrdef2	0f8h, black, 0, 0
	; lower part
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 006h), col1, 02fh, 3
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+22, 2
	chrdef2	(GROUNDLEVEL - 006h), col1, 02fh, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+26, 2
	chrdef2	(GROUNDLEVEL - 006h), col1, 02fh, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+30, 2
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 3
	chrdef2	0f8h, black, 0, 0
	; top part
	db	target, char, 24
	chrdef	(x+4), (GROUNDLEVEL - 010h), col1, 038h, 2
	chrdef	(x+12), (GROUNDLEVEL - 010h), col1, 02fh, 2
	chrdef	(x+19), (GROUNDLEVEL - 010h), col1, 02fh, 2
	chrdef	(x+25), (GROUNDLEVEL - 010h), col1, 02fh, 2
	chrdef	(x+31), (GROUNDLEVEL - 010h), col1, 039h, 2
	chrdef	(x+34), (GROUNDLEVEL - 014h), col1, 02eh, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; helicopter
; 5 chars
; UNUSED, no hit table
heli macro target, x, char, col1
	db	target, char, 20
	chrdef	(x+1), (GROUNDLEVEL - 00eh), col1, 037h, 4
	chrdef	x, (GROUNDLEVEL - 008h), col1, 031h, 2
	chrdef	(x+6), (GROUNDLEVEL - 008h), col1, 00fh, 2
	chrdef	(x-2), (GROUNDLEVEL + 002h), col1, 01eh, 5
	chrdef	(x+4), (GROUNDLEVEL + 002h), col1, 00eh, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; tank
; 4 chars
; UNUSED, no hit table
tank	macro target, x, char, col1
	db	target, char, 16
	chrdef	x, (GROUNDLEVEL + 002h), col1, 03fh, 5
	chrdef	x, (GROUNDLEVEL - 002h), col1, 02fh, 5
	chrdef	x, (GROUNDLEVEL - 006h), col1, 027h, 5
	chrdef	(x+4), (GROUNDLEVEL - 00ah), col1, 02eh, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; group of tanks
; 4 quads
; UNUSED, no hit table
tankgroup macro target, x, quad, col1, col2, col3, col4
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL + 002h), col1, 03fh, 5
	chrdef	x, (GROUNDLEVEL + 002h), black, 00ch, 5
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL + 002h), col2, 03fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL + 002h), col3, 03fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	target+3, quad+14, 2
	chrdef2	(GROUNDLEVEL + 002h), col4, 03fh, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 002h), col1, 02fh, 5
	chrdef	x, (GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 002h), col2, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 002h), col3, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+3, quad+30, 2
	chrdef2	(GROUNDLEVEL - 002h), col4, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	target, quad+32, 4
	chrdef	x, (GROUNDLEVEL - 006h), col1, 027h, 5
	chrdef	x, (GROUNDLEVEL - 006h), black, 00ch, 5
	db	target+1, quad+38, 2
	chrdef2	(GROUNDLEVEL - 006h), col2, 027h, 5
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 5
	db	target+2, quad+42, 2
	chrdef2	(GROUNDLEVEL - 006h), col3, 027h, 5
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 5
	db	target+3, quad+46, 2
	chrdef2	(GROUNDLEVEL - 006h), col4, 027h, 5
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 5
	db	target, quad+48, 4
	chrdef	(x+4), (GROUNDLEVEL - 00ah), col1, 02eh, 5
	chrdef	(x+4), (GROUNDLEVEL - 00ah), black, 00ch, 5
	db	target+1, quad+54, 2
	chrdef2	(GROUNDLEVEL - 00ah), col2, 02eh, 5
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 5
	db	target+2, quad+58, 2
	chrdef2	(GROUNDLEVEL - 00ah), col3, 02eh, 5
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 5
	db	target+3, quad+62, 2
	chrdef2	(GROUNDLEVEL - 00ah), col4, 02eh, 5
	chrdef2	(GROUNDLEVEL - 00ah), black, 00ch, 5
	endm

; 3 vans
; uses 2 quads, 3 char, chars separate for _extra
; quad part
vans1 macro target, x, quad, col0, col1, col2, col3
	; wheels: Y cut at bottom
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef	x, (GROUNDLEVEL + 002h), black, 00ch, 0
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 0
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 0
	db	eram_permtarg, quad+14, 2
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	; middle part
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 002h), col1, 02fh, 5
	chrdef	x, (GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 002h), col2, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 002h), col3, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	eram_permtarg, quad+30, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	endm

; 3 vans
; uses 2 quads, 3 char, chars separate for _extra
; char part
vans2 macro target, x, char, col1, col2, col3
	db	target, char, 4
	chrdef	(x+1), (GROUNDLEVEL - 006h), col1, 032h, 5
	chrdef	(x+1), (GROUNDLEVEL - 006h), black, 00ch, 5
	db	target+1, char+4, 4
	chrdef	(x+17), (GROUNDLEVEL - 006h), col2, 032h, 5
	chrdef	(x+17), (GROUNDLEVEL - 006h), black, 00ch, 5
	db	target+2, char+8, 4
	chrdef	(x+33), (GROUNDLEVEL - 006h), col3, 032h, 5
	chrdef	(x+33), (GROUNDLEVEL - 006h), black, 00ch, 5
	endm

; a railroad train, based on an idea by Rafael Cardoso
; uses grid, 3 quads and 6 chars, see traine for 2 chars in extra part
; there is no x parameter, the grid is fixed
train macro target, char, quad, col1, col2
	; bodys
	db	target, vdc_gridv0, 2
	db	020h, 020h
	db	0, 0
	db	target+1, vdc_gridv3, 2
	db	020h, 020h
	db	0, 0
	db	target+2, vdc_gridv6, 2
	db	020h, 020h
	db	0, 0
	; wheels
	db	target, quad, 4
	chrdef	00ch, (GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef	00ch, (GROUNDLEVEL - 004h), black, 00ch, 2
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	db	eram_permtarg, quad+10, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	db	target+1, quad+14, 2
	chrdef2	(GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	db	target+1, quad+16, 4
	chrdef	04ch, (GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef	04ch, (GROUNDLEVEL - 004h), black, 00ch, 2
	db	eram_permtarg, quad+22, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	db	target+2, quad+30, 2
	chrdef2	(GROUNDLEVEL - 004h), col1, 031h, 2
	chrdef2	(GROUNDLEVEL - 004h), black, 00ch, 2
	; windows last car
	db	target, char, 12
	chrdef	00ah, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	014h, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	01eh, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	; windows middle car
	db	target+1, char+12, 12
	chrdef	03ah, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	044h, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	04eh, (GROUNDLEVEL - 014h), col2, 02fh, 2
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	; top of engine
	db	target+2, quad+32, 4
	chrdef	070h, (GROUNDLEVEL - 01eh), col1, 01dh, 3
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target+2, quad+38, 2
	chrdef2	(GROUNDLEVEL - 01eh), col1, 02ch, 3
	chrdef2	0f8h, black, 0, 0
	db	target+2, quad+42, 2
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	chrdef2	0f8h, black, 0, 0
	db	target+2, quad+46, 2
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	chrdef2	0f8h, black, 0, 0
	endm

; a railroad train, based on an idea by Rafael Cardoso
; uses 2 chars in extra part, see train for rest
; there is no x parameter, the grid is fixed
traine macro target, char, col1
	; front and rest of top
	db	target+2, char, 8
	chrdef	088h, (GROUNDLEVEL - 00ah), col1, 039h, 0
	chrdef	06ah, (GROUNDLEVEL - 01eh), col1, 01dh, 3
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; A space port
; uses grid and 3 quads
; there is no x parameter, the grid is fixed
spaceport macro target, quad, col1, col2
	; use grid for building
	db	target, vdc_gridv1, 3
	db	020h, 020h, 020h
	db	0, 0, 0

	; space between grid and ground + door
	db	target, quad, 4
	chrdef	018h, (GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 008h), col1, 02fh, 0
	chrdef2	0f8h, black, 0, 0
	db	target, quad+10, 2
	chrdef2	(GROUNDLEVEL - 008h), col2, 02fh, 0
	chrdef2	0f8h, black, 0, 0
	db	target, quad+14, 2
	chrdef2	(GROUNDLEVEL - 008h), black, 00ch, 0
	chrdef2	0f8h, black, 0, 0
	db	target, quad+16, 4
	chrdef	020h, (GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+22, 2
	chrdef2	(GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef2	0f8h, black, 0, 0
	db	target, quad+26, 2
	chrdef2	(GROUNDLEVEL - 006h), col1, 02fh, 1
	chrdef2	0f8h, black, 0, 0
	db	target, quad+30, 2
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	chrdef2	0f8h, black, 0, 0

	; windows
	db	target, quad+32, 4
	chrdef	01ch, (GROUNDLEVEL - 012h), col2, 031h, 3
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+38, 2
	chrdef2	(GROUNDLEVEL - 012h), col2, 031h, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+42, 2
	chrdef2	(GROUNDLEVEL - 012h), col2, 031h, 3
	chrdef2	0f8h, black, 0, 0
	db	target, quad+46, 2
	chrdef2	(GROUNDLEVEL - 012h), black, 00ch, 4
	chrdef2	0f8h, black, 0, 0
	endm

; a spaceship
; uses 5 chars and 1 quad, see spaceshipe for extra
spaceship macro target, x, char, quad, col1, col2
	; the ship
	db	target, char, 20
	chrdef	(x+2), (GROUNDLEVEL - 016h), col1, 038h, 0
	chrdef	(x+10), (GROUNDLEVEL - 016h), col1, 02fh, 0
	chrdef	(x+18), (GROUNDLEVEL - 016h), col1, 02fh, 0
	chrdef	(x+26), (GROUNDLEVEL - 016h), col1, 02fh, 0
	chrdef	(x+34), (GROUNDLEVEL - 016h), col1, 039h, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0

	; top of ship
	db	target, quad, 4
	chrdef	(x+10), (GROUNDLEVEL - 01eh), col2, 031h, 2
	chrdef	0f8h, 0f8h, black, 0, 0
	db	target, quad+6, 2
	chrdef2	(GROUNDLEVEL - 01eh), col2, 031h, 2
	chrdef2	0f8h, black, 0, 0
	db	target, quad+10, 2
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 0
	chrdef2	0f8h, black, 0, 0
	db	target, quad+14, 2
	chrdef2	(GROUNDLEVEL - 01eh), black, 00ch, 3
	chrdef2	0f8h, black, 0, 0
	endm

; a spaceship, extra part
; uses 2 chars, see spaceship for normal
spaceshipe macro target, x, char, col1
	; landing gear
	db	target, char, 8
	chrdef	(x), (GROUNDLEVEL - 008h), col1, 02eh, 0
	chrdef	(x+36), (GROUNDLEVEL - 008h), col1, 03bh, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; a street lantern
; uses 4 chars
lantern macro target, x, char, col1, col2
	db	target, char, 16
	chrdef	(x), (GROUNDLEVEL - 006h), col1, 014h, 1
	chrdef	(x), (GROUNDLEVEL - 00ch), col1, 037h, 4
	chrdef	(x-6), (GROUNDLEVEL - 00ch), col2, 044h, 5
	chrdef	(x+8), (GROUNDLEVEL - 00ch), col2, 00fh, 5
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	chrdef	0f8h, 0f8h, black, 0, 0
	endm

; 3 normal cars
; uses 3 quads
cars macro target, x, quad, col0, col1, col2, col3
	db	target, quad, 4
	chrdef	x, (GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef	x, (GROUNDLEVEL + 002h), black, 00ch, 0
	db	target+1, quad+6, 2
	chrdef2	(GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 0
	db	target+2, quad+10, 2
	chrdef2	(GROUNDLEVEL + 002h), col0, 02ch, 0
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 0
	db	eram_permtarg, quad+14, 2
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	chrdef2	(GROUNDLEVEL + 002h), black, 00ch, 5
	; middle part
	db	target, quad+16, 4
	chrdef	x, (GROUNDLEVEL - 002h), col1, 02fh, 5
	chrdef	x, (GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+1, quad+22, 2
	chrdef2	(GROUNDLEVEL - 002h), col2, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	target+2, quad+26, 2
	chrdef2	(GROUNDLEVEL - 002h), col3, 02fh, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	db	eram_permtarg, quad+30, 2
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5
	chrdef2	(GROUNDLEVEL - 002h), black, 00ch, 5

	db	target, quad+32, 4
	chrdef	(x+1), (GROUNDLEVEL - 006h), col1, 037h, 1
	chrdef	(x+1), (GROUNDLEVEL - 006h), black, 00ch, 1
	db	target+1, quad+38, 2
	chrdef2	(GROUNDLEVEL - 006h), col2, 037h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	db	target+2, quad+42, 2
	chrdef2	(GROUNDLEVEL - 006h), col3, 037h, 1
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 1
	db	target, quad+46, 2
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 5
	chrdef2	(GROUNDLEVEL - 006h), black, 00ch, 5
	endm

; ROM table for target hit routine
; 1 byte target variable or 0 as end marker, eram_permtarg as dummy entry
; 1 byte y hit range, 2 pixel above overlap, see checktargets for explanation
; 2 byte x hit range in double add form

; Y absolute: GROUNDLEVEL - 01ch
; X absolute: x-6/x+6
treehit	macro target, x
	db	target
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+6), 13
	endm

; Y absolute: GROUNDLEVEL - 022h
; X absolute: x-7,x+15
househit macro target, x
	db	target
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - (x+15), 23
	endm

; first tree like single tree, rest 16 pixel apart
foresthit macro target, x
	db	target
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+6), 13

	db	target+1
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+22), 13

	db	target+2
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+38), 13

	db	target+3
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+54), 13

	; dummy entries for shot trees
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+6), 13

	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+22), 13

	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+38), 13

	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+54), 13
	endm

; first like single house, rest 24 pixel apart
hgrouphit macro target, x
	db	target
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - (x+15), 23

	db	target+1
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - (x+39), 23

	db	target+2
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - (x+63), 23

	; dummy entry, has to cover empty spaces between houses
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - (x+63), 70
	endm

pyramidhit	macro target, x
; big pyramid
; Y absolute: GROUNDLEVEL - 026h
; X absolute: x-7/x+01eh
	db	target
	db	0104h - (GROUNDLEVEL - 026h)
	db	0ffh - (x+01eh), 026h
; small pyramid
; Y absolute: GROUNDLEVEL - 018h
; X absolute: x+21h/x+036h
	db	target+1
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x+036h), 016h
; tiny pyramids
; Y absolute: GROUNDLEVEL - 018h, empty quad on top!
; X absolute: x+03ah/x+046h
	db	target+2
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x+046h), 00dh
; Y absolute: GROUNDLEVEL - 010h
; X absolute: x+04bh/x+055h
	db	target+3
	db	0104h - (GROUNDLEVEL - 010h)
	db	0ffh - (x+055h), 00bh
; Y absolute: GROUNDLEVEL - 010h
; X absolute: x+05bh/x+065h
	db	target+4
	db	0104h - (GROUNDLEVEL - 010h)
	db	0ffh - (x+065h), 00bh
	; dummy entries
; Y absolute: GROUNDLEVEL - 026h
; X absolute: x-7/x+016h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 026h)
	db	0ffh - (x+016h), 01eh
; Y absolute: GROUNDLEVEL - 018h
; X absolute: x+017h/x+03dh
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x+03dh), 027h
; Y absolute: GROUNDLEVEL - 010h
; X absolute: x+03eh/x+077h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 010h)
	db	0ffh - (x+077h), 03ah
	endm

islandhit macro target, x
; Y absolute: GROUNDLEVEL - 020h
; X absolute: x+2/x+00fh
	db	target
	db	0104h - (GROUNDLEVEL - 020h)
	db	0ffh - (x+00fh), 00eh
; X absolute: x+012h/x+01fh
	db	target+1
	db	0104h - (GROUNDLEVEL - 020h)
	db	0ffh - (x+01fh), 00eh
; X absolute: x+022h/x+02fh
	db	target+2
	db	0104h - (GROUNDLEVEL - 020h)
	db	0ffh - (x+02fh), 00eh
; X absolute: x+032h/x+03eh, it is a tree not a small house
	db	target+3
	db	0104h - (GROUNDLEVEL - 020h)
	db	0ffh - (x+03eh), 00dh
	; dummy entry for whole island
; X absolute: x-5/x+046h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 020h)
	db	0ffh - (x+046h), 04ch
	endm

minisubhit macro target, x
; Y absolute: GROUNDLEVEL - 010h
; X absolute: x-006h/x+00eh
	db	target
	db	0104h - (GROUNDLEVEL - 010h)
	db	0ffh - (x+00eh), 015h
	endm

castlehit macro target, x
; Y absolute: GROUNDLEVEL - 01ch
; X absolute: X-7/x+025h
	db	target
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+025h), 02dh
	; dummy entry, quads at right side
; Y absolute: GROUNDLEVEL - 01ch
; X absolute: X-7/x+036h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01ch)
	db	0ffh - (x+036h), 03eh
	endm

vanhit macro target, x
; Y absolute: GROUNDLEVEL - 012h
; X absolute: X-6/X+6 X+0ah/X+016h, X+01ah/X+026h
	db	target
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+006h), 00dh
	db	target+1
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+016h), 00dh
	db	target+2
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+026h), 00dh
	; dummy entry for invisible quad part/ shot parts
; X absolute: X-6/X+036h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+036h), 03dh
	endm

trainhit macro target
; Y absolute: GROUNDLEVEL - 022h/02ah
; X absolute: 002h/026h, 032h/056h, 062h/08eh
; there is no x parameter, target uses grid
	db	target
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - 026h, 025h
	db	target+1
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - 056h, 025h
	db	target+2
	db	0104h - (GROUNDLEVEL - 02ah)
	db	0ffh - 08eh, 02dh
	; dummy entry, wheels are shared
; Y absolute: GROUNDLEVEL - 010h
; X absolute: 006h/083h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 010h)
	db	0ffh - 083h, 07eh
	; dummy entry, quad of engine to right side
; Y absolute: GROUNDLEVEL - 02ah
; X absolute: 08eh/0a8h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 02ah)
	db	0ffh - 0a8h, 01bh
	endm

spaceporthit macro target
; Y absolute: GROUNDLEVEL - 022h
; X absolute: 013h/046h
	db	target
	db	0104h - (GROUNDLEVEL - 022h)
	db	0ffh - 046h, 034h
	; dummy entry, window and ground quads to the left
; Y absolute: GROUNDLEVEL - 01eh
; X absolute: 047h/051h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 01eh)
	db	0ffh - 051h, 00bh
	endm

spaceshiphit macro target, x
; Y absolute: GROUNDLEVEL - 02ah
; X absolute: X-6/X+02bh
	db	target
	db	0104h - (GROUNDLEVEL - 02ah)
	db	0ffh - (x+02bh), 032h
	; dummy entries, quad of ship top to the left
; Y absolute: GROUNDLEVEL - 02ah
; X absolute: X+02ch/X+02fh
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 02ah)
	db	0ffh - (x+02fh), 004h
; Y absolute: GROUNDLEVEL - 02ah
; X absolute: X+035h/X+03fh
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 02ah)
	db	0ffh - (x+03fh), 00bh
	endm

lantern_hit macro target, x
; Y absolute: GROUNDLEVEL - 018h
; X absolute: X-8/X+008h
	db	target
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x+008h), 011h
	; dummy entry left side
; Y absolute: GROUNDLEVEL - 018h
; X absolute: X-00ch/X-9
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x-009h), 004h
	; dummy entry right side
; Y absolute: GROUNDLEVEL - 018h
; X absolute: X+9/X+00dh
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 018h)
	db	0ffh - (x+00dh), 005h
	endm

cars_hit macro target, x
; Y absolute: GROUNDLEVEL - 012h
; X absolute: X-6/X+007h
	db	target
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+007h), 00eh
; Y absolute: GROUNDLEVEL - 012h
; X absolute: X+00ah/X+017h
	db	target+1
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+017h), 00eh
; Y absolute: GROUNDLEVEL - 012h
; X absolute: X+01ah/X+027h
	db	target+2
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+027h), 00eh
	; dummy entry for invisible part/shot parts
; Y absolute: GROUNDLEVEL - 012h
; X absolute: X-6h/X+037h
	db	eram_permtarg
	db	0104h - (GROUNDLEVEL - 012h)
	db	0ffh - (x+037h), 03eh
	endm
