import json
import matplotlib.pyplot as plt
import networkx as nx
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("input", help="input JSON file", type=argparse.FileType('r'))
parser.add_argument("output", help="output JSON file", type=str)
args = parser.parse_args()

jsonObject = json.load(args.input)

def get_node_name_from_id(nodeId):
    return [node["label"] for node in jsonObject['nodes'] if nodeId == node["id"]][0]

G = nx.DiGraph()
G.add_weighted_edges_from([(get_node_name_from_id(edge['start']), get_node_name_from_id(edge['end']), edge["weight"]) for edge in jsonObject['edges']])

nx.readwrite.write_gml(G, args.output)