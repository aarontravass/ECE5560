
key='BDDD9F7CF8B69B24810B0A0F02CE69549F5E94BAD865100F60698C13A5E190F24D8900' +\
    'B8E9126461110D51FA7D5C7B1E0F2DA28568D36D96BE65D9062DD2EE89'
N = int(key, 16)
e = int('010001', 16)
d = int('6D7690B4E44FA332709384C112C51E45037CEC12AD1FD71A866353B72033E3F44FE76B' +
        'CC343CB4319CCD5049AE3B52CB65102249BAF44AB834311CC908E17461', 16)

message = open('1kb.txt')
message = ''.join([s if s !='0' else '1' for s in ''.join(message.readlines()).strip()])
i=0
fin=''
while(i<len(message)):
    msg=message[i:(min(len(message),i+len(key)-30))]
    int_msg = int(msg, 16)
    plaintext_after_int = pow(pow(int_msg, d, N), e, N)
    plaintext_after = hex(plaintext_after_int)
    fin+=plaintext_after[2:]
    i+=len(key)-30
print(fin)
print(message)
print(fin==message)
#print("Data after verification:", unhexlify(bytes(plaintext_after_int)).decode('utf8'))
# print(message==unhexlify(plaintext_after[2:]).decode('utf8'))
