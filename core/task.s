
task.o:     file format elf32-i386
task.o
architecture: i386, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x00000000

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         000004cc  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000500  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000104  00000000  00000000  00000500  2**5
                  ALLOC
  3 .rodata.str1.1 00000097  00000000  00000000  00000500  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .rodata       00000028  00000000  00000000  00000597  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .comment      00000035  00000000  00000000  000005bf  2**0
                  CONTENTS, READONLY
  6 .note.GNU-stack 00000000  00000000  00000000  000005f4  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
00000000 l    df *ABS*	00000000 task.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss	00000000 .bss
00000100 l     O .bss	00000004 _os_current_task
00000000 l     O .bss	00000100 _os_ready_queue
00000000 l    d  .rodata.str1.1	00000000 .rodata.str1.1
00000000 l     O .rodata	0000000e __FUNCTION__.1593
0000000e l     O .rodata	0000000a __FUNCTION__.1577
00000018 l     O .rodata	00000010 __FUNCTION__.1498
00000000 l    d  .rodata	00000000 .rodata
00000000 l    d  .note.GNU-stack	00000000 .note.GNU-stack
00000000 l    d  .comment	00000000 .comment
00000000 g     F .text	00000007 eos_destroy_task
00000007 g     F .text	0000000a eos_get_current_task
00000011 g     F .text	0000000b eos_get_priority
0000001c g     F .text	0000000b eos_get_period
00000027 g     F .text	00000005 _os_wakeup_all
0000002c g     F .text	0000004e eos_suspend_task
00000000         *UND*	00000000 _os_remove_node
00000000         *UND*	00000000 _os_unset_ready
0000007a g     F .text	000000e3 _os_schedule
00000000         *UND*	00000000 eos_disable_interrupt
00000001       O *COM*	00000001 _os_scheduler_lock
00000000         *UND*	00000000 eos_restore_interrupt
00000000         *UND*	00000000 _os_add_node_tail
00000000         *UND*	00000000 _os_set_ready
00000000         *UND*	00000000 _os_save_context
00000000         *UND*	00000000 _os_get_highest_priority
00000000         *UND*	00000000 _os_restore_context
0000015d g     F .text	00000058 _os_wakeup_task
000001b5 g     F .text	00000054 _os_wakeup_queue
00000209 g     F .text	0000004e _os_wait
00000000         *UND*	00000000 _os_add_node_priority
00000257 g     F .text	00000043 eos_resume_task
0000029a g     F .text	0000007b eos_change_priority
00000315 g     F .text	00000048 _os_init_task
00000000         *UND*	00000000 eos_printf
0000035d g     F .text	0000001e eos_set_period
00000000         *UND*	00000000 eos_get_system_timer
0000037b g     F .text	000000c3 eos_sleep
00000000         *UND*	00000000 eos_get_scheduler_lock
00000000         *UND*	00000000 eos_set_alarm
0000043e g     F .text	0000008e eos_create_task
00000000         *UND*	00000000 _os_create_context
00000001       O *COM*	00000001 _os_ready_group
00000008       O *COM*	00000001 _os_ready_table



Disassembly of section .text:

00000000 <eos_destroy_task>:
   0:	55                   	push   %ebp
   1:	31 c0                	xor    %eax,%eax
   3:	89 e5                	mov    %esp,%ebp
   5:	5d                   	pop    %ebp
   6:	c3                   	ret    

00000007 <eos_get_current_task>:
   7:	55                   	push   %ebp
   8:	a1 00 01 00 00       	mov    0x100,%eax
			9: R_386_32	.bss
   d:	89 e5                	mov    %esp,%ebp
   f:	5d                   	pop    %ebp
  10:	c3                   	ret    

00000011 <eos_get_priority>:
  11:	55                   	push   %ebp
  12:	89 e5                	mov    %esp,%ebp
  14:	8b 45 08             	mov    0x8(%ebp),%eax
  17:	5d                   	pop    %ebp
  18:	8b 40 08             	mov    0x8(%eax),%eax
  1b:	c3                   	ret    

0000001c <eos_get_period>:
  1c:	55                   	push   %ebp
  1d:	89 e5                	mov    %esp,%ebp
  1f:	8b 45 08             	mov    0x8(%ebp),%eax
  22:	5d                   	pop    %ebp
  23:	8b 40 0c             	mov    0xc(%eax),%eax
  26:	c3                   	ret    

00000027 <_os_wakeup_all>:
  27:	55                   	push   %ebp
  28:	89 e5                	mov    %esp,%ebp
  2a:	5d                   	pop    %ebp
  2b:	c3                   	ret    

