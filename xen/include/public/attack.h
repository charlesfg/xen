#ifndef __XEN_PUBLIC_ATTACK_H__
#define __XEN_PUBLIC_ATTACK_H__

/* Variables related to the attack */
#define ATTACK_SET_BYPASS_L2_UPDATE 1
#define ATTACK_UNSET_BYPASS_L2_UPDATE 2

struct attack_data {
    unsigned int debug; /* Enable debug messages */
    unsigned long addr; /* address to internal reference */
    unsigned long addrs[10];
};

typedef struct attack_data attack_t;

#endif /* __XEN_PUBLIC_ATTACK_H__ */
