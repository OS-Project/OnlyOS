.global _start
.global _estack
.global _sbss
.global _ebss

.equ  UND_STACK_SIZE, 0x8
.equ  ABT_STACK_SIZE, 0x8
.equ  FIQ_STACK_SIZE, 0x8
.equ  IRQ_STACK_SIZE, 0x100
.equ  SVC_STACK_SIZE, 0x30

.equ  MODE_UND, 0x1B     
.equ  MODE_USR, 0x10            
.equ  MODE_FIQ, 0x11
.equ  MODE_IRQ, 0x12
.equ  MODE_SVC, 0x13
.equ  MODE_ABT, 0x17
.equ  MODE_SYS, 0x1F            

.equ FIQ_BIT, 0x40
.equ IRQ_BIT, 0x80               


.global _start
.global error
.global svc_asm_call