0000002c <eos_suspend_task>:
  2c:	55                   	push   %ebp
  2d:	89 e5                	mov    %esp,%ebp
  2f:	53                   	push   %ebx
  30:	83 ec 04             	sub    $0x4,%esp
  33:	8b 5d 08             	mov    0x8(%ebp),%ebx
  36:	80 3b 01             	cmpb   $0x1,(%ebx)
  39:	75 38                	jne    73 <eos_suspend_task+0x47>
  3b:	50                   	push   %eax
  3c:	50                   	push   %eax
  3d:	8d 43 30             	lea    0x30(%ebx),%eax
  40:	50                   	push   %eax
  41:	8b 43 08             	mov    0x8(%ebx),%eax
  44:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			47: R_386_32	.bss
  4b:	50                   	push   %eax
  4c:	e8 fc ff ff ff       	call   4d <eos_suspend_task+0x21>
			4d: R_386_PC32	_os_remove_node
  51:	8b 43 08             	mov    0x8(%ebx),%eax
  54:	83 c4 10             	add    $0x10,%esp
  57:	83 3c 85 00 00 00 00 	cmpl   $0x0,0x0(,%eax,4)
  5e:	00 
			5a: R_386_32	.bss
  5f:	75 0f                	jne    70 <eos_suspend_task+0x44>
  61:	83 ec 0c             	sub    $0xc,%esp
  64:	0f b6 c0             	movzbl %al,%eax
  67:	50                   	push   %eax
  68:	e8 fc ff ff ff       	call   69 <eos_suspend_task+0x3d>
			69: R_386_PC32	_os_unset_ready
  6d:	83 c4 10             	add    $0x10,%esp
  70:	c6 03 04             	movb   $0x4,(%ebx)
  73:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  76:	31 c0                	xor    %eax,%eax
  78:	c9                   	leave  
  79:	c3                   	ret    

0000007a <_os_schedule>:
  7a:	55                   	push   %ebp
  7b:	89 e5                	mov    %esp,%ebp
  7d:	53                   	push   %ebx
  7e:	83 ec 04             	sub    $0x4,%esp
  81:	e8 fc ff ff ff       	call   82 <_os_schedule+0x8>
			82: R_386_PC32	eos_disable_interrupt
  86:	80 3d 00 00 00 00 01 	cmpb   $0x1,0x0
			88: R_386_32	_os_scheduler_lock
  8d:	75 0e                	jne    9d <_os_schedule+0x23>
  8f:	83 ec 0c             	sub    $0xc,%esp
  92:	50                   	push   %eax
  93:	e8 fc ff ff ff       	call   94 <_os_schedule+0x1a>
			94: R_386_PC32	eos_restore_interrupt
  98:	e9 b8 00 00 00       	jmp    155 <_os_schedule+0xdb>
  9d:	83 ec 0c             	sub    $0xc,%esp
  a0:	50                   	push   %eax
  a1:	e8 fc ff ff ff       	call   a2 <_os_schedule+0x28>
			a2: R_386_PC32	eos_restore_interrupt
  a6:	8b 15 00 01 00 00    	mov    0x100,%edx
			a8: R_386_32	.bss
  ac:	83 c4 10             	add    $0x10,%esp
  af:	85 d2                	test   %edx,%edx
  b1:	74 4a                	je     fd <_os_schedule+0x83>
  b3:	80 3a 02             	cmpb   $0x2,(%edx)
  b6:	75 32                	jne    ea <_os_schedule+0x70>
  b8:	51                   	push   %ecx
  b9:	51                   	push   %ecx
  ba:	8d 42 30             	lea    0x30(%edx),%eax
  bd:	50                   	push   %eax
  be:	8b 42 08             	mov    0x8(%edx),%eax
  c1:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			c4: R_386_32	.bss
  c8:	50                   	push   %eax
  c9:	e8 fc ff ff ff       	call   ca <_os_schedule+0x50>
			ca: R_386_PC32	_os_add_node_tail
  ce:	a1 00 01 00 00       	mov    0x100,%eax
			cf: R_386_32	.bss
  d3:	0f b6 40 08          	movzbl 0x8(%eax),%eax
  d7:	89 04 24             	mov    %eax,(%esp)
  da:	e8 fc ff ff ff       	call   db <_os_schedule+0x61>
			db: R_386_PC32	_os_set_ready
  df:	a1 00 01 00 00       	mov    0x100,%eax
			e0: R_386_32	.bss
  e4:	83 c4 10             	add    $0x10,%esp
  e7:	c6 00 01             	movb   $0x1,(%eax)
  ea:	e8 fc ff ff ff       	call   eb <_os_schedule+0x71>
			eb: R_386_PC32	_os_save_context
  ef:	85 c0                	test   %eax,%eax
  f1:	89 c2                	mov    %eax,%edx
  f3:	74 63                	je     158 <_os_schedule+0xde>
  f5:	a1 00 01 00 00       	mov    0x100,%eax
			f6: R_386_32	.bss
  fa:	89 50 04             	mov    %edx,0x4(%eax)
  fd:	e8 fc ff ff ff       	call   fe <_os_schedule+0x84>
			fe: R_386_PC32	_os_get_highest_priority
 102:	8b 04 85 00 00 00 00 	mov    0x0(,%eax,4),%eax
			105: R_386_32	.bss
 109:	8b 58 08             	mov    0x8(%eax),%ebx
 10c:	52                   	push   %edx
 10d:	52                   	push   %edx
 10e:	8d 43 30             	lea    0x30(%ebx),%eax
 111:	50                   	push   %eax
 112:	8b 43 08             	mov    0x8(%ebx),%eax
 115:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			118: R_386_32	.bss
 11c:	50                   	push   %eax
 11d:	e8 fc ff ff ff       	call   11e <_os_schedule+0xa4>
			11e: R_386_PC32	_os_remove_node
 122:	8b 43 08             	mov    0x8(%ebx),%eax
 125:	83 c4 10             	add    $0x10,%esp
 128:	83 3c 85 00 00 00 00 	cmpl   $0x0,0x0(,%eax,4)
 12f:	00 
			12b: R_386_32	.bss
 130:	75 0f                	jne    141 <_os_schedule+0xc7>
 132:	83 ec 0c             	sub    $0xc,%esp
 135:	0f b6 c0             	movzbl %al,%eax
 138:	50                   	push   %eax
 139:	e8 fc ff ff ff       	call   13a <_os_schedule+0xc0>
			13a: R_386_PC32	_os_unset_ready
 13e:	83 c4 10             	add    $0x10,%esp
 141:	c6 03 02             	movb   $0x2,(%ebx)
 144:	83 ec 0c             	sub    $0xc,%esp
 147:	ff 73 04             	pushl  0x4(%ebx)
 14a:	89 1d 00 01 00 00    	mov    %ebx,0x100
			14c: R_386_32	.bss
 150:	e8 fc ff ff ff       	call   151 <_os_schedule+0xd7>
			151: R_386_PC32	_os_restore_context
 155:	83 c4 10             	add    $0x10,%esp
 158:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 15b:	c9                   	leave  
 15c:	c3                   	ret    

