; $Id: flashdefs.h 323 2007-07-08 16:22:12Z sgust $

; History:
; Version 1.0
;   first release
;
; This is the firmware for my FlashCART design.

; Copyright (C) 2007 by Soeren Gust, sgust@ithh.informationstheater.de

; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:

; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.

; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
; THE SOFTWARE.

; You can always get the latest version at http://soeren.informationstheater.de

; variables
iram_header		equ	020h	; header for communications
iram_hd_len		equ	020h
iram_hd_cmd		equ	021h	; command
iram_hd_adrh		equ	022h	; address high byte
iram_hd_adrm		equ	023h	; address middle byte
iram_hd_adrl		equ	024h	; address low byte
iram_hd_hsum		equ	025h	; header checksum
iram_hd_dsumh		equ	026h	; data checksum low byte
iram_hd_dsuml		equ	027h	; data checksum high byte
iram_sizeofheader	equ	8	; length of header
iram_sizeofheadersum	equ	5	; length of checksummed header

iram_mode		equ	03fh	; bit register, bits are following
iram_mode_plus		equ	0	; 1 if running on VP+
iram_mode_pal		equ	1	; 1 if running on PAL
iram_mode_local		equ	2	; 1 if command is program generated

; protocol commands/error codes
CMD_NOP		equ	0		; do nothing
CMD_FIRMWARE	equ	1		; read firmware version
CMD_END		equ	2		; end communication, only when embedded

CMD_FLS_RD	equ	010h		; read flash at adr
CMD_FLS_WR	equ	011h		; write flash
CMD_FLS_ER 	equ	012h		; erase flash at adr
CMD_FLS_ID	equ	013h		; return flash id
CMD_FLS_DWR	equ	014h		; direct write

CMD_EEP_RD	equ	020h		; read eeprom
CMD_EEP_WR	equ	021h		; write eeprom
CMD_EEP_ER	equ	022h		; erase eeprom
CMD_EEP_ID	equ	023h		; return eeprom address length

CMD_VDC_WR	equ	030h		; write to vdc
CMD_VPP_RD	equ	031h		; read from vpp
CMD_VPP_WR	equ	032h		; write to vpp
CMD_VPP_RDSL	equ	033h		; read from vpp slice
CMD_VPP_WRSL	equ	034h		; write to vpp slice
CMD_VPP_MODE	equ	035h		; call plusmode
CMD_VPP_CMD	equ	036h		; call pluscmd

CMD_ANSWER	equ	080h		; answer mark

CMD_ERR_NOCMD	equ	0F6h		; unknown command
CMD_ERR_NOEEP	equ	0F7h		; no EEPROM found
CMD_ERR_REFUSE	equ	0F8h		; refuse to execute
CMD_ERR_NOVPP	equ	0F9h		; command needs Videopac+
CMD_ERR_ERASE	equ	0FAh		; error erasing
CMD_ERR_VRFY	equ	0FBh		; verify error
CMD_ERR_WRITE	equ	0FCh		; write error
CMD_ERR_HSUM	equ	0FDh		; header checksum mismatch
CMD_ERR_DSUM	equ	0FEh		; data checksum mismatch
CMD_ERR_TIME	equ	0FFh		; timeout

; internal returncodes
RET_OK		equ	0
RET_TIMEOUT	equ	1
RET_HSUM	equ	2
RET_DSUM	equ	3

; The addresses to call the firmware
commapi_init		equ	0500h
commapi_version		equ	0502h
commapi_readblock	equ	0504h
commapi_execcmd		equ	0506h
commapi_eepromsize	equ	0508h
commapi_eepromread	equ	050ah
commapi_eepromwrite	equ	050ch
