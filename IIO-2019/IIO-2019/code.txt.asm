.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib "D:\Visual Studio 2019\YAP\IIO\IIO-2019\Debug\Lib.lib"
	ExitProcess PROTO :DWORD

	readw PROTO: DWORD
	readr PROTO: DWORD
	strln PROTO: DWORD
	strton PROTO: BYTE

.stack 4096
.const
	L0 DWORD 15
	L1 DWORD 8
	L2 DWORD 10
	L3 DWORD 70
	L4 DWORD 71
	L5 DWORD 0
	L6 DWORD 4
	L7 BYTE "NEGATIVE ELEMENT", 0
	L8 BYTE "Result of AND", 0
	L9 BYTE "Result of OR", 0
	L10 BYTE "Result of NOT", 0
	L11 BYTE "IIO-2019", 0
	L12 BYTE "RESULT STRLN(IIO-2019)", 0
	L13 BYTE "5", 0
	L14 BYTE "Result of STRTON", 0
	L15 DWORD 22
	L16 BYTE "RESULT strton plus 22", 0
	L17 BYTE "Result of CYCLE", 0
	L18 DWORD 7
	L19 DWORD 6
	L20 BYTE "RESULT FUNC SECOND", 0
	L21 DWORD 74
	L22 BYTE "Program end.IIO-2019", 0
.data
	firstfx DWORD ?
	secondres DWORD ?
	startonea DWORD ?
	starttwoa DWORD ?
	startoneo DWORD ?
	starttwoo DWORD ?
	startinvrt DWORD ?
	startresa DWORD ?
	startreso DWORD ?
	startresn DWORD ?
	startresng DWORD ?
	startonestr DWORD ?
	starttwostr DWORD ?
	startresln DWORD ?
	startresstn DWORD ?
	startoneapp DWORD ?
	starttwoapp DWORD ?
	startthapp DWORD ?
	startfrapp DWORD ?
	startsys DWORD ?
	startresf DWORD ?

.code

first PROC firstfb : DWORD
	push firstfb
	pop edx
	push firstfb
	call strln
	push eax
	pop firstfx
	push firstfx
	ret
first ENDP

second PROC secondsa : SDWORD, secondsb : SDWORD
	push secondsa
	push secondsb
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop secondres
	push secondres
	ret
second ENDP

main PROC
	push L0
	pop startonea
	push L1
	pop starttwoa
	push L0
	pop startoneo
	push L1
	pop starttwoo
	push L2
	pop startinvrt
	push L3
	pop startoneapp
	push L4
	pop starttwoapp
	push L5
	push L6
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop startresng
	push offset L7
		call readw
	push startresng
		call readr
	push offset L8
		call readw
	push startonea
	push starttwoa
	pop eax
	pop ebx
	and eax, ebx
	push eax
	pop startresa
	push startresa
		call readr
	push offset L9
		call readw
	push startoneo
	push starttwoo
	pop eax
	pop ebx
	or eax, ebx
	push eax
	pop startreso
	push startreso
		call readr
	push offset L10
		call readw
	push startinvrt
	pop startresn
	push startresn
		call readr
	push offset L11
	pop startonestr
	push offset L12
		call readw
	push startonestr
	pop edx
	push startonestr
	call first
	push eax
	pop startresln
	push startresln
		call readr
	push offset L13
	pop starttwostr
	push offset L14
		call readw
	push starttwostr
	pop edx
	push starttwostr
	call strton
	push eax
	pop startresstn
	push startresstn
		call readr
	push startresstn
	push L15
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop startthapp
	push offset L16
		call readw
	push startthapp
		call readr
	push offset L17
		call readw
	mov ecx, L18
Mark:
	push startfrapp
	push L19
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop startfrapp
	push startfrapp
loop Mark
	push startfrapp
		call readr
	push offset L20
		call readw
	push startoneapp
	push starttwoapp
	pop edx
	pop edx
	push starttwoapp
	push startoneapp
	call second
	push eax
	pop startresf
	push startresf
		call readr
	push L21
	pop startsys
	push offset L22
		call readw
	push 0
	call ExitProcess
main ENDP
end main