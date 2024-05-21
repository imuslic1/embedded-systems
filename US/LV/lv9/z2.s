.data
prompt1:
    .asciz "Unesite proizvoljan tekst:\n"
prompt2:
    .asciz "Unesen je tekst:\n"
tekst:
    .asciz "                   "        @ Buffer to store the input (20 spaces)

.text
.global _start

_start:
    @ Display the first prompt
    mov     r7, #4                      @ syscall number for sys_write
    mov     r0, #1                      @ file descriptor 1 (stdout)
    ldr     r1, =prompt1                @ address of prompt1
    mov     r2, #27                     @ length of prompt1 string
    swi     #0                          @ make the syscall

    @ Read the input text
    mov     r7, #3                      @ syscall number for sys_read
    mov     r0, #0                      @ file descriptor 0 (stdin)
    ldr     r1, =tekst                  @ address of tekst buffer
    mov     r2, #20                     @ number of bytes to read (assuming 20 characters max)
    swi     #0                          @ make the syscall

    @ Selection sort the tekst array
    ldr     r1, =tekst                  @ address of tekst buffer
    mov     r2, #20                     @ number of elements in the array

selection_sort:
    mov     r3, #0                      @ i = 0

outer_loop:
    cmp     r3, r2                      @ if (i >= 20)
    bge     end_sort                    @ break

    mov     r4, r3                      @ min_index = i
    add     r5, r3, #1                  @ j = i + 1

inner_loop:
    cmp     r5, r2                      @ if (j >= 20)
    bge     update_min                  @ break

    ldrb    r6, [r1, r5]                @ r6 = tekst[j]
    ldrb    r7, [r1, r4]                @ r7 = tekst[min_index]
    cmp     r6, r7                      @ if (tekst[j] < tekst[min_index])
    bge     skip_update                 @ skip if r6 >= r7
    mov     r4, r5                      @ min_index = j

skip_update:
    add     r5, r5, #1                  @ j = j + 1
    b inner_loop                        @ continue inner loop

update_min:
    cmp     r3, r4                      @ if (i != min_index)
    beq     no_swap                     @ skip swap if i == min_index

    ldrb    r6, [r1, r3]                @ r6 = tekst[i]
    ldrb    r7, [r1, r4]                @ r7 = tekst[min_index]
    strb    r7, [r1, r3]                @ tekst[i] = tekst[min_index]
    strb    r6, [r1, r4]                @ tekst[min_index] = tekst[i]

no_swap:
    add     r3, r3, #1                  @ i = i + 1
    b outer_loop                        @ continue outer loop

end_sort:
    @ Display the second prompt
    mov     r7, #4                      @ syscall number for sys_write
    mov     r0, #1                      @ file descriptor 1 (stdout)
    ldr     r1, =prompt2                @ address of prompt2
    mov     r2, #17                     @ length of prompt2 string
    swi     #0                          @ make the syscall

    @ Display the sorted tekst
    mov     r7, #4                      @ syscall number for sys_write
    mov     r0, #1                      @ file descriptor 1 (stdout)
    ldr     r1, =tekst                  @ address of tekst buffer
    mov     r2, #20                     @ length of tekst buffer (20 characters)
    swi     #0                          @ make the syscall

    @ Exit the program
    mov     r7, #1                      @ syscall number for sys_exit
    swi     #0                          @ make the syscall
