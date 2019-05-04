    .text
    .global start

start:
  ldr sp, =stack_top
  bl sum
stop: b stop

sum:
  stmfd sp!, {r0-r4, lr}
  mov r0, #0
  ldr r1, =array
  ldr r2, =array_size
  ldr r2, [r2]
  sum_loop:
    ldr r3, [r1], #4
    add r0, r0, r3
    sub r2, r2, #1
    cmp r2, #0
    bne sum_loop
  ldr r4, =result
  str r0, [r4]
  ldmfd sp!, {r0-r4, pc}

    .data
array_size: .word 10
array: .word 1,2,3,4,5,6,7,8,9,10
result: .word 0
