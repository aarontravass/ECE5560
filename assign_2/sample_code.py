#!/usr/bin/python3

# XOR two bytearrays
def xor(first, second):
   return bytearray(x^y for x,y in zip(first, second))

MSG   = "This"
HEX_1 = "3f1b9dc0dbfad2965173f1e4581a6b86"
HEX_2 = "7c7f7cdd948fe6c617d87ef674f0f51e"

# Convert ascii string to bytearray
D1 = bytes(MSG, 'utf-8')

# Convert hex string to bytearray
D2 = bytearray.fromhex(HEX_1)
D3 = bytearray.fromhex(HEX_2)

r1 = xor(D1, D2)
r2 = xor(r1, D3)

print(r1.hex())
print(r2.hex())