0000015d <_os_wakeup_task>:
 15d:	55                   	push   %ebp
 15e:	89 e5                	mov    %esp,%ebp
 160:	53                   	push   %ebx
 161:	83 ec 14             	sub    $0x14,%esp
 164:	8b 5d 08             	mov    0x8(%ebp),%ebx
 167:	8b 43 40             	mov    0x40(%ebx),%eax
 16a:	85 c0                	test   %eax,%eax
 16c:	89 45 f8             	mov    %eax,-0x8(%ebp)
 16f:	74 12                	je     183 <_os_wakeup_task+0x26>
 171:	50                   	push   %eax
 172:	50                   	push   %eax
 173:	8d 43 30             	lea    0x30(%ebx),%eax
 176:	50                   	push   %eax
 177:	8d 45 f8             	lea    -0x8(%ebp),%eax
 17a:	50                   	push   %eax
 17b:	e8 fc ff ff ff       	call   17c <_os_wakeup_task+0x1f>
			17c: R_386_PC32	_os_remove_node
 180:	83 c4 10             	add    $0x10,%esp
 183:	50                   	push   %eax
 184:	50                   	push   %eax
 185:	8d 43 30             	lea    0x30(%ebx),%eax
 188:	50                   	push   %eax
 189:	8b 43 08             	mov    0x8(%ebx),%eax
 18c:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			18f: R_386_32	.bss
 193:	50                   	push   %eax
 194:	e8 fc ff ff ff       	call   195 <_os_wakeup_task+0x38>
			195: R_386_PC32	_os_add_node_tail
 199:	0f b6 43 08          	movzbl 0x8(%ebx),%eax
 19d:	89 04 24             	mov    %eax,(%esp)
 1a0:	e8 fc ff ff ff       	call   1a1 <_os_wakeup_task+0x44>
			1a1: R_386_PC32	_os_set_ready
 1a5:	c6 03 01             	movb   $0x1,(%ebx)
 1a8:	e8 fc ff ff ff       	call   1a9 <_os_wakeup_task+0x4c>
			1a9: R_386_PC32	_os_schedule
 1ad:	83 c4 10             	add    $0x10,%esp
 1b0:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 1b3:	c9                   	leave  
 1b4:	c3                   	ret    

000001b5 <_os_wakeup_queue>:
 1b5:	55                   	push   %ebp
 1b6:	89 e5                	mov    %esp,%ebp
 1b8:	56                   	push   %esi
 1b9:	53                   	push   %ebx
 1ba:	8b 55 08             	mov    0x8(%ebp),%edx
 1bd:	8b 02                	mov    (%edx),%eax
 1bf:	85 c0                	test   %eax,%eax
 1c1:	74 3f                	je     202 <_os_wakeup_queue+0x4d>
 1c3:	8b 58 08             	mov    0x8(%eax),%ebx
 1c6:	51                   	push   %ecx
 1c7:	51                   	push   %ecx
 1c8:	8d 73 30             	lea    0x30(%ebx),%esi
 1cb:	56                   	push   %esi
 1cc:	52                   	push   %edx
 1cd:	e8 fc ff ff ff       	call   1ce <_os_wakeup_queue+0x19>
			1ce: R_386_PC32	_os_remove_node
 1d2:	58                   	pop    %eax
 1d3:	5a                   	pop    %edx
 1d4:	56                   	push   %esi
 1d5:	8b 43 08             	mov    0x8(%ebx),%eax
 1d8:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			1db: R_386_32	.bss
 1df:	50                   	push   %eax
 1e0:	e8 fc ff ff ff       	call   1e1 <_os_wakeup_queue+0x2c>
			1e1: R_386_PC32	_os_add_node_tail
 1e5:	0f b6 43 08          	movzbl 0x8(%ebx),%eax
 1e9:	89 04 24             	mov    %eax,(%esp)
 1ec:	e8 fc ff ff ff       	call   1ed <_os_wakeup_queue+0x38>
			1ed: R_386_PC32	_os_set_ready
 1f1:	83 c4 10             	add    $0x10,%esp
 1f4:	c6 03 01             	movb   $0x1,(%ebx)
 1f7:	8d 65 f8             	lea    -0x8(%ebp),%esp
 1fa:	5b                   	pop    %ebx
 1fb:	5e                   	pop    %esi
 1fc:	5d                   	pop    %ebp
 1fd:	e9 fc ff ff ff       	jmp    1fe <_os_wakeup_queue+0x49>
			1fe: R_386_PC32	_os_schedule
 202:	8d 65 f8             	lea    -0x8(%ebp),%esp
 205:	5b                   	pop    %ebx
 206:	5e                   	pop    %esi
 207:	5d                   	pop    %ebp
 208:	c3                   	ret    

