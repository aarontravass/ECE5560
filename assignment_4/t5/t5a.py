from binascii import hexlify, unhexlify

N = int('BDDD9F7CF8B69B24810B0A0F02CE69549F5E94BAD865100F60698C13A5E190F24D8900' +
        'B8E9126461110D51FA7D5C7B1E0F2DA28568D36D96BE65D9062DD2EE89', 16)
e = int('010001', 16)
d = int('6D7690B4E44FA332709384C112C51E45037CEC12AD1FD71A866353B72033E3F44FE76B' +
        'CC343CB4319CCD5049AE3B52CB65102249BAF44AB834311CC908E17461', 16)

message = "This is a contact for $20,000"
given_ciphertext = '4560BE3C1E1D9A42B6784C7F06CBB6908D2A56017BB02794B06F322E7D339395' + \
                   '2C03B3FB310084C59C30CD33350188662E8090364AD5E57A8149E2D795393A30'
int_msg = int(hexlify(bytes(message.encode('ascii'))), 16)
int_cipher = pow(int_msg, d, N)
ciphertext = hex(int_cipher)
print("Signed value is ", ciphertext[2:])
print(ciphertext[2:].upper() == given_ciphertext)
plaintext_after_int = pow(int_cipher, e, N)
plaintext_after = hex(plaintext_after_int)
print("Data after verification:", unhexlify(plaintext_after[2:]).decode('utf8'))
print(message == unhexlify(plaintext_after[2:]).decode('utf8'))
