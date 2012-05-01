[ORG 0]

jmp 07C0h:start         ; Goto segment 07C0

;-----------------------------------------
    msg     db  'Hello World',0


    start:
		
            ; Update the segment registers
            mov ax, cs
            mov ds, ax
            mov es, ax


            mov si, msg     ; Print msg
    print:
            lodsb           ; AL=memory contents at DS:SI

            cmp al, 0       ; If AL=0 then hang
            je hang

            mov ah, 0Eh     ; Print AL
            mov bx, 7
            int 10h

            jmp print       ; Print next character


    hang:                   ; Hang!
            jmp hang

;---------------------------------------- 
times 510-($-$$) db 0
dw 0AA55h

