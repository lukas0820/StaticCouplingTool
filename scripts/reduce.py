import json
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("count", help="number of nodes that the result graph should have ", type=int)
parser.add_argument("input", help="input JSON file", type=argparse.FileType('r'))
parser.add_argument("output", help="output JSON file", type=argparse.FileType('w'))
args = parser.parse_args()

jsonObject = json.load(args.input)

edges = jsonObject["edges"]
nodes = jsonObject["nodes"]

couplingCountMap = {}
for currentEdge in edges:
    start = currentEdge["start"]
    end = currentEdge["end"]
    weight = currentEdge["weight"]
    couplingCountMap[start] = weight if start not in couplingCountMap else couplingCountMap[start] + weight
    couplingCountMap[end] = weight if end not in couplingCountMap else couplingCountMap[end] + weight
nodesWithHighestCoupling = dict(sorted(couplingCountMap.items(), key=lambda item: item[1], reverse=True)[:args.count]).keys()


newEdges = []
for currentEdge in edges:
    start = currentEdge["start"]
    end = currentEdge["end"]
    if start in nodesWithHighestCoupling and end in nodesWithHighestCoupling:
        newEdges.append(currentEdge)

newNodes = []
for currentNode in nodes:
    nodeId = currentNode["id"]
    if nodeId in nodesWithHighestCoupling:
        newNodes.append(currentNode)

newJsonObject = {}
newJsonObject["edges"] = newEdges
newJsonObject["nodes"] = newNodes

json.dump(newJsonObject, args.output)



   


