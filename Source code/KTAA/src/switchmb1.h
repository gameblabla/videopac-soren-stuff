; Kill the attacking aliens for the G7000 by Soeren Gust
;
; $Id: switchmb1.h,v 1.19 2003/08/15 14:51:13 sgust Exp $

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

; bank switching table for MB1

	switchtable drawtargets,0
	switchtable checkbonus,3
	switchtable levelplus,1
	switchtable bonusscreen,2
	switchtable powerupstart,2
	switchtable powerupcollect,2
	switchtable poweruphit,2
	switchtable endofexplosion,2
	switchtable slowdownexpire,2
	switchtable addscoreb2,3
	switchtable mountainplus,2

; return to bank 1
switchmb1_1
	; back to bank 1
	orl	P1,#1			; set bit 0
	anl	P1,#0fdh		; clear bit 1
	ret				; executed in bank 1

; return to bank 2
switchmb1_2
	; back to bank 2
	orl	P1,#2			; set bit 1
	anl	P1,#0feh		; clear bit 0
	ret				; executed in bank 2

; return to bank 3
switchmb1_3
	; back to bank 3
	orl	P1,#3			; back to bank 3
	ret
