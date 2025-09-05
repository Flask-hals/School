#jakno825
#thosj050
# TDP015 Programming Assignment 5
# Graphs
# Skeleton Code

# In a research project at IDA algorithms 
# for the parsing of natural language to meaning representations in
# the form of directed graphs are developed.
#
# A desirable property of these graphs is that they should be acyclic,
# that is, should not contain any (directed) cycles. Your task in this
# assignment is to implement a Python function that tests this
# property, and to apply your function to compute the number of cyclic
# graphs in one of the datasets that I am using in my research.
#
# Your final script should be callable from the command line as follows:
#
# $ python3 p5.py ccg.train.json
#
# With this data file your program should report 418 cyclic graphs.
#
# The graphs are stored in a JSON file containing a single dictionary
# mapping graph ids (8-digit integers) to graphs, where each graph is
# represented as a dictionary mapping vertices (or rather their ids)
# to lists of neighbouring vertices.
import json
import sys

def cyclic(graph):
    """Test whether the directed graph `graph` has a (directed) cycle.

    The input graph needs to be represented as a dictionary mapping vertex
    ids to iterables of ids of neighboring vertices. Example:

    {"1": ["2"], "2": ["3"], "3": ["1"]}

    Args:
        graph: A directed graph.

    Returns:
        `True` iff the directed graph `graph` has a (directed) cycle.
    """
    # TODO: Replace the following line with your own code.
    deg = {}
    s = set()
    
    for key in graph.keys():
        add = True
        for values in graph.values():
            for items in values:
                if key == items:
                    add = False
                    if key not in deg.keys():
                        deg[key] = 1
                    else:
                        deg[key] += 1
        if add:  
            s.add(key)

    while len(s) != 0:
        node = s.pop()
        for keys in graph.keys():
            for values in graph[node]:
                if keys == values:
                    graph[node].remove(values)
                    deg[keys] -= 1
                if keys in deg.keys():
                    if deg[keys] == 0:
                        s.add(keys)
            
    for edges in graph.values():
        if len(edges) != 0:
            return True
    return False


if __name__ == "__main__":
    # TODO: Replace the following line with your own code.
    with open(sys.argv[1], 'r') as file:
        data = json.load(file)

    count = 0
    for value in data.values():
        iscyclic = cyclic(value)
        if iscyclic:
            count += 1
    print(count)