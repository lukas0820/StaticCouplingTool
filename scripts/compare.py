import json
import argparse
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument("input1", help="input JSON file 1", type=argparse.FileType('r'))
parser.add_argument("input2", help="input JSON file 2", type=argparse.FileType('r'))

args = parser.parse_args()
nodeCount = 0
jsonObject1 = json.load(args.input1)
jsonObject2 = json.load(args.input2)


def list1(c):
    

    global jsonObject1
    edges = jsonObject1["edges"]
    nodes = jsonObject1["nodes"]

    def get_node_name_from_id(nodeId):
        pathList = [node["id"] for node in jsonObject1['nodes'] if nodeId == node["id"]][0].split(".")[0].split("/")
        return pathList[len(pathList) - 1]
    couplingCountMap = {}
    for currentEdge in edges:
        start = get_node_name_from_id(currentEdge["start"])
        end = get_node_name_from_id(currentEdge["end"])
        weight = int(currentEdge["weight"])
        couplingCountMap[start] = weight if start not in couplingCountMap else couplingCountMap[start] + weight
        couplingCountMap[end] = weight if end not in couplingCountMap else couplingCountMap[end] + weight
    nodesWithHighestCoupling = sorted(couplingCountMap.items(), key=lambda item: item[1], reverse=True)[:c]
    return nodesWithHighestCoupling

def list2(c):
    
    global jsonObject2
    edges = jsonObject2["edges"]
    nodes = jsonObject2["nodes"]

    global nodeCount
    nodeCount = len(nodes)

    def get_node_name_from_id(nodeId):
        return [node["label"] for node in jsonObject2['nodes'] if nodeId == node["id"]][0]

    couplingCountMap = {}
    for currentEdge in edges:
        start = get_node_name_from_id(currentEdge["start"])
        end = get_node_name_from_id(currentEdge["end"])
        weight = currentEdge["weight"]
        couplingCountMap[start] = weight if start not in couplingCountMap else couplingCountMap[start] + weight
        couplingCountMap[end] = weight if end not in couplingCountMap else couplingCountMap[end] + weight
    nodesWithHighestCoupling = sorted(couplingCountMap.items(), key=lambda item: item[1], reverse=True)[:c]
    return nodesWithHighestCoupling


def compare(c): 
    l1 = list1(c)
    l2 = list2(c)


    count = 0
    for i in l1:
        if i[0] in [j[0] for j in l2]:
            count = count + 1
    return count / c

list2(1)
x = list(range(1, nodeCount, int(nodeCount / 25)))
y = [compare(i) for i in x]

print(x)
print(y)

plt.plot(x, y)
plt.xlabel('node count')
plt.ylabel("match in %")
plt.show()








   


