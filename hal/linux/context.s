
context.o:     file format elf32-i386
context.o
architecture: i386, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x00000000

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000004e  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000084  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000084  2**2
                  ALLOC
  3 .comment      00000035  00000000  00000000  00000084  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  00000000  00000000  000000b9  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
00000000 l    df *ABS*	00000000 context.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss	00000000 .bss
0000004a l       .text	00000000 resume_point
00000000 l    d  .note.GNU-stack	00000000 .note.GNU-stack
00000000 l    d  .comment	00000000 .comment
00000000 g     F .text	00000005 print_context
00000005 g     F .text	00000021 _os_create_context
00000026 g     F .text	0000000b _os_restore_context
00000031 g     F .text	0000001d _os_save_context
00000001       O *COM*	00000001 _os_ready_group
00000008       O *COM*	00000001 _os_ready_table
00000001       O *COM*	00000001 _os_scheduler_lock



Disassembly of section .text:

00000000 <print_context>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	5d                   	pop    %ebp
   4:	c3                   	ret    

00000005 <_os_create_context>:
   5:	55                   	push   %ebp
   6:	89 e5                	mov    %esp,%ebp
   8:	8b 45 0c             	mov    0xc(%ebp),%eax
   b:	8b 55 14             	mov    0x14(%ebp),%edx
   e:	03 45 08             	add    0x8(%ebp),%eax
  11:	89 50 fc             	mov    %edx,-0x4(%eax)
  14:	8b 55 10             	mov    0x10(%ebp),%edx
  17:	c7 40 f8 00 00 00 00 	movl   $0x0,-0x8(%eax)
  1e:	83 e8 30             	sub    $0x30,%eax
  21:	89 50 24             	mov    %edx,0x24(%eax)
  24:	5d                   	pop    %ebp
  25:	c3                   	ret    

00000026 <_os_restore_context>:
  26:	55                   	push   %ebp
  27:	89 e5                	mov    %esp,%ebp
  29:	8b 65 08             	mov    0x8(%ebp),%esp
  2c:	61                   	popa   
  2d:	9d                   	popf   
  2e:	c3                   	ret    
  2f:	5d                   	pop    %ebp
  30:	c3                   	ret    

00000031 <_os_save_context>:
  31:	55                   	push   %ebp
  32:	89 e5                	mov    %esp,%ebp
  34:	b8 00 00 00 00       	mov    $0x0,%eax
  39:	68 4a 00 00 00       	push   $0x4a
			3a: R_386_32	.text
  3e:	9c                   	pushf  
  3f:	60                   	pusha  
  40:	89 e0                	mov    %esp,%eax
  42:	ff 75 04             	pushl  0x4(%ebp)
  45:	ff 75 00             	pushl  0x0(%ebp)
  48:	89 e5                	mov    %esp,%ebp

0000004a <resume_point>:
  4a:	c9                   	leave  
  4b:	c3                   	ret    
  4c:	5d                   	pop    %ebp
  4d:	c3                   	ret    

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
  1f:	72 65                	jb     86 <resume_point+0x3c>
  21:	6c                   	insb   (%dx),%es:(%edi)
  22:	65                   	gs
  23:	61                   	popa   
  24:	73 65                	jae    8b <resume_point+0x41>
  26:	29 20                	sub    %esp,(%eax)
  28:	28 53 55             	sub    %dl,0x55(%ebx)
  2b:	53                   	push   %ebx
  2c:	45                   	inc    %ebp
  2d:	20 4c 69 6e          	and    %cl,0x6e(%ecx,%ebp,2)
  31:	75 78                	jne    ab <resume_point+0x61>
  33:	29 00                	sub    %eax,(%eax)
