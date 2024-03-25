#ifndef __XEN_ATTACK_H__
#define __XEN_ATTACK_H__
 
#include <xen/lib.h>
#include <public/attack.h>

/* flags */
#define ATTACK_BYPASS_L2_UPDATE 1

extern int attack_flags; 
extern attack_t at_payload;

 

/* functions */
void print_attack_flags(void);

static inline int is_attack_address(unsigned long addr)
{
    int i;
    for (i=0; i<10; i++)
    {
        if (addr == at_payload.addrs[i])
            return i+1;
    }
    return 0;
}


#endif /* __XEN_ATTACK_H__ */