00000209 <_os_wait>:
 209:	55                   	push   %ebp
 20a:	89 e5                	mov    %esp,%ebp
 20c:	53                   	push   %ebx
 20d:	83 ec 04             	sub    $0x4,%esp
 210:	8b 5d 08             	mov    0x8(%ebp),%ebx
 213:	80 7d 0c 00          	cmpb   $0x0,0xc(%ebp)
 217:	75 13                	jne    22c <_os_wait+0x23>
 219:	50                   	push   %eax
 21a:	50                   	push   %eax
 21b:	a1 00 01 00 00       	mov    0x100,%eax
			21c: R_386_32	.bss
 220:	83 c0 30             	add    $0x30,%eax
 223:	50                   	push   %eax
 224:	53                   	push   %ebx
 225:	e8 fc ff ff ff       	call   226 <_os_wait+0x1d>
			226: R_386_PC32	_os_add_node_tail
 22a:	eb 11                	jmp    23d <_os_wait+0x34>
 22c:	50                   	push   %eax
 22d:	50                   	push   %eax
 22e:	a1 00 01 00 00       	mov    0x100,%eax
			22f: R_386_32	.bss
 233:	83 c0 30             	add    $0x30,%eax
 236:	50                   	push   %eax
 237:	53                   	push   %ebx
 238:	e8 fc ff ff ff       	call   239 <_os_wait+0x30>
			239: R_386_PC32	_os_add_node_priority
 23d:	8b 03                	mov    (%ebx),%eax
 23f:	83 c4 10             	add    $0x10,%esp
 242:	8b 15 00 01 00 00    	mov    0x100,%edx
			244: R_386_32	.bss
 248:	89 42 40             	mov    %eax,0x40(%edx)
 24b:	c6 02 03             	movb   $0x3,(%edx)
 24e:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 251:	c9                   	leave  
 252:	e9 fc ff ff ff       	jmp    253 <_os_wait+0x4a>
			253: R_386_PC32	_os_schedule

00000257 <eos_resume_task>:
 257:	55                   	push   %ebp
 258:	89 e5                	mov    %esp,%ebp
 25a:	53                   	push   %ebx
 25b:	83 ec 04             	sub    $0x4,%esp
 25e:	8b 5d 08             	mov    0x8(%ebp),%ebx
 261:	80 3b 04             	cmpb   $0x4,(%ebx)
 264:	75 2d                	jne    293 <eos_resume_task+0x3c>
 266:	50                   	push   %eax
 267:	50                   	push   %eax
 268:	8d 43 30             	lea    0x30(%ebx),%eax
 26b:	50                   	push   %eax
 26c:	8b 43 08             	mov    0x8(%ebx),%eax
 26f:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			272: R_386_32	.bss
 276:	50                   	push   %eax
 277:	e8 fc ff ff ff       	call   278 <eos_resume_task+0x21>
			278: R_386_PC32	_os_add_node_tail
 27c:	0f b6 43 08          	movzbl 0x8(%ebx),%eax
 280:	89 04 24             	mov    %eax,(%esp)
 283:	e8 fc ff ff ff       	call   284 <eos_resume_task+0x2d>
			284: R_386_PC32	_os_set_ready
 288:	c6 03 01             	movb   $0x1,(%ebx)
 28b:	e8 fc ff ff ff       	call   28c <eos_resume_task+0x35>
			28c: R_386_PC32	_os_schedule
 290:	83 c4 10             	add    $0x10,%esp
 293:	8b 5d fc             	mov    -0x4(%ebp),%ebx
 296:	31 c0                	xor    %eax,%eax
 298:	c9                   	leave  
 299:	c3                   	ret    

