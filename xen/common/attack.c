#include <xen/attack.h>

int attack_flags = 0;
attack_t at_payload = {0, 0, {0,0,0,0,0,0,0,0,0,0}};

void print_attack_flags()
{   
    printk("attack_flags\t%d\n",attack_flags);
    printk("ATTACK_BYPASS_L2_UPDATE\t%d\n", attack_flags & ATTACK_BYPASS_L2_UPDATE);
}
