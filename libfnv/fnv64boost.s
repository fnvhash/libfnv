        .globl  fnv64boost

        .text
fnv64boost:
        mov     %rdx, %rax
        mov     %rsi, %rcx
        movq    $0x100000001b3, %rsi
        xor     %rdx, %rdx
nexta:
        movb (%rdi), %dl
        xorb    %dl, %al
        mul     %rsi
        inc     %rdi
        dec     %rcx
        jnz nexta
        ret