0000029a <eos_change_priority>:
 29a:	55                   	push   %ebp
 29b:	89 e5                	mov    %esp,%ebp
 29d:	57                   	push   %edi
 29e:	56                   	push   %esi
 29f:	53                   	push   %ebx
 2a0:	83 ec 0c             	sub    $0xc,%esp
 2a3:	8b 5d 08             	mov    0x8(%ebp),%ebx
 2a6:	8b 75 0c             	mov    0xc(%ebp),%esi
 2a9:	80 3b 01             	cmpb   $0x1,(%ebx)
 2ac:	75 55                	jne    303 <eos_change_priority+0x69>
 2ae:	50                   	push   %eax
 2af:	50                   	push   %eax
 2b0:	8d 7b 30             	lea    0x30(%ebx),%edi
 2b3:	57                   	push   %edi
 2b4:	8b 43 08             	mov    0x8(%ebx),%eax
 2b7:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			2ba: R_386_32	.bss
 2be:	50                   	push   %eax
 2bf:	e8 fc ff ff ff       	call   2c0 <eos_change_priority+0x26>
			2c0: R_386_PC32	_os_remove_node
 2c4:	8b 43 08             	mov    0x8(%ebx),%eax
 2c7:	83 c4 10             	add    $0x10,%esp
 2ca:	83 3c 85 00 00 00 00 	cmpl   $0x0,0x0(,%eax,4)
 2d1:	00 
			2cd: R_386_32	.bss
 2d2:	75 0f                	jne    2e3 <eos_change_priority+0x49>
 2d4:	83 ec 0c             	sub    $0xc,%esp
 2d7:	0f b6 c0             	movzbl %al,%eax
 2da:	50                   	push   %eax
 2db:	e8 fc ff ff ff       	call   2dc <eos_change_priority+0x42>
			2dc: R_386_PC32	_os_unset_ready
 2e0:	83 c4 10             	add    $0x10,%esp
 2e3:	50                   	push   %eax
 2e4:	50                   	push   %eax
 2e5:	57                   	push   %edi
 2e6:	8d 04 b5 00 00 00 00 	lea    0x0(,%esi,4),%eax
			2e9: R_386_32	.bss
 2ed:	50                   	push   %eax
 2ee:	e8 fc ff ff ff       	call   2ef <eos_change_priority+0x55>
			2ef: R_386_PC32	_os_add_node_tail
 2f3:	89 f2                	mov    %esi,%edx
 2f5:	0f b6 c2             	movzbl %dl,%eax
 2f8:	89 04 24             	mov    %eax,(%esp)
 2fb:	e8 fc ff ff ff       	call   2fc <eos_change_priority+0x62>
			2fc: R_386_PC32	_os_set_ready
 300:	83 c4 10             	add    $0x10,%esp
 303:	89 73 08             	mov    %esi,0x8(%ebx)
 306:	89 73 3c             	mov    %esi,0x3c(%ebx)
 309:	8d 65 f4             	lea    -0xc(%ebp),%esp
 30c:	5b                   	pop    %ebx
 30d:	5e                   	pop    %esi
 30e:	5f                   	pop    %edi
 30f:	5d                   	pop    %ebp
 310:	e9 fc ff ff ff       	jmp    311 <eos_change_priority+0x77>
			311: R_386_PC32	_os_schedule

00000315 <_os_init_task>:
 315:	55                   	push   %ebp
 316:	89 e5                	mov    %esp,%ebp
 318:	83 ec 0c             	sub    $0xc,%esp
 31b:	68 00 00 00 00       	push   $0x0
			31c: R_386_32	.rodata
 320:	68 00 00 00 00       	push   $0x0
			321: R_386_32	.rodata.str1.1
 325:	68 07 00 00 00       	push   $0x7
			326: R_386_32	.rodata.str1.1
 32a:	e8 fc ff ff ff       	call   32b <_os_init_task+0x16>
			32b: R_386_PC32	eos_printf
 32f:	c7 04 24 14 00 00 00 	movl   $0x14,(%esp)
			332: R_386_32	.rodata.str1.1
 336:	e8 fc ff ff ff       	call   337 <_os_init_task+0x22>
			337: R_386_PC32	eos_printf
 33b:	31 c0                	xor    %eax,%eax
 33d:	83 c4 10             	add    $0x10,%esp
 340:	c7 05 00 01 00 00 00 	movl   $0x0,0x100
 347:	00 00 00 
			342: R_386_32	.bss
 34a:	c7 04 85 00 00 00 00 	movl   $0x0,0x0(,%eax,4)
 351:	00 00 00 00 
			34d: R_386_32	.bss
 355:	40                   	inc    %eax
 356:	83 f8 3f             	cmp    $0x3f,%eax
 359:	75 ef                	jne    34a <_os_init_task+0x35>
 35b:	c9                   	leave  
 35c:	c3                   	ret    

0000035d <eos_set_period>:
 35d:	55                   	push   %ebp
 35e:	89 e5                	mov    %esp,%ebp
 360:	53                   	push   %ebx
 361:	83 ec 04             	sub    $0x4,%esp
 364:	8b 5d 08             	mov    0x8(%ebp),%ebx
 367:	8b 45 0c             	mov    0xc(%ebp),%eax
 36a:	89 43 0c             	mov    %eax,0xc(%ebx)
 36d:	e8 fc ff ff ff       	call   36e <eos_set_period+0x11>
			36e: R_386_PC32	eos_get_system_timer
 372:	8b 00                	mov    (%eax),%eax
 374:	89 43 10             	mov    %eax,0x10(%ebx)
 377:	58                   	pop    %eax
 378:	5b                   	pop    %ebx
 379:	5d                   	pop    %ebp
 37a:	c3                   	ret    

