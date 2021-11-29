import time
import binascii
from Crypto.Util import number

def intfunc(text):
	t = int(text, 16)
	return t
	
def randprime(val):
	prime = number.getPrime(val)
	return prime
	

def sizefunc(val):
	x = pow(2,val)
	return 256 * x


def strintfunc(text):
	y = text.encode('utf8')
	t = int(binascii.hexlify(bytes(y)), 16)
	return t
	
def signing_algorithm(K): 
	t0 = time.process_time()
	encrypted = hex(pow(K[0], K[1], K[2]))
	t1 = time.process_time()
	duration = t1 - t0
	if(K[3] == 5):
		print ("It took", duration, "seconds to sign the text. The key size was ", K[3], "bits.")
	elif(K[3] != 0):
		print ("It took", duration, "seconds to sign a file of size ", K[3], "kilobytes.")
	return encrypted[2:]

def verifying_algorithm(K): 
	data = pow(K[0], K[2], K[3])
	deciphered = hex(pow(data, K[1], K[3]))
	return binascii.unhexlify(deciphered[2:]).decode('utf8')
