
; sim isto é um teste
add 0,0
def: teste
    NOP
    ADD 0x00 0x01 ; sim isto é um teste
    JMP teste
finish

add 0x00 0x01

NOP 0x00 0x00
ADD 0x00 0x00

end