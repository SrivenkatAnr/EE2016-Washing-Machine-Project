ldi ZL,LOW(NUM<<1)
ldi ZH,HIGH(NUM<<1)

lpm R16,Z+
lpm R17,Z
ldi R18,0x00
mov R19,R17
dec R16
mult : add R17,R19
BRCC adca
inc R18
adca : dec R16
BRNE mult 
sts 0x60,R17
sts 0x61,R18

nop
NUM: .db 0x5f,0xd3
