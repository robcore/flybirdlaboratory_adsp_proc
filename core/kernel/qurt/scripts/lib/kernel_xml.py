from ezxml import Element, str_attr, size_attr, long_attr
import re

'''    XML tag             AttrType   Req/Opt       C template regex       Default value (or None)    '''
kernel_db = [
    ["hthread_mask",       str_attr,  "required", "HTHREADMASK",           None   ],
    ["heap_size",          size_attr, "optional", "KERNELHEAPSIZE",        0x1C000],
    ["heap_size_island",   size_attr, "optional", "KERNELHEAPSIZEISLAND",  0      ],
    ["heap_section_island",str_attr,  "optional", "ISLANDHEAPSECTION",     ".data.island"], 
    ["tlb_debug_level",    long_attr, "optional", "TLBDEBUGLEVEL",         0      ],
    ["dynamic_tlb_reservation",
                           long_attr, "optional", "DYNAMICTLBRESERVE",     -1     ],
    ["kernel_separation",  long_attr, "optional", "KERNELSEP",             0      ],
    ["split_virtual_pool", long_attr, "optional", "SPLITVIRTPOOL",         0      ],
    ["max_user_processes", long_attr, "optional", "MAXUSERPROCESSES",      8      ],
    ["max_threads",        str_attr,  "required", "MAXTHREADS",            None   ],
    ["max_threads_in_tcm", str_attr,  "optional", "MAXTHREADSINTCM",       "0"    ],
    ["tcm_utcb_from_stack",long_attr, "optional", "TCMUTCBFROMSTACK",      -1     ],
    ["max_futexes",        str_attr,  "required", "MAXFUTEXES",            None   ],
    ["qurtos_qdi_handles", str_attr,  "optional", "QURTOSQDIHANDLES",      "1024" ],
    ["trace_mask",         str_attr,  "required", "QURTKDEFAULTTRACEMASK", None   ],
    ["trace_size",         size_attr, "required", "TRACESIZE",             None   ],
    ["fastint_stack_size", size_attr, "optional", "FASTINTSTACKSIZE",      384    ],
    ["int_nest_allow_mask",size_attr, "optional", "L1NESTALLOW",           0      ],
    ["qurtos_stack_size",  size_attr, "optional", "QURTOSSTACKSIZE",       0      ],
    ["qurtos_island_stack_size",
                           size_attr, "optional", "QURTOSISLANDSTACKSIZE", 0      ],
    ["tcm_size",           size_attr, "optional", "TCMSIZE",               32     ],
    ["tcm_save_size",      size_attr, "optional", "TCMSAVESIZE",           0      ],
    ["page_table_size",    size_attr, "optional", "PAGETABLESIZE",         0x24000],
    ["debug_buf_size",     size_attr, "optional", "DEBUGBUFSIZE",          8192   ]
]

#   user_processes      user_threads
object_cache_keys = '''
    memory_blocks
    virt_regions        phys_regions
    qurtos_threads      shmem_regions
'''

def object_cache_el():
    T = (long_attr, "optional")
    L = [(e,T) for e in object_cache_keys.split()]
    D = dict((k,v) for (k,v) in L)
    return Element("object_cache", **D)

def object_cache_initializer(elems):
    L = [(e,'OBJCACHE_DEFAULT') for e in object_cache_keys.split()]
    D = dict((k,v) for (k,v) in L)
    for E in elems:
        D.update(E.__dict__)
    L = [".%s = %s" % (e,str(D[e])) for e in object_cache_keys.split()]
    S = ', \\\n   '.join(L)
    return S

# FIXME: support "fastint_stack size= " until cust_config.xml can move to "fastint_stack_size value= " 
Fastint_stack_el = Element("fastint_stack",
                      size = (str_attr,"optional"))
Kernel_el = Element("kernel", object_cache_el(), Fastint_stack_el, *[Element(e[0], value=(e[1],e[2])) for e in kernel_db]) 

def kernel_hook(cfg, name, value):
    if name == 'max_user_processes':
        if value > 0:
            # If max_user_processes is positive,
            #  add initialization functions to pull
            #  in user process support
            cfg.add_init_func('qurtos_user_client_init')

''' Collect the attributes of the kernel element '''

def collect_kernel_element(cfg):
    k = cfg.find_child("kernel")
    if not k:
        return
    for e in kernel_db:
        try:
            v = k.find_child(e[0]).value
        except AttributeError:
            v = e[4]
            if v == None:
                print('Cannot parse kernel attribute ' + e[0])
                raise
        kernel_hook(cfg, e[0], v)
        if e[1] == size_attr or e[1] == long_attr:
            v = ('%#X' % v)
        cfg[e[3]] = v

    # FIXME: support "fastint_stack size= " until cust_config.xml can move to "fastint_stack_size value= " 
    try:
        cfg['FASTINTSTACKSIZE'] = k.find_child("fastint_stack").size
    except AttributeError:
        pass
    cfg['OBJCACHECONFIG'] = object_cache_initializer(k.find_children('object_cache'))
