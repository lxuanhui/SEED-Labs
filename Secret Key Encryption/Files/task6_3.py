#!/usr/bin/python3

# XOR two bytearrays
def xor(first, second, third):
	return bytearray(x^y^z for x,y,z in zip(first, second,third))
	
p1 = bytearray("Yes", encoding='utf-8')
padding = 16 - len(p1) % 16
p1.extend([padding]*padding)
IV = "fdecac907d7622b1d660de98c3fc0ef0"
IV = bytearray.fromhex(IV)
IV_next = "6f0c52be7d7622b1d660de98c3fc0ef0"
IV_next = bytearray.fromhex(IV_next)

p2 = xor(p1,IV,IV_next)
print(p2.decode('utf-8'))

