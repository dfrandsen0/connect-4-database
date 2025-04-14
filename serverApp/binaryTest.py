

given = ['0', '1', '1', '1', '0', '1', '0', '1']
result = 0

for bit in given:
    result <<= 1
    if bit == '1':
        result |= 1

byte_value = result.to_bytes(1)#, byteorder="big")

for i in range(8):
    bit = str((byte_value[0] >> (7 - i)) & 1)
    print(bit)
