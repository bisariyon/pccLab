START:   MOV A, B          ; Move contents of B to A
         ADD C            ; Add contents of C to A
         MOV D, A         ; Move contents of A to D
         SUB E            ; Subtract contents of E from A
         JZ ZERO          ; Jump to ZERO if A is zero
         INX H            ; Increment H register
         JMP START        ; Repeat the loop

ZERO:    MVI A, 00H       ; Load immediate value 00H into A
         OUT 01H          ; Output the value of A to port 01H
         HLT               ; Halt the program
