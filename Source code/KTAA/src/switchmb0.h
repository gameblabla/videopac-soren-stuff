; Kill the attacking aliens for the G7000 by Soeren Gust
;
; $Id: switchmb0.h,v 1.13 2003/09/25 21:21:26 sgust Exp $

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

; bank switching table for MB0

	switchtable titlescreen,1
	switchtable levelscreen,1
	switchtable gameoverb3,1
	switchtable respawn,2
	switchtable showscoreb1,0
	switchtable showscoreb2,0
	switchtable getrandbyteb1,2
	switchtable getrandbyteb3,2
	switchtable waitfireb1,2

; return to bank 1
switchmb0_1
	; back to bank 1
	orl	P1,#1			; set bit 0
	anl	P1,#0fdh		; clear bit 1
	ret				; executed in bank 1

; return to bank 2
switchmb0_2
	; back to bank 2
	orl	P1,#2			; set bit 1
	anl	P1,#0feh		; clear bit 0
	ret				; executed in bank 2

; return to bank 3
switchmb0_3
	; back to bank 3
	orl	P1,#3			; back to bank 3
	ret				; executed in bank 3
