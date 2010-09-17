.text

# On an exception, push a fake stack thread mode stack frame and redirect
# thread execution to a thread mode error handler

# From RM008:
# The SP is decremented by eight words by the completion of the stack push.
# Figure 5-1 shows the contents of the stack after an exception pre-empts the
# current program flow.
#
# Old SP--> <previous>
#           xPSR
#           PC
#           LR
#           r12
#           r3
#           r2
#           r1
#    SP-->  r0

.globl HardFaultException
.thumb_func
HardFaultException:
   ldr r0, CPSR_MASK           @ Set default CPSR
   push {r0}
   ldr r0, TARGET_PC           @ Set target pc
   push {r0}
   sub sp, sp, #24             @ its not like i even care
   ldr r0, EXC_RETURN          @ Return to thread mode
   mov lr, r0
   bx lr                       @ Exception exit

 .align 4
 CPSR_MASK:  .word 0x61000000
 EXC_RETURN: .word 0xFFFFFFF9
 TARGET_PC:  .word throb


