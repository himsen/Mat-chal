#!/usr/bin/python

import binascii

def h2i(h):
	if (ord("0") <= ord(h)) and (ord(h) <= ord("9")):
		return ord(h) - ord("0")
	elif (ord("A") <= ord(h)) and (ord(h) <= ord("F")):
		return ord(h) - ord("A") + 10
	else:
		return ord(h) - ord("a") + 10

def h2b(hexa):
	byte = bytearray()
	i = 0

	while i < len(hexa) - 1:
		b1 = h2i(hexa[i])
		i += 1
		b2 = h2i(hexa[i])
		i += 1
		byte.append(b1*16 + b2)

	return byte

def xor(x, y):
	res = bytearray()
	for i in range(len(x)):
		res.append(x[i]^y[i])

	return res

def hex_xor(hexa_x, hexa_y):
	return xor(h2b(hexa_x), h2b(hexa_y))

def b2h(bina):
	print binascii.hexlify(bytearray(bina))

if __name__ == '__main__':
	print(b2h(hex_xor("1c0111001f010100061a024b53535009181c","686974207468652062756c6c277320657965")))