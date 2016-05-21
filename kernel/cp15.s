.global CP15VectorBaseAddrSet

CP15VectorBaseAddrSet:
    MCR     p15, #0, r0, c12, c0, #0
    DSB
    BX      lr