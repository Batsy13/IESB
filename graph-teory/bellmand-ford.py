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
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}

shortest_path = bellman_ford(graph, 'A')
print(shortest_path)