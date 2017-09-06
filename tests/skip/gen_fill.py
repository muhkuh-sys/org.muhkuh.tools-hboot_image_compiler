tFile = open('fill_data.bin', 'wb')
for ucData in range(0x000, 0x100):
    tFile.write(chr(ucData))
tFile.close()
