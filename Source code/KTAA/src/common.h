; Common vars, macros etc for Kill the attacking aliens for the G7000
;
; $Id: common.h,v 1.118 2003/09/29 20:44:51 sgust Exp $

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

; You can always get the latest version at <http://soeren.informationstheater.de>

; This is written for asl, see <http://www.alfsembler.de>. I use several
; special features (macros, section) of asl, so using other assemblers
; requires a lot of porting.

; variables in internal ram
iram_ictrl	equ	020h	; control irq
; next 3 accessed with inc/dec r0
iram_ship_shape	equ	021h	; shape of ship (0 = right, 1 = right+up, ...)
iram_ship_x	equ	022h	; x position of ship
iram_ship_y	equ	023h	; y position of ship
; shipshot accessed with inc/dec r0
iram_shipshot_y	equ	024h	; y position of ship shot
iram_shipshot_x	equ	025h	; x position of ship shot
iram_shipshot_v	equ	026h	; direction of ship shot (x/y in high/low nibble)
iram_palflag	equ	027h	; 0 NTSC, 0xff PAL
iram_level	equ	028h	; current level
iram_shield	equ	029h	; strength of the shield
iram_gamestate	equ	02ah	; play/dead/end
iram_firelimit	equ	02bh	; fire rate limiter/debounce
iram_color1	equ	02ch	; color of sky
iram_color2	equ	02dh	; color of ground

; all alien data is accessed with inc/dec r0
iram_alien0_t	equ	02eh	; 7-2: type of alien, 1-0: framenum
iram_alien0_y	equ	02fh	; x position of alien
iram_alien0_x	equ	030h	; y position of alien
iram_alien1_t	equ	031h	; 7-2: type of alien, 1-0: framenum
iram_alien1_y	equ	032h	; x position of alien
iram_alien1_x	equ	033h	; y position of alien
iram_alien2_t	equ	034h	; 7-2: type of alien, 1-0: framenum
iram_alien2_y	equ	035h	; x position of alien
iram_alien2_x	equ	036h	; y position of alien
iram_ashot0_x	equ	037h	; x position of alien shot
iram_ashot0_y	equ	038h	; y position of alien shot
iram_ashot1_x	equ	039h	; x position of alien shot
iram_ashot1_y	equ	03ah	; y position of alien shot
iram_ashot2_x	equ	03bh	; x position of alien shot
iram_ashot2_y	equ	03ch	; y position of alien shot

; the bits in iram_ictrl
ictrl_draw	equ	080h	; if set draw the playfield
ictrl_second	equ	040h	; (jb6) if set start second raster in raster irq
ictrl_dirty	equ	020h	; (jb5) if set draw quad targets
ictrl_flash	equ	010h	; (jb4) if set flash screen, low bits as counter
ictrl_bottom	equ	008h	; raster has reached bottom if set
ictrl_flcount	equ	007h	; bitmask for flash counter

; alternative use outside gameloop
iram_datacall	equ	iram_ship_shape	; which call to use to get data
; next 3 accessed with dec/inc
iram_xpos	equ	iram_ship_x	; x position of char object
iram_width	equ	iram_ship_y	; width of char object in chars
iram_attr	equ	iram_shipshot_y	; attribute byte
iram_bonuswait	equ	iram_firelimit	; initial wait on bonusscreen
iram_colcycle	equ	iram_shipshot_x	; used for color cycling on perfect bonus
iram_temp	equ	iram_gamestate	; used for temp storage

;eram usage:
; next 4 use dec/inc for access
eram_r6		equ	000h	; store R6 while in irq
eram_r5		equ	001h	; store R5 while in irq
eram_r4		equ	002h	; store R4 while in irq
eram_r3		equ	003h	; store R3 while in irq
; next 3 use inc r0 for access
eram_scoreh	equ	004h	; score high byte
eram_scorem	equ	005h	; score middle byte
eram_scorel	equ	006h	; score low byte
; next 3 use inc r0 for access
eram_bonush	equ	007h	; bonus high byte
eram_bonusm	equ	008h	; bonus middle byte
eram_bonusl	equ	009h	; bonus low byte
; next 2 use inc r0 for access
eram_randomh	equ	00ah	; random value seed
eram_randoml	equ	00bh	; random value seed
eram_timel	equ	00ch	; frame counter low
; next 3 use inc r0 for access
eram_joystate	equ	00dh	; for joystick fire FSM
eram_joywait	equ	00eh	; for joystick fire FSM
eram_frame	equ	00fh	; for joystick fire FSM/frame drop counter for ntsc
eram_charquadx	equ	010h	; x pos of active targets, 8 char + 16 quad
; next 3 use inc r0 for access
eram_powerup	equ	028h	; which ashot is used as power-up
eram_powertime	equ	029h	; how long will power-up stay
eram_powertype	equ	02ah	; type of power-up
eram_plusmode	equ	02bh	; 0 running on 7000, 0ffh running on 7400
eram_shotmulti	equ	02ch	; shot speed multiplicator, 0 minimal speed, 1 double speed, max value 3
eram_completion	equ	02dh	; how often the last level was completed

