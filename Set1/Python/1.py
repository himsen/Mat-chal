#!/usr/bin/python

# https://tools.ietf.org/html/rfc4648#section-4

charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

def h2i(h):
	if (ord("0") <= ord(h)) and (ord(h) <= ord("9")):
		return ord(h) - ord("0")
	elif (ord("A") <= ord(h)) and (ord(h) <= ord("F")):
		return ord(h) - ord("A") + 10
	else:
		return ord(h) - ord("a") + 10

def hex2bin(hexa):
	res = bytearray()
	i = 0

	while i < len(hexa):
		b1 = h2i(hexa[i])
		i += 1
		b2 = h2i(hexa[i])
		i += 1
		val = b1*16 + b2
		res.append(val)

	return res

def bin2b64(binary):
	strlen = len(binary)
	i = 0
	res = []
	
	while i < strlen:

		b1 = 0 if i > (strlen - 1) else binary[i]
		i += 1
		b2 = 0 if i > (strlen - 1) else binary[i]
		i += 1
		b3 = 0 if i > (strlen - 1) else binary[i]
		i += 1

		# 3 bytes 
		b = (b1 << 0x10) + (b2 << 0x08) + b3

		res.append( charset[ (b >> 18) ] )
		res.append( charset[ (b >> 12) & 0x3F ] )
		res.append( charset[ (b >> 6) & 0x3F ] )
		res.append( charset[ b & 0x3F ] )

		if i - 1 > (strlen - 1):
			res[len(res) - 1] = "="
			if i - 2 > (strlen - 1):
				res[len(res) - 2] = "="

	print(res)	

def hex2b64(hexa):
	bin2b64(hex2bin(hexa))

if __name__ == '__main__':
	hex2b64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")
	print("FF")
	print(b'FF')
	#b64encode("492")