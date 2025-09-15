from sparse_graph import SparseGraph

if __name__ == "__main__":
    classes = ['M', 'A', 'C', 'F', 'Q', 'P']
    g = SparseGraph(classes)

    g.add_edge('C', 'F')
    g.add_edge('C', 'A')
    g.add_edge('F', 'A')
    g.add_edge('M', 'P')
    g.add_edge('M', 'A')
    g.add_edge('P', 'A')
    g.add_edge('Q', 'F')

    for v_origin, v_dest in g.get_edges():
        print(f"- Class {v_origin} has a conflict with: {v_dest}")
    print("-" * 30)

    minimum_schedules, color_assignments = g.color_graph()
    print(f"Minimum number of schedules required (Chromatic Number χ(G)): {minimum_schedules}")
    print(color_assignments)