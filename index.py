from sys import argv
import shutil
import os

global filen
global edir

# 🛠 - CPP TemGen◞ Beta Fast Templates Generator ◟ 

filen = argv[1]
edir = argv[2]

class Index:
    def __init__(self):
        try:
            self.unzip()
        except:
            print('[ Error ] > Failed Process.')

    def unzip(self):
        shutil.unpack_archive(filen, edir)
        print('[ Success ] > Hecho.')
        print('[ In Progress ] > Removing File...')
        os.remove(filen)
        print('[ Success ] > Remove File.')

if __name__ == "__main__":
    Index()