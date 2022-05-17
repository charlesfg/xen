#include <xen/effector.h>
#include <xen/compiler.h>
#include <xen/hypercall.h>
#include <xen/nospec.h>
#include <xen/trace.h>
#include <xen/guest_access.h>

 
#define LOG(_m,_a...) \
        printk("%s:%d- " _m "\n",__FILE__,__LINE__, ## _a); 

#define logvar(_v,_f,_a...) \
        printk(#_v "\t" _f "\n",_v);

long do_arbitrary_va(XEN_GUEST_HANDLE_PARAM(void) addr, int unmap){

    arbitrary_va_t addr_arg; 
    mfn_t mfn;
    void *va_dst_maddr;
    unsigned long  d;


 

    if ( !guest_handle_is_null(addr) ) 
    {
        if ( copy_from_guest(&addr_arg, addr, 1) )
        {
            printk("Bad Address on 'addr' on arbitrary_va hypercall\n");
            return -EFAULT;
        }
    } 
    else 
    { 
        printk("Addresses parameters should not be null\n");
        return -EINVAL;
    }

    LOG("'%sapping address %p'!", unmap ? "Unm " : "M", (void *) addr_arg.target_addr); 


    if (unmap) {
        unmap_domain_page((const void *)addr_arg.va_mapped_addr);
        return 0;
    }

    mfn = maddr_to_mfn(addr_arg.target_addr);
    logvar(mfn_x(mfn),"%"PRI_mfn" (maddr_to_mfn)");
    va_dst_maddr = map_domain_page_global(mfn);
    show_page_walk((unsigned long) va_dst_maddr);

    // this is to get the page offset
    d = (unsigned long ) va_dst_maddr + (addr_arg.target_addr & 0xfff);
    addr_arg.va_mapped_addr = d;
    LOG("va address is: %p", (void *) d);

    if ( unlikely(!guest_handle_is_null(addr)) )
    {
        copy_to_guest(addr, &addr_arg, 1);
    }
    else
    {
        LOG("guest handle null on copying to guest");
        return -ENODATA;
    }

    return 0;
}


int do_arbitrary_access(unsigned long dst_maddr,  void *buff, size_t n, int action)
{
    mfn_t mfn;
    void *va_dst_maddr, *d;
    unsigned long rb ; // returned bytes that was not copied 
    int rc = 0;
    bool linear = action & 0x2;
    bool verbose  = action & ARBITRARY_VERBOSE;

    if (verbose)
        LOG("Address mode is '%s'!", linear ? "Linear" : "Physical"); 

    action &= 0x1;

    if (!linear){
        mfn = maddr_to_mfn(dst_maddr);
        if (verbose)
            logvar(mfn_x(mfn),"%"PRI_mfn" (maddr_to_mfn)");
        va_dst_maddr = map_domain_page(mfn);
        //va_dst_maddr = map_domain_page_global(mfn);
        d =  va_dst_maddr + (dst_maddr & 0xfff);
        if (verbose)
            show_page_walk((unsigned long) va_dst_maddr);
    }
    else 
    {
        d = (void *) dst_maddr;
        if (verbose)
            show_page_walk((unsigned long) d);
    }



    if (verbose){
        LOG("Actiong is '%s'!", action ? "WRITE" : "READ"); 
        LOG("%ld bytes (buff) %p %s (dst_maddr) %lx",n, buff, action ? "to" : "from", dst_maddr);
        logvar(d,"%p ");
    }

    if (action == ARBITRARY_READ)
    {
        rb = __copy_to_user(buff, d, n);
        if (rb)
        {
            LOG("Residual bytes to copy to user:  %ld bytes", rb);
            rb = __copy_to_user(buff+(n-rb), d+(n-rb), rb);
            if (rb) {
                LOG("Could not copy %ld bytes", rb);
                rc = EFAULT;
                goto out;
            }

        }
          
    } 
    else if (action == ARBITRARY_WRITE )
    {
        //stac();
        //memcpy(d,src,n);
        //clac();
        rb = __copy_from_user(d, buff, n);
        if (rb)
        {
            LOG("Residual bytes to copy from user:  %ld bytes", rb);
            rb = __copy_from_user(d+(n-rb), buff+(n-rb), n);
            if (rb) {
                LOG("Could not copy %ld bytes", rb);
                rc = EFAULT;
                goto out;
            }
        }
        LOG("Done!"); 
    }
    else
    {
        LOG("ACTION %d NOT IMPLEMENTED",action);
        rc =  -EINVAL;
    }
out:

    if (!linear)
        unmap_domain_page(d);
    //unmap_domain_page_global(d);

    return rc;
}
