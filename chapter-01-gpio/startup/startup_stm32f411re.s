    .syntax unified
    .cpu cortex-m4
    .fpu softvfp
    .thumb

    .global g_pfnVectors
    .global Default_Handler

/* Reset handler */
    .section .text.Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    /* Copy .data section from flash to RAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit

    /* Zero .bss section */
    ldr r2, =_sbss
    ldr r4, =_ebss
    movs r3, #0
    b LoopFillZerobss

FillZerobss:
    str r3, [r2]
    adds r2, r2, #4

LoopFillZerobss:
    cmp r2, r4
    bcc FillZerobss

    /* Call SystemInit (can be a stub or CMSIS init) */
    bl SystemInit

    /* Call main */
    bl main

LoopForever:
    b LoopForever

    .size Reset_Handler, .-Reset_Handler

/* Default handler for unhandled interrupts */
    .section .text.Default_Handler,"ax",%progbits
    .weak Default_Handler
    .type Default_Handler, %function
Default_Handler:
    b Default_Handler
    .size Default_Handler, .-Default_Handler

/* Weak aliases for all exception/interrupt handlers */
    .macro WEAK_ALIAS name
    .weak \name
    .set \name, Default_Handler
    .endm

    WEAK_ALIAS NMI_Handler
    WEAK_ALIAS HardFault_Handler
    WEAK_ALIAS MemManage_Handler
    WEAK_ALIAS BusFault_Handler
    WEAK_ALIAS UsageFault_Handler
    WEAK_ALIAS SVC_Handler
    WEAK_ALIAS DebugMon_Handler
    WEAK_ALIAS PendSV_Handler
    WEAK_ALIAS SysTick_Handler

/* Weak stub for SystemInit */
    .weak SystemInit
    .type SystemInit, %function
SystemInit:
    bx lr
    .size SystemInit, .-SystemInit

/* Vector table */
    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object

g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .word BusFault_Handler
    .word UsageFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word DebugMon_Handler
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler

    .size g_pfnVectors, .-g_pfnVectors