; all alien data is accessed with inc/dec r0 and is identical to iram_alien0_t
eram_alien0_v	equ	02eh	; speed alien 0 / respawn counter when type == 0
eram_alien0_a	equ	02fh	; data1 alien 0 / type to respawn
eram_alien0_b	equ	030h	; data2 alien 0
eram_alien1_v	equ	031h	; speed alien 1 / respawn counter when type == 0
eram_alien1_a	equ	032h	; data1 alien 1 / type to respawn
eram_alien1_b	equ	033h	; data2 alien 1
eram_alien2_v	equ	034h	; speed alien 2 / respawn counter when type == 0
eram_alien2_a	equ	035h	; data1 alien 2 / type to respawn
eram_alien2_b	equ	036h	; data2 alien 2
; alien shots are identical to iram_ashot?_x
eram_ashot0_v	equ	037h	; speed alien shot 0
eram_ashot1_v	equ	039h	; speed alien shot 1
eram_ashot2_v	equ	03bh	; speed alien shot 2
eram_shottime	equ	03ch	; time counter for faster shots
eram_slowdown	equ	03dh	; time counter for slower aliens
eram_probspawn	equ	03eh	; spawn counter to block probspawn

; 50h-57h alien alive counters, more available if needed
eram_alienvar	equ	050h

; next 3 use inc r0 for access
eram_hisch	equ	060h	; hi-score high byte
eram_hiscm	equ	061h	; hi-score middle byte
eram_hiscl	equ	062h	; hi-score low byte

eram_permtarg	equ	073h	; for permanent displayed targets, no bonus
; 74h-7fh target state variables (12 for historical reasons)
eram_targets	equ	074h

; values for iram_gamestate
STATE_PLAY	equ	0	; normal game play
STATE_DEAD	equ	1	; ship dying
STATE_EXP	equ	2	; ship exploding
STATE_END	equ	3	; end of game display

; values for eram_joystate
JOYSTATE_START	equ	0	; waiting for fire released
JOYSTATE_WAIT1	equ	1	; fire released, wait for debounce
JOYSTATE_WAIT2	equ	2	; waiting for FIRE
JOYSTATE_FIRE1	equ	3	; fire pressed, wait some frames to debounce
JOYSTATE_FIRE2	equ	4	; waiting for fire release
JOYSTATE_UP	equ	5	; fire release, wait some frames to debounce
JOYSTATE_END	equ	6	; finished

; adjustable constants
LEFTX		equ	008h	; x position of left border
RIGHTX		equ	092h	; x position of right border
TOPY		equ	020h	; y position top of screen
GROUNDLEVEL	equ	0a6h	; y position of ground
BOTALIENY	equ	GROUNDLEVEL - 049h ; y position of bottom for aliens
SCOREX		equ	070h	; x position of score display
SCOREY		equ	0c2h	; y position of score display
SHIELD		equ	6	; initial shield strength
PROB_POW_SHIELD	equ	02ah	; probability for a shield power-up
PROB_POW_SHOT	equ	03eh	; probability for fast shot power-up
PROB_POW_SLOW	equ	03eh	; probability for alien slowdown power-up
PROB_POW_TEN	equ	05ah	; probability for ten points power-up
PROBSPAWN_BLOCK	equ	3	; number of aliens between probspawned aliens
DIFF_COMPLETE	equ	004h	; difficulty increase after level 7 finished

	if ((PROB_POW_SHIELD + PROB_POW_TEN + PROB_POW_SHOT + PROB_POW_SLOW) <> 256)
	error	"Power-up probability mismatch"
	endif

; the aliens
ALN_UFO		equ	1	; flies left<->right on same height
				; x random, y depends on alien0-2
ALN_DISC	equ	2	; disc shaped alien, zigzag flight

ALN_BOMBER	equ	3	; T shaped ship, fast bomber

ALN_RANDOM	equ	4	; changes direction at random

ALN_ATTACK	equ	5	; attacks targets

ALN_BOOMERANG	equ	6	; follows ship

; bonus offsets in bonustable
BONUS_TREE	equ	1
BONUS_HOUSE	equ	2
BONUS_BIGPY	equ	3
BONUS_MIDPY	equ	4
BONUS_SMLPY	equ	5
BONUS_TINPY	equ	6
BONUS_MINSUB	equ	7
BONUS_CASTLE	equ	8
BONUS_VAN	equ	9
BONUS_TRAINCAR	equ	10
BONUS_TRAINENG	equ	11
BONUS_SPACEPORT	equ	12
BONUS_SPACESHIP	equ	13
BONUS_LANTERN	equ	14
BONUS_CAR	equ	15

; This macro removes the SEL MB0/1 automatic from the call command
call macro addr
	if ($ < 0800h)
	!call addr & 07ffh
	else
	!call addr | 0800h
	endif
	endm

; This macro removes the SEL MB0/1 automatic from the jmp command
jmp macro addr
	if ($ < 0800h)
	!jmp addr & 07ffh
	else
	!jmp addr | 0800h
	endif
	endm

; macro to generate code for calling routines in other banks
; the routine is responsible for the correct return to the calling bank
; This should support all possible combinations, but in use are only:
; 3 to 0 1 2, 2 to 0 1 3, 1 to 0 2
switchtable macro name,bnk
name_bank label $
	; switch to target bank
	if (bnk == 0)
	anl	P1,#0fch	; clear bits 0 1
	elseif (bnk == 1)
	anl	P1,#0fdh	; clear bit 1
	orl	P1,#1		; set bit 0
	elseif (bnk == 2)
	anl	P1,#0feh	; clear bit 0
	orl	P1,#2		; set bit 1
	elseif (bnk == 3)
	orl	P1,#3		; set bits 0 1
	else
	error "unknown bank: bnk"
	endif
	; the symbol is only defined in target bank
	if (bnk == BANK)
	jmp	name
	else
	nop
	nop
	endif
	endm

; call a routine in other bank
bcall	macro addr
	call addr_bank
	endm

; jump to a routine in other bank
bjmp	macro addr
	jmp addr_bank
	endm

; This macro is a replacement for call printchar with reduced stack usage
; It does only work on chars and does not advance the x position.
mprintchar macro
	mov	a,r4		; y position
	movx	@r0,a
	inc	r0
	mov	a,r3		; x position
	movx	@r0,a
	inc	r0
	call	calcchar23	; calculate bytes 2 and 3
	mov	a,r5
	movx	@r0,a		; set byte 2
	inc	r0
	mov	a,r6
	movx	@r0,a		; set byte 3
	inc	r0		; needed when setting alien shots
	endm

; macro to simplify char definition
chrdef	macro x,y,color,char,off
	db	y, x
	db	lo(char*8-y/2+off), col_chr_color|hi(char*8-y/2+off)
	endm

; another macro to simplify char definition as part of quad
chrdef2	macro y,color,char,off
	db	lo(char*8-y/2+off), col_chr_color|hi(char*8-y/2+off)
	endm

; macro to simplify quad definition
quaddef	macro x,y,color,text
	if (strlen(text) <> 4)
	error 	"quaddef: text must be 4 chars long"
	endif
	db	y, x
	irpc	char,text
	db	lo('char'*8-y/2), col_chr_color|hi('char'*8-y/2)
	endm
	endm

; macro to simplify quad definition, every part can have different colors
quaddefcolor macro x,y,col1,col2,col3,col4,text
	db	y, x
	db	lo(hi(hiword(text))*8-y/2), col_chr_col1|hi(hi(hiword(text))*8-y/2)
	db	lo(lo(hiword(text))*8-y/2), col_chr_col2|hi(lo(hiword(text))*8-y/2)
	db	lo(hi(loword(text))*8-y/2), col_chr_col3|hi(hi(loword(text))*8-y/2)
	db	lo(lo(loword(text))*8-y/2), col_chr_col4|hi(lo(loword(text))*8-y/2)
	endm

; for multicolor VP+ gfx
blockchar macro col1, col2, char
	db	col_patr_stable | col_patr_blck | col_pbck_col1 | col_plus_col2
	db	char
	endm

; map numerical level names
maplevel macro lvl, name1, name2
	if (BANK == 0)
target_lvl	equ target_name1	; normal target table
targetextra_lvl	equ targetextra_name1	; extra target table
copyetarget_lvl	equ copyetarget_name1	; access routine
copyitarget_lvl	equ copyitarget_name1	; access routine
gettarget_lvl	equ gettarget_name1	; access routine
	endif

	if (BANK == 1)
