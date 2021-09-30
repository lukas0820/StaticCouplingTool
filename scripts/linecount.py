import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument("count", help="number of nodes that the result graph should have ", type=int)
parser.add_argument("input", help="input JSON file", type=str)

args = parser.parse_args()

allFiles = os.walk(args.input)
cfiles = dict()
filecount = 0
for root, dirs, files in os.walk(args.input):
    for i in files:
        if i.endswith(".c") or i.endswith(".h") or i.endswith(".cpp") or i.endswith(".hpp"):
            filecount = filecount + 1
            linecount = sum(1 for line in open(os.path.join(root,i)))
            name = i.split(".")[0]
            cfiles[name] = linecount if name not in cfiles else cfiles[name] + linecount


filesWithMostLines = sorted(cfiles.items(), key=lambda item: item[1], reverse=True)[:args.count]

    
for i in filesWithMostLines:
    print(i[0] + " : " + str(i[1]))
print(filecount)








   


