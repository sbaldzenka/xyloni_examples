
build/leds_blinking.elf:     file format elf32-littleriscv


Disassembly of section .init:

f9000000 <_start>:

_start:
#ifdef USE_GP
.option push
.option norelax
	la gp, __global_pointer$
f9000000:	00001197          	auipc	gp,0x1
f9000004:	96018193          	addi	gp,gp,-1696 # f9000960 <__global_pointer$>

f9000008 <init>:
	sw a0, smp_lottery_lock, a1
    ret
#endif

init:
	la sp, _sp
f9000008:	a2018113          	addi	sp,gp,-1504 # f9000380 <__freertos_irq_stack_top>

	/* Load data section */
	la a0, _data_lma
f900000c:	81018513          	addi	a0,gp,-2032 # f9000170 <_data>
	la a1, _data
f9000010:	81018593          	addi	a1,gp,-2032 # f9000170 <_data>
	la a2, _edata
f9000014:	81c18613          	addi	a2,gp,-2020 # f900017c <__bss_start>
	bgeu a1, a2, 2f
f9000018:	00c5fc63          	bgeu	a1,a2,f9000030 <init+0x28>
1:
	lw t0, (a0)
f900001c:	00052283          	lw	t0,0(a0)
	sw t0, (a1)
f9000020:	0055a023          	sw	t0,0(a1)
	addi a0, a0, 4
f9000024:	00450513          	addi	a0,a0,4
	addi a1, a1, 4
f9000028:	00458593          	addi	a1,a1,4
	bltu a1, a2, 1b
f900002c:	fec5e8e3          	bltu	a1,a2,f900001c <init+0x14>
2:

	/* Clear bss section */
	la a0, __bss_start
f9000030:	81c18513          	addi	a0,gp,-2020 # f900017c <__bss_start>
	la a1, _end
f9000034:	82018593          	addi	a1,gp,-2016 # f9000180 <_end>
	bgeu a0, a1, 2f
f9000038:	00b57863          	bgeu	a0,a1,f9000048 <init+0x40>
1:
	sw zero, (a0)
f900003c:	00052023          	sw	zero,0(a0)
	addi a0, a0, 4
f9000040:	00450513          	addi	a0,a0,4
	bltu a0, a1, 1b
f9000044:	feb56ce3          	bltu	a0,a1,f900003c <init+0x34>
2:

#ifndef NO_LIBC_INIT_ARRAY
	call __libc_init_array
f9000048:	010000ef          	jal	ra,f9000058 <__libc_init_array>
#endif

	call main
f900004c:	0c4000ef          	jal	ra,f9000110 <main>

f9000050 <mainDone>:
mainDone:
    j mainDone
f9000050:	0000006f          	j	f9000050 <mainDone>

f9000054 <_init>:


	.globl _init
_init:
    ret
f9000054:	00008067          	ret

Disassembly of section .text:

f9000058 <__libc_init_array>:
f9000058:	ff010113          	addi	sp,sp,-16
f900005c:	00812423          	sw	s0,8(sp)
f9000060:	01212023          	sw	s2,0(sp)
f9000064:	81018413          	addi	s0,gp,-2032 # f9000170 <_data>
f9000068:	81018913          	addi	s2,gp,-2032 # f9000170 <_data>
f900006c:	40890933          	sub	s2,s2,s0
f9000070:	00112623          	sw	ra,12(sp)
f9000074:	00912223          	sw	s1,4(sp)
f9000078:	40295913          	srai	s2,s2,0x2
f900007c:	00090e63          	beqz	s2,f9000098 <__libc_init_array+0x40>
f9000080:	00000493          	li	s1,0
f9000084:	00042783          	lw	a5,0(s0)
f9000088:	00148493          	addi	s1,s1,1
f900008c:	00440413          	addi	s0,s0,4
f9000090:	000780e7          	jalr	a5
f9000094:	fe9918e3          	bne	s2,s1,f9000084 <__libc_init_array+0x2c>
f9000098:	81018413          	addi	s0,gp,-2032 # f9000170 <_data>
f900009c:	81018913          	addi	s2,gp,-2032 # f9000170 <_data>
f90000a0:	40890933          	sub	s2,s2,s0
f90000a4:	40295913          	srai	s2,s2,0x2
f90000a8:	00090e63          	beqz	s2,f90000c4 <__libc_init_array+0x6c>
f90000ac:	00000493          	li	s1,0
f90000b0:	00042783          	lw	a5,0(s0)
f90000b4:	00148493          	addi	s1,s1,1
f90000b8:	00440413          	addi	s0,s0,4
f90000bc:	000780e7          	jalr	a5
f90000c0:	fe9918e3          	bne	s2,s1,f90000b0 <__libc_init_array+0x58>
f90000c4:	00c12083          	lw	ra,12(sp)
f90000c8:	00812403          	lw	s0,8(sp)
f90000cc:	00412483          	lw	s1,4(sp)
f90000d0:	00012903          	lw	s2,0(sp)
f90000d4:	01010113          	addi	sp,sp,16
f90000d8:	00008067          	ret