0000037b <eos_sleep>:
 37b:	55                   	push   %ebp
 37c:	89 e5                	mov    %esp,%ebp
 37e:	56                   	push   %esi
 37f:	53                   	push   %ebx
 380:	8b 5d 08             	mov    0x8(%ebp),%ebx
 383:	e8 fc ff ff ff       	call   384 <eos_sleep+0x9>
			384: R_386_PC32	eos_get_scheduler_lock
 388:	84 c0                	test   %al,%al
 38a:	74 21                	je     3ad <eos_sleep+0x32>
 38c:	51                   	push   %ecx
 38d:	68 0e 00 00 00       	push   $0xe
			38e: R_386_32	.rodata
 392:	68 00 00 00 00       	push   $0x0
			393: R_386_32	.rodata.str1.1
 397:	68 07 00 00 00       	push   $0x7
			398: R_386_32	.rodata.str1.1
 39c:	e8 fc ff ff ff       	call   39d <eos_sleep+0x22>
			39d: R_386_PC32	eos_printf
 3a1:	83 c4 10             	add    $0x10,%esp
 3a4:	c7 45 08 2f 00 00 00 	movl   $0x2f,0x8(%ebp)
			3a7: R_386_32	.rodata.str1.1
 3ab:	eb 42                	jmp    3ef <eos_sleep+0x74>
 3ad:	85 db                	test   %ebx,%ebx
 3af:	89 de                	mov    %ebx,%esi
 3b1:	75 56                	jne    409 <eos_sleep+0x8e>
 3b3:	a1 00 01 00 00       	mov    0x100,%eax
			3b4: R_386_32	.bss
 3b8:	8b 50 0c             	mov    0xc(%eax),%edx
 3bb:	85 d2                	test   %edx,%edx
 3bd:	74 4a                	je     409 <eos_sleep+0x8e>
 3bf:	8b 58 10             	mov    0x10(%eax),%ebx
 3c2:	01 d3                	add    %edx,%ebx
 3c4:	89 58 10             	mov    %ebx,0x10(%eax)
 3c7:	e8 fc ff ff ff       	call   3c8 <eos_sleep+0x4d>
			3c8: R_386_PC32	eos_get_system_timer
 3cc:	3b 18                	cmp    (%eax),%ebx
 3ce:	77 2a                	ja     3fa <eos_sleep+0x7f>
 3d0:	52                   	push   %edx
 3d1:	68 0e 00 00 00       	push   $0xe
			3d2: R_386_32	.rodata
 3d6:	68 00 00 00 00       	push   $0x0
			3d7: R_386_32	.rodata.str1.1
 3db:	68 07 00 00 00       	push   $0x7
			3dc: R_386_32	.rodata.str1.1
 3e0:	e8 fc ff ff ff       	call   3e1 <eos_sleep+0x66>
			3e1: R_386_PC32	eos_printf
 3e5:	83 c4 10             	add    $0x10,%esp
 3e8:	c7 45 08 52 00 00 00 	movl   $0x52,0x8(%ebp)
			3eb: R_386_32	.rodata.str1.1
 3ef:	8d 65 f8             	lea    -0x8(%ebp),%esp
 3f2:	5b                   	pop    %ebx
 3f3:	5e                   	pop    %esi
 3f4:	5d                   	pop    %ebp
 3f5:	e9 fc ff ff ff       	jmp    3f6 <eos_sleep+0x7b>
			3f6: R_386_PC32	eos_printf
 3fa:	a1 00 01 00 00       	mov    0x100,%eax
			3fb: R_386_32	.bss
 3ff:	8b 70 10             	mov    0x10(%eax),%esi
 402:	e8 fc ff ff ff       	call   403 <eos_sleep+0x88>
			403: R_386_PC32	eos_get_system_timer
 407:	2b 30                	sub    (%eax),%esi
 409:	8b 1d 00 01 00 00    	mov    0x100,%ebx
			40b: R_386_32	.bss
 40f:	e8 fc ff ff ff       	call   410 <eos_sleep+0x95>
			410: R_386_PC32	eos_get_system_timer
 414:	83 ec 0c             	sub    $0xc,%esp
 417:	53                   	push   %ebx
 418:	83 c3 14             	add    $0x14,%ebx
 41b:	68 00 00 00 00       	push   $0x0
			41c: R_386_32	_os_wakeup_task
 420:	56                   	push   %esi
 421:	53                   	push   %ebx
 422:	50                   	push   %eax
 423:	e8 fc ff ff ff       	call   424 <eos_sleep+0xa9>
			424: R_386_PC32	eos_set_alarm
 428:	a1 00 01 00 00       	mov    0x100,%eax
			429: R_386_32	.bss
 42d:	83 c4 20             	add    $0x20,%esp
 430:	c6 00 03             	movb   $0x3,(%eax)
 433:	8d 65 f8             	lea    -0x8(%ebp),%esp
 436:	5b                   	pop    %ebx
 437:	5e                   	pop    %esi
 438:	5d                   	pop    %ebp
 439:	e9 fc ff ff ff       	jmp    43a <eos_sleep+0xbf>
			43a: R_386_PC32	_os_schedule

