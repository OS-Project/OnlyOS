.global set_vectorBaseAddr

set_vectorBaseAddr:
    MCR     p15, #0, r0, c12, c0, #0
    DSB
    BX      lr
