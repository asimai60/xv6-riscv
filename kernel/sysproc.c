#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  uint64 msg_addr;
  char exit_msg[32];

  argint(0, &n);
  argaddr(1, &msg_addr);
  int res = fetchstr(msg_addr, exit_msg, sizeof(exit_msg));

  if (msg_addr == 0) {
    exit(n, 0);  
  } else if (res < 0){
    // to solve the error of the string is too long we can add the null terminator manually
    // exit_msg[32] = '\0';
    // exit(n, exit_msg);

    exit(n, 0);  
  } else {
    exit_msg[sizeof(exit_msg) - 1] = '\0';
    exit(n, exit_msg);
  }

  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p, msg_addr;
  argaddr(0, &p);
  argaddr(1, &msg_addr);
  return wait(p, msg_addr);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_memsize(void)
{
  return myproc()->sz;
}

uint64
sys_setaffinitymask(void)
{
  int mask;
  argint(0, &mask);
  acquire(&myproc()->lock);
  myproc()->affinity_mask = mask;
  myproc()->effective_affinity_mask = mask;
  release(&myproc()->lock);
  return 0;
}