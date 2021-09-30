import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument("input", help="input JSON file", type=str)
parser.add_argument("name", help="input JSON file", type=str)

args = parser.parse_args()

allFiles = os.walk(args.input)
cfiles = dict()

for root, dirs, files in os.walk(args.input):
    for i in files:
        if i.endswith(".c") or i.endswith(".h") or i.endswith(".cpp") or i.endswith(".hpp"):
            linecount = sum(1 for line in open(os.path.join(root,i)))
            name = i.split(".")[0]
            cfiles[name] = linecount if name not in cfiles else cfiles[name] + linecount


filesWithMostLines = sorted(cfiles.items(), key=lambda item: item[1], reverse=True)
currentRank = 1


for i in filesWithMostLines:
    if i[0] == args.name:
        print(currentRank)
        print(i[1])
    currentRank = currentRank + 1








   


