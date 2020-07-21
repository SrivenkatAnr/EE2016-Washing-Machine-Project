.def count = R16
.def val = R17
.def ans = R19
.def car = R18
ldi car, 0x00

ldi ZL, LOW(NUM<<1)
ldi ZH, HIGH(NUM<<1)

lpm count,Z
inc ZL
lpm ans, Z   

dec count
loop : inc ZL
lpm val,Z
add ans, val
BRCC nocar
inc car
nocar:
dec count
BRNE loop

sts 0x60,ans
sts 0x61,car

nop
NUM: .db 0x04,0x04,0x03,0xff,0x01,0x01
