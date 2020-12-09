import mmap
import os
while True:
    file_nameu = input()
    with open(file_nameu, "r+b") as f:
        mm = mmap.mmap(f.fileno(), 0)
        print(mm.read())  # prints the file
        b = input()
        mm.seek(0)
        print(mm.read())