leveldraw_lvl	equ leveldraw_name1	; VP+ gfx drawing routine
colplus_lvl	equ colplus_name1	; sky color for VP+
colhigh_lvl	equ colhigh_name1	; color highlight mask for VP+
	endif

	if (BANK == 2)
spawn_lvl	equ spawn_name2		; alien respawn decision routine
	endif

	if (BANK == 3)
maxshipy_lvl	equ maxshipy_name1		; y target hit range
targethit_lvl	equ targethit_name1	; hit table
colsky_lvl	equ colsky_name1	; sky color for normal G7000
colgnd_lvl	equ colgnd_name1	; ground color
alieninit_lvl	macro			; initial alien combination
	alieninit_name2
	endm
bonustable_lvl	macro			; bonus table
	bonustable_name1
	endm
	endif
	endm

; generates an assemble time error message when expr is not true
assert macro expr
	if (~~val(expr))
	error expr
	endif
	endm

; debugging macro: display offsets for target hits on ashot 0
debug_displayhittarget macro
	mov	a,r0			; which shot?
	xrl	a,#iram_ashot0_y	; compare with shot 0
	jz	.ok			; continue if shot 0
	ret				; leave if shot 1/2
.ok	mov	a,r3			; x offset
	mov	r0,#eram_scoreh
	movx	@r0,a			; into score display
	mov	a,r4			; y offset
	mov	r0,#eram_scorem
	movx	@r0,a			; into scoredisplay
	mov	r0,#iram_ashot0_y	; restore register
	endm

; sky colors (only for G7000) and ground colors
colsky_forest	equ	col_bck_blue
colgnd_forest	equ	080h | col_bck_green | col_grd_white | col_grd_lum
colsky_street	equ	080h | col_bck_violet | col_grd_white
colgnd_street	equ	080h | col_bck_green | col_grd_white | col_grd_lum
colsky_pyramid	equ	080h | col_bck_blue
colgnd_pyramid	equ	080h | col_bck_yellow | col_grd_white | col_grd_lum
colsky_water	equ	col_bck_blue
colgnd_water	equ	080h | col_bck_blue | col_grd_white | col_grd_lum
colsky_ice	equ	080h | col_bck_cyan	; dark due to ship hit marker
colgnd_ice	equ	080h | col_bck_white | col_grd_white | col_grd_lum
colsky_train	equ	080h | col_bck_violet | col_grd_yellow
colgnd_train	equ	080h | col_bck_green | col_grd_white | col_grd_lum
colsky_moon	equ	080h | col_bck_black | col_grd_cyan | col_grd_lum
colgnd_moon	equ	080h | col_bck_cyan | col_grd_white | col_grd_lum

; sky colors for VP+ gfx
colplus_forest	equ	col_pbck_blue | col_plus_blue
colplus_street	equ	col_pbck_violet | col_plus_violet
colplus_pyramid	equ	col_pbck_blue | col_plus_blue
colplus_water	equ	col_pbck_blue | col_plus_blue
colplus_ice	equ	col_pbck_cyan | col_plus_cyan
colplus_train	equ	col_pbck_violet | col_plus_violet
colplus_moon	equ	col_pbck_black | col_plus_black

; table of highlighted colors on VP+
colhigh_forest	equ	0e7h	; blue yellow
colhigh_street	equ	0ffh	; none
colhigh_pyramid	equ	0f7h	; yellow
colhigh_water	equ	0efh	; blue
colhigh_ice	equ	0ffh	; none
colhigh_train	equ	0ffh	; none
colhigh_moon	equ	0ffh	; none

; cpl of max ship y position
maxshipy_forest		equ	GROUNDLEVEL - 026h
maxshipy_street		equ	GROUNDLEVEL - 030h
maxshipy_pyramid	equ	GROUNDLEVEL - 024h
maxshipy_water		equ	GROUNDLEVEL - 028h
maxshipy_ice		equ	GROUNDLEVEL - 02ch
maxshipy_train		equ	GROUNDLEVEL - 01eh
maxshipy_moon		equ	GROUNDLEVEL - 01eh

; map the level and alien names
	maplevel 1, forest, justufos
	maplevel 2, water, justdiscs
	maplevel 3, street, ufodiscs
	maplevel 4, pyramid, introattack
	maplevel 5, ice, introrand
	maplevel 6, train, introboom
	maplevel 7, moon, difficult
