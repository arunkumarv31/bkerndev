[ORG 0]

jmp 07C0h:start         ; Goto segment 07C0

start:
	mov ax, cs
	mov ds, ax
	mov es, ax

    hang:                           ; Hang!
        jmp hang
 
times 510-($-$$) db 0
dw 0AA55h

