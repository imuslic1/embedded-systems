.section .data
    buffer_size: .int 12            @ Definiramo veličinu bafera za unos
    input_buffer: .space 12         @ Rezerviramo prostor za unos broja (ASCII)

.section .bss
    number: .word 0                 @ Memorijska lokacija za cijeli broj

.section .text
    .global _start

_start:
    @ Učitavanje broja sa stdin
    ldr r1, =input_buffer           @ Učitaj adresu bafera
    ldr r2, =buffer_size            @ Učitaj veličinu bafera
    ldr r2, [r2]                    @ Učitaj vrijednost veličine bafera

    @ Syscall za čitanje sa stdin
    mov r7, #3                      @ Syscall broj za read
    mov r0, #0                      @ File descriptor za stdin
    mov r2, #12                     @ Maksimalni broj bajtova za čitanje
    swi 0                           @ Poziv syscall

    @ Konverzija ASCII na integer
    ldr r0, =input_buffer           @ Adresa bafera sa unesenim podacima
    mov r1, #0                      @ Inicijaliziraj rezultat na 0
    mov r2, #0                      @ Inicijaliziraj privremeni registar za rezultat

convert_loop:
    ldrb r3, [r0], #1               @ Učitaj naredni karakter iz bafera
    cmp r3, #10                     @ Provjeri je li kraj linije (ASCII kod za novi red)
    beq store_number                @ Ako je kraj linije, spremi broj
    sub r3, r3, #48                 @ Pretvori ASCII karakter u cifru (0-9)
    
    @ r1 = r1 * 10
    mov r4, r1, lsl #3              @ r4 = r1 * 8
    add r1, r4, r1, lsl #1          @ r1 = r4 + r1 * 2 = r1 * 10
    
    add r1, r1, r3                  @ Dodaj cifru u rezultat
    b convert_loop                  @ Nastavi konverziju

store_number:
    ldr r0, =number                 @ Učitaj adresu memorijske lokacije
    str r1, [r0]                    @ Spremi konvertirani broj u memorijsku lokaciju

    @ Završetak programa
    mov r7, #1                      @ Syscall broj za exit
    mov r0, #0                      @ Status kod 0
    swi 0                           @ Prekid za syscall
