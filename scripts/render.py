import json
import matplotlib.pyplot as plt
import networkx as nx
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("input", help="input JSON file", type=argparse.FileType('r'))
args = parser.parse_args()

jsonObject = json.load(args.input)

def get_node_name_from_id(nodeId):
    return [node["label"] for node in jsonObject['nodes'] if nodeId == node["id"]][0]

G = nx.DiGraph()
G.add_edges_from([(get_node_name_from_id(edge['start']), get_node_name_from_id(edge['end'])) for edge in jsonObject['edges']])
labels = {((get_node_name_from_id(edge['start']), get_node_name_from_id(edge['end']))):edge["weight"] for edge in jsonObject['edges']}

pos = nx.spring_layout(G, k=100, iterations=1, seed = 7)

nx.draw_networkx_edges(G, pos)
nx.draw_networkx_labels(G, pos)
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)

plt.axis("off")
plt.show()