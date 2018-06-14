tFile = open('fill_data.bin', 'wb')
for ucData in range(0x000, 0x100):
    tFile.write(chr(ucData))
tFile.close()

tFile = open('fill_data2.bin', 'wb')
for ucData in range(255, -1, -1):
    tFile.write(chr(ucData))
tFile.close()
