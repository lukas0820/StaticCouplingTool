import json
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("count", help="number of nodes that the result graph should have ", type=int)
parser.add_argument("input", help="input JSON file", type=argparse.FileType('r'))

args = parser.parse_args()

jsonObject = json.load(args.input)

edges = jsonObject["edges"]
nodes = jsonObject["nodes"]

def get_node_name_from_id(nodeId):
    return [node["label"] for node in jsonObject['nodes'] if nodeId == node["id"]][0]

couplingCountMap = {}
for currentEdge in edges:
    start = currentEdge["start"]
    end = currentEdge["end"]
    weight = currentEdge["weight"]
    couplingCountMap[start] = weight if start not in couplingCountMap else couplingCountMap[start] + weight
    couplingCountMap[end] = weight if end not in couplingCountMap else couplingCountMap[end] + weight
nodesWithHighestCoupling = sorted(couplingCountMap.items(), key=lambda item: item[1], reverse=True)[:args.count]

for node in nodesWithHighestCoupling:
    print(get_node_name_from_id(node[0]) +  ":" + str(node[1]))






   


