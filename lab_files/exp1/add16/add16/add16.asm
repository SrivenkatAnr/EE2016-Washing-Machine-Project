.def a0 = R16
.def a1 = R18
.def b0 = R17
.def b1 = R19
.def c = R20

ldi ZL,LOW(NUM<<1)
ldi ZH,HIGH(NUM<<1)
lpm a0, Z+
lpm a1, Z

ldi ZL,LOW(NUM1<<1)
ldi ZH,HIGH(NUM1<<1)
lpm b0, Z+
lpm b1, Z

add b0,a0
adc b1,a1

ldi c, 0x00
BRCC nocar
ldi c, 0x01
nocar:
sts 0x60,b0
sts 0x61,b1
sts 0x62,c

nop

NUM: .db 0xd3,0x5f
NUM1: .db 0xab,0xcd