f90000dc <clint_uDelay>:
*          and the time limit is non-negative, indicating that the delay has
*          not yet elapsed.
*
******************************************************************************/
    static void clint_uDelay(u32 usec, u32 hz, u32 reg){
        u32 mTimePerUsec = hz/1000000;
f90000dc:	000f47b7          	lui	a5,0xf4
f90000e0:	24078793          	addi	a5,a5,576 # f4240 <__stack_size+0xf4040>
f90000e4:	02f5d5b3          	divu	a1,a1,a5
    readReg_u32 (clint_getTimeLow , CLINT_TIME_ADDR)
f90000e8:	0000c7b7          	lui	a5,0xc
f90000ec:	ff878793          	addi	a5,a5,-8 # bff8 <__stack_size+0xbdf8>
f90000f0:	00f60633          	add	a2,a2,a5
*          so the 'volatile' keyword is used to prevent the compiler from
*          optimizing away or reordering the read operation.
*
******************************************************************************/
    static inline u32 read_u32(u32 address){
        return *((volatile u32*) address);
f90000f4:	00062783          	lw	a5,0(a2)
        u32 limit = clint_getTimeLow(reg) + usec*mTimePerUsec;
f90000f8:	02a58533          	mul	a0,a1,a0
f90000fc:	00f50533          	add	a0,a0,a5
f9000100:	00062783          	lw	a5,0(a2)
        while((int32_t)(limit-(clint_getTimeLow(reg))) >= 0);
f9000104:	40f507b3          	sub	a5,a0,a5
f9000108:	fe07dce3          	bgez	a5,f9000100 <clint_uDelay+0x24>
f900010c:	00008067          	ret

f9000110 <main>:
#include <stdint.h>
#include "bsp.h"
#include "gpio.h"

void main()
{
f9000110:	ff010113          	addi	sp,sp,-16
f9000114:	00112623          	sw	ra,12(sp)
f9000118:	00812423          	sw	s0,8(sp)
f900011c:	00912223          	sw	s1,4(sp)
f9000120:	01212023          	sw	s2,0(sp)
*          optimizing away or reordering the write operation.
*
******************************************************************************/

    static inline void write_u32(u32 data, u32 address){
        *((volatile u32*) address) = data;
f9000124:	f80157b7          	lui	a5,0xf8015
f9000128:	00f00713          	li	a4,15
f900012c:	00e7a423          	sw	a4,8(a5) # f8015008 <__global_pointer$+0xff0146a8>
f9000130:	f8015937          	lui	s2,0xf8015
f9000134:	00100793          	li	a5,1
f9000138:	00f92223          	sw	a5,4(s2) # f8015004 <__global_pointer$+0xff0146a4>
    gpio_setOutputEnable(SYSTEM_GPIO_0_IO_CTRL, 0xF);

    while(1)
    {
    	gpio_setOutput(SYSTEM_GPIO_0_IO_CTRL,0x1);
    	bsp_uDelay(200*1000);
f900013c:	f8b00637          	lui	a2,0xf8b00
f9000140:	017d84b7          	lui	s1,0x17d8
f9000144:	84048593          	addi	a1,s1,-1984 # 17d7840 <__stack_size+0x17d7640>
f9000148:	00031437          	lui	s0,0x31
f900014c:	d4040513          	addi	a0,s0,-704 # 30d40 <__stack_size+0x30b40>
f9000150:	f8dff0ef          	jal	ra,f90000dc <clint_uDelay>
f9000154:	00200793          	li	a5,2
f9000158:	00f92223          	sw	a5,4(s2)
    	gpio_setOutput(SYSTEM_GPIO_0_IO_CTRL,0x2);
        bsp_uDelay(200*1000);
f900015c:	f8b00637          	lui	a2,0xf8b00
f9000160:	84048593          	addi	a1,s1,-1984
f9000164:	d4040513          	addi	a0,s0,-704
f9000168:	f75ff0ef          	jal	ra,f90000dc <clint_uDelay>
f900016c:	fc5ff06f          	j	f9000130 <main+0x20>
