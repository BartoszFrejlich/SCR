import mmap as memory_senpai
import os

while True:
    file_nameu = input()
    with open(file_nameu, "r+b") as f:
        memory_chan = memory_senpai.mmap(f.fileno(), 0)
        print(memory_chan.read())  # prints the file
        b = input()
        memory_chan.seek(0)
        print(memory_chan.read())