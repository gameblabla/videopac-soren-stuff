; This file defines a codepage named videopac. After including this file you
; can define string constants for the G7000 by switching to this codepage
; with "codepage videopac". This does only work with asl.

; $Id: charset.h 390 2003-07-19 12:41:28Z sgust $

; Copyright (C) 2003 by Soeren Gust, sgust@ithh.informationstheater.de

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

	codepage videopac

	; The numbers
	charset '0',0
	charset '1',1
	charset '2',2
	charset '3',3
	charset '4',4
	charset '5',5
	charset '6',6
	charset '7',7
	charset '8',8
	charset '9',9

	; A-Z
	charset 'A',020h
	charset 'B',025h
	charset 'C',023h
	charset 'D',01ah
	charset 'E',012h
	charset 'F',01bh
	charset 'G',01ch
	charset 'H',01dh
	charset 'I',016h
	charset 'J',01eh
	charset 'K',01fh
	charset 'L',00eh
	charset 'M',026h
	charset 'N',02dh
	charset 'O',017h
	charset 'P',00fh
	charset 'Q',018h
	charset 'R',013h
	charset 'S',019h
	charset 'T',014h
	charset 'U',015h
	charset 'V',024h
	charset 'W',011h
	charset 'X',022h
	charset 'Y',02ch
	charset 'Z',021h

	; other
	charset ' ',00ch
	charset ':',00ah
	charset '$',00bh
	charset '?',00dh
	charset '+',010h
	charset '.',027h
	charset '-',028h
	charset '*',029h
	charset '=',02bh
	charset '/',02eh
	charset '\\',03bh
	charset '#',02fh
	charset '[',032h
	charset ']',035h
	charset '^',037h
	charset '~',036h
	charset '>',038h
	charset '<',039h

	codepage standard
