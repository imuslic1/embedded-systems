.section .data
N:          .word 48         @ Ovdje definiramo konstantu N (može biti 47 ili 48)
fibonacci:  .space 192       @ Rezerviramo dovoljno prostora za 48 Fibonaccijevih brojeva (48 * 4 = 192 bajta)

.section .text
.global _start
.global generate_fibonacci
.global done

_start:
    ldr r1, =N               @ Učitaj adresu N u r1
    ldr r2, [r1]             @ Učitaj vrijednost N u r2
    ldr r3, =fibonacci       @ r3 pokazuje na početak niza Fibonaccijevih brojeva

    mov r4, #1               @ Prvi broj je 1
    str r4, [r3], #4         @ Spremi prvi broj u memoriju i povećaj r3 za 4

    mov r4, #1               @ Drugi broj je 1
    str r4, [r3], #4         @ Spremi drugi broj u memoriju i povećaj r3 za 4

    subs r2, r2, #2          @ Smanji N za 2 jer smo već generirali prva dva broja
	cmp r2, #0
    beq done                 @ Ako je N bilo 2, završavamo jer smo već generirali dva broja

generate_fibonacci:
    ldr r4, [r3, #-4]        @ Učitaj prethodni broj (n-1)
    ldr r5, [r3, #-8]        @ Učitaj pretprethodni broj (n-2)
    add r4, r4, r5           @ Računaj trenutni broj kao zbroj prethodna dva
    str r4, [r3], #4         @ Spremi trenutni broj u memoriju i povećaj r3 za 4

    subs r2, r2, #1  		 @ Smanjuj N za 1
	cmp r2, #0
    bne generate_fibonacci   @ Ponavljaj dok r2 ne postane 0
	beq done

done:
	@mov r0, #0              @ Status kod 0
    @mov r7, #1              @ Syscall za exit
    @swi 0                   @ Prekid za syscall
	b done