0000043e <eos_create_task>:
 43e:	55                   	push   %ebp
 43f:	89 e5                	mov    %esp,%ebp
 441:	56                   	push   %esi
 442:	8b 75 1c             	mov    0x1c(%ebp),%esi
 445:	53                   	push   %ebx
 446:	8b 5d 08             	mov    0x8(%ebp),%ebx
 449:	50                   	push   %eax
 44a:	68 18 00 00 00       	push   $0x18
			44b: R_386_32	.rodata
 44f:	68 00 00 00 00       	push   $0x0
			450: R_386_32	.rodata.str1.1
 454:	68 07 00 00 00       	push   $0x7
			455: R_386_32	.rodata.str1.1
 459:	e8 fc ff ff ff       	call   45a <eos_create_task+0x1c>
			45a: R_386_PC32	eos_printf
 45e:	83 c4 0c             	add    $0xc,%esp
 461:	56                   	push   %esi
 462:	53                   	push   %ebx
 463:	68 7d 00 00 00       	push   $0x7d
			464: R_386_32	.rodata.str1.1
 468:	e8 fc ff ff ff       	call   469 <eos_create_task+0x2b>
			469: R_386_PC32	eos_printf
 46d:	89 73 08             	mov    %esi,0x8(%ebx)
 470:	89 73 3c             	mov    %esi,0x3c(%ebx)
 473:	c7 43 0c 00 00 00 00 	movl   $0x0,0xc(%ebx)
 47a:	c7 43 10 00 00 00 00 	movl   $0x0,0x10(%ebx)
 481:	89 5b 38             	mov    %ebx,0x38(%ebx)
 484:	ff 75 18             	pushl  0x18(%ebp)
 487:	ff 75 14             	pushl  0x14(%ebp)
 48a:	ff 75 10             	pushl  0x10(%ebp)
 48d:	ff 75 0c             	pushl  0xc(%ebp)
 490:	e8 fc ff ff ff       	call   491 <eos_create_task+0x53>
			491: R_386_PC32	_os_create_context
 495:	83 c4 18             	add    $0x18,%esp
 498:	89 43 04             	mov    %eax,0x4(%ebx)
 49b:	8d 43 30             	lea    0x30(%ebx),%eax
 49e:	50                   	push   %eax
 49f:	8b 43 08             	mov    0x8(%ebx),%eax
 4a2:	8d 04 85 00 00 00 00 	lea    0x0(,%eax,4),%eax
			4a5: R_386_32	.bss
 4a9:	50                   	push   %eax
 4aa:	e8 fc ff ff ff       	call   4ab <eos_create_task+0x6d>
			4ab: R_386_PC32	_os_add_node_tail
 4af:	0f b6 43 08          	movzbl 0x8(%ebx),%eax
 4b3:	89 04 24             	mov    %eax,(%esp)
 4b6:	e8 fc ff ff ff       	call   4b7 <eos_create_task+0x79>
			4b7: R_386_PC32	_os_set_ready
 4bb:	c6 03 01             	movb   $0x1,(%ebx)
 4be:	e8 fc ff ff ff       	call   4bf <eos_create_task+0x81>
			4bf: R_386_PC32	_os_schedule
 4c3:	8d 65 f8             	lea    -0x8(%ebp),%esp
 4c6:	31 c0                	xor    %eax,%eax
 4c8:	5b                   	pop    %ebx
 4c9:	5e                   	pop    %esi
 4ca:	5d                   	pop    %ebp
 4cb:	c3                   	ret    

Disassembly of section .bss:

00000000 <_os_ready_queue>:
	...

00000100 <_os_current_task>:
 100:	00 00                	add    %al,(%eax)
	...

Disassembly of section .rodata.str1.1:

00000000 <.rodata.str1.1>:
   0:	74 61                	je     63 <.rodata.str1.1+0x63>
   2:	73 6b                	jae    6f <.rodata.str1.1+0x6f>
   4:	2e 63 00             	arpl   %ax,%cs:(%eax)
   7:	5b                   	pop    %ebx
   8:	25 31 35 73 3a       	and    $0x3a733531,%eax
   d:	25 33 30 73 5d       	and    $0x5d733033,%eax
  12:	20 00                	and    %al,(%eax)
  14:	69 6e 69 74 69 61 6c 	imul   $0x6c616974,0x69(%esi),%ebp
  1b:	69 7a 69 6e 67 20 74 	imul   $0x7420676e,0x69(%edx),%edi
  22:	61                   	popa   
  23:	73 6b                	jae    90 <.rodata.str1.1+0x90>
  25:	20 6d 6f             	and    %ch,0x6f(%ebp)
  28:	64                   	fs
  29:	75 6c                	jne    97 <_os_schedule+0x1d>
  2b:	65 2e 0a 00          	or     %cs:%gs:(%eax),%al
  2f:	73 63                	jae    94 <.rodata.str1.1+0x94>
  31:	68 65 64 75 6c       	push   $0x6c756465
  36:	65                   	gs
  37:	72 20                	jb     59 <.rodata.str1.1+0x59>
  39:	69 73 20 6c 6f 63 6b 	imul   $0x6b636f6c,0x20(%ebx),%esi
  40:	65 64 2e 20 63 61    	and    %ah,%cs:%fs:%gs:0x61(%ebx)
  46:	6e                   	outsb  %ds:(%esi),(%dx)
  47:	27                   	daa    
  48:	74 20                	je     6a <.rodata.str1.1+0x6a>
  4a:	73 6c                	jae    b8 <_os_schedule+0x3e>
  4c:	65                   	gs
  4d:	65                   	gs
  4e:	70 2e                	jo     7e <.rodata.str1.1+0x7e>
  50:	0a 00                	or     (%eax),%al
  52:	54                   	push   %esp
  53:	68 65 72 65 20       	push   $0x20657265
  58:	65                   	gs
  59:	78 69                	js     c4 <_os_schedule+0x4a>
  5b:	73 74                	jae    d1 <_os_schedule+0x57>
  5d:	20 71 75             	and    %dh,0x75(%ecx)
  60:	65                   	gs
  61:	75 65                	jne    c8 <_os_schedule+0x4e>
  63:	64 20 6a 6f          	and    %ch,%fs:0x6f(%edx)
  67:	62 73 2c             	bound  %esi,0x2c(%ebx)
  6a:	20 73 6f             	and    %dh,0x6f(%ebx)
  6d:	20 65 78             	and    %ah,0x78(%ebp)
  70:	65 63 75 74          	arpl   %si,%gs:0x74(%ebp)
  74:	65 20 74 68 65       	and    %dh,%gs:0x65(%eax,%ebp,2)
  79:	6d                   	insl   (%dx),%es:(%edi)
  7a:	2e 0a 00             	or     %cs:(%eax),%al
  7d:	74 61                	je     e0 <_os_schedule+0x66>
  7f:	73 6b                	jae    ec <_os_schedule+0x72>
  81:	3a 20                	cmp    (%eax),%ah
  83:	30 78 25             	xor    %bh,0x25(%eax)
  86:	78 2c                	js     b4 <_os_schedule+0x3a>
  88:	20 70 72             	and    %dh,0x72(%eax)
  8b:	69 6f 72 69 74 79 3a 	imul   $0x3a797469,0x72(%edi),%ebp
  92:	20                   	.byte 0x20
  93:	25                   	.byte 0x25
  94:	64 0a 00             	or     %fs:(%eax),%al

Disassembly of section .rodata:

00000000 <__FUNCTION__.1593>:
   0:	5f                   	pop    %edi
   1:	6f                   	outsl  %ds:(%esi),(%dx)
   2:	73 5f                	jae    63 <eos_suspend_task+0x37>
   4:	69 6e 69 74 5f 74 61 	imul   $0x61745f74,0x69(%esi),%ebp
   b:	73 6b                	jae    78 <eos_suspend_task+0x4c>
	...

0000000e <__FUNCTION__.1577>:
   e:	65 6f                	outsl  %gs:(%esi),(%dx)
  10:	73 5f                	jae    71 <eos_suspend_task+0x45>
  12:	73 6c                	jae    80 <_os_schedule+0x6>
  14:	65                   	gs
  15:	65                   	gs
  16:	70 00                	jo     18 <__FUNCTION__.1498>

00000018 <__FUNCTION__.1498>:
  18:	65 6f                	outsl  %gs:(%esi),(%dx)
  1a:	73 5f                	jae    7b <_os_schedule+0x1>
  1c:	63 72 65             	arpl   %si,0x65(%edx)
  1f:	61                   	popa   
  20:	74 65                	je     87 <_os_schedule+0xd>
  22:	5f                   	pop    %edi
  23:	74 61                	je     86 <_os_schedule+0xc>
  25:	73 6b                	jae    92 <_os_schedule+0x18>
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%edi)
   3:	43                   	inc    %ebx
   4:	3a 20                	cmp    (%eax),%ah
   6:	28 47 4e             	sub    %al,0x4e(%edi)
   9:	55                   	push   %ebp
   a:	29 20                	sub    %esp,(%eax)
   c:	34 2e                	xor    $0x2e,%al
   e:	31 2e                	xor    %ebp,(%esi)
  10:	32 20                	xor    (%eax),%ah
  12:	32 30                	xor    (%eax),%dh
  14:	30 36                	xor    %dh,(%esi)
  16:	31 31                	xor    %esi,(%ecx)
  18:	31 35 20 28 70 72    	xor    %esi,0x72702820
  1e:	65                   	gs
  1f:	72 65                	jb     86 <_os_schedule+0xc>
  21:	6c                   	insb   (%dx),%es:(%edi)
  22:	65                   	gs
  23:	61                   	popa   
  24:	73 65                	jae    8b <_os_schedule+0x11>
  26:	29 20                	sub    %esp,(%eax)
  28:	28 53 55             	sub    %dl,0x55(%ebx)
  2b:	53                   	push   %ebx
  2c:	45                   	inc    %ebp
  2d:	20 4c 69 6e          	and    %cl,0x6e(%ecx,%ebp,2)
  31:	75 78                	jne    ab <_os_schedule+0x31>
  33:	29 00                	sub    %eax,(%eax)
