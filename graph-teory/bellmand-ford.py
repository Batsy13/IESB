def bellman_ford(graph, start):
    distances = {node: float('inf') for node in graph}
    distances[start] = 0

    edges = []
    for u in graph:
        for v, weight in graph[u].items():
            edges.append((u, v, weight))

    num_nodes = len(graph)

    for _ in range(num_nodes - 1):
        for u, v, weight in edges:
            if distances[u] != float('inf') and distances[u] + weight < distances[v]:
                distances[v] = distances[u] + weight

    for u, v, weight in edges:
        if distances[u] != float('inf') and distances[u] + weight < distances[v]:
            return "Graph contains a negative weight cycle"

    return distances

graph = {
    'S': {'A': 3,'B': 5},
    'A': {'C': -5, 'D': 8},
    'B': {'A': 6, 'C': 8, 'D': -9},
    'C': {'D': -3},
    'D': {'S': 2}
}

shortest_path = bellman_ford(graph, 'S')
print(shortest_path)