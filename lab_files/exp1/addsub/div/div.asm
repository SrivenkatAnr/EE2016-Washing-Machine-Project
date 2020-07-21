.def num = R16
.def den = R17
.def quo = R18
.def rem = R19

ldi num,0xD3
ldi den,0x5F
sts 0x60,num
sts 0x61,den

div : inc quo
	  sub num,den
	  brne div

inc quo
add num,den
mov rem,num

sts 0x62,quo
sts 0x63,rem

nop
