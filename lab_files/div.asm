.def R16 = num
.def R17 = den
.def R18 = quo
.def R19 = rem

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
