import time
key='BDDD9F7CF8B69B24810B0A0F02CE69549F5E94BAD865100F60698C13A5E190F24D8900' +\
    'B8E9126461110D51FA7D5C7B1E0F2DA28568D36D96BE65D9062DD2EE89'
N = int(key, 16)
e = int('010001', 16)
d = int('6D7690B4E44FA332709384C112C51E45037CEC12AD1FD71A866353B72033E3F44FE76B' +
        'CC343CB4319CCD5049AE3B52CB65102249BAF44AB834311CC908E17461', 16)
import os
os.system('openssl rand -hex 1000 > 1kb.txt')
os.system('openssl rand -hex 1000000 > 1mb.txt')
os.system('openssl rand -hex 100000 > 100kb.txt')
os.system('openssl rand -hex 10000000 > 10mb.txt')
message = open('1kb.txt')
message = ''.join(message.readlines()).strip()
i=0
fin=''
print("Signing 1k file")
t0 = time.process_time()
while(i<len(message)):
    msg=message[i:(min(len(message),i+len(key)-100))]
    should_add_zero= True if msg[0]=='0' else False
    int_msg = int(msg, 16)
    cipher_int = pow(int_msg, d, N)
    ciphertext = hex(cipher_int)
    i+=100
t1 = time.process_time()
print("Time taken:",t1-t0,"s" )
#----------------------------------------------------------------------------------
message = open('100kb.txt')
message = ''.join(message.readlines()).strip()
i=0
fin=''
print("Signing 100k file")
t0 = time.process_time()
while(i<len(message)):
    msg=message[i:(min(len(message),i+len(key)-100))]
    should_add_zero= True if msg[0]=='0' else False
    int_msg = int(msg, 16)
    cipher_int = pow(int_msg, d, N)
    ciphertext = hex(cipher_int)
    i += 100
t1 = time.process_time()
print("Time taken:",t1-t0,"s" )

#----------------------------------------------------------------------------------
message = open('1mb.txt')
message = ''.join(message.readlines()).strip()
i=0
fin=''
print("Signing 1mb file")
t0 = time.process_time()
while(i<len(message)):
    msg=message[i:(min(len(message),i+len(key)-100))]
    should_add_zero= True if msg[0]=='0' else False
    int_msg = int(msg, 16)
    cipher_int = pow(int_msg, d, N)
    ciphertext = hex(cipher_int)
    i += 100
t1 = time.process_time()
print("Time taken:",t1-t0,"s" )

#----------------------------------------------------------------------------------
message = open('10mb.txt')
message = ''.join(message.readlines()).strip()
i=0
fin=''
print("Signing 10mb file")
t0 = time.process_time()
while(i<len(message)):
    msg=message[i:(min(len(message),i+len(key)-100))]
    should_add_zero= True if msg[0]=='0' else False
    int_msg = int(msg, 16)
    cipher_int = pow(int_msg, d, N)
    ciphertext = hex(cipher_int)
    i += 100
t1 = time.process_time()
print("Time taken:",t1-t0,"s" )

