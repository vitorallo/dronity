#pragma once

#define PAGE_OFFSET		0xC0000000
/*
 * Alternative possibilities for PAGE_OFFSET:
 * default 0x40000000 if VMSPLIT_1G
 * default 0x80000000 if VMSPLIT_2G
 */
#define TASK_SIZE		(PAGE_OFFSET - 0x01000000)
#define MODULE_ADDR		(PAGE_OFFSET - 0x00800000)
#define KERNEL_ADDR		(PAGE_OFFSET + 0x00008000)

#define PAGE_SHIFT		12

#define PTE_FILE_MAX_BITS	29

#define SYSCALLS syscalls_arm

//this is the wordsize here arm supposed to be ONLY 32bit and not 64... hope...
#define __WORDSIZE 32

//this is epoll out of the competition :P
#define EPOLL_CLOEXEC 02000000


//this is to fix the missing support for cpu_set_t, if you end up using this, you probably don't support AFFINITY too, remember
//to comment out #define AFFINITY_SUPPORT 1 in the config.h

#define CPU_SETSIZE 1024
#define __NCPUBITS  (8 * sizeof (unsigned long))
typedef struct
{
   unsigned long __bits[CPU_SETSIZE / __NCPUBITS];
} cpu_set_t;

#define CPU_SET(cpu, cpusetp) \
  ((cpusetp)->__bits[(cpu)/__NCPUBITS] |= (1UL << ((cpu) % __NCPUBITS)))
#define CPU_ZERO(cpusetp) \
  memset((cpusetp), 0, sizeof(cpu_set_t))
