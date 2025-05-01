from graph import Graph
from random import randint as randomNumber

from collections import deque

#Finds the shortest path between two vertices using BFS
def findShortestPath(graph, startVertex, endVertex):
    visited = set()
    parent = {}
    queue = [startVertex]
    visited.add(startVertex)

    while queue:
        current = queue[0]
        queue = queue[1:] 

        if current == endVertex:
            path = []
            while current != startVertex:
                path.append(current)
                current = parent[current]
            path.append(startVertex)
            return path[::-1]

        for neighbor in graph.getOutboundNeighbors(current):
            if neighbor not in visited:
                visited.add(neighbor)
                parent[neighbor] = current
                queue.append(neighbor)

    return None  

#Reads graph data from a file and initializes the graph with vertices and edges
def readGraphFromFile(graph, filename):
    with open(filename, "r") as file:
        lines = file.readlines()
        vertices, edges = map(int, lines[0].strip().split())
        graph.__init__(vertices)  
        for line in lines[1:]:
            if line.strip() == "":
                continue
            start, end, cost = map(int, line.strip().split())
            graph.addEdge(start, end, cost)
    print("Graph loaded successfully.")

#Writes the graph structure and edge costs to a text file
def writeGraphToFile(graph, filename):
    with open(filename, "w") as file:
        file.write(f"{len(graph.getVertices())} {graph.edgesCount()}\n")
        for (start, end), cost in graph.costs.items():
            file.write(f"{start} {end} {cost}\n")
    print("Graph saved successfully.")

#Generates a random directed graph with specified number of vertices and edges
def generateRandomGraph(vertexNumber, edgeNumber):
    graph = Graph(vertexNumber)
    i = 1
    if edgeNumber > vertexNumber * vertexNumber:
        print("Too many edges! Using max possible.")
        edgeNumber = vertexNumber * vertexNumber
    while i <= edgeNumber:
        start = randomNumber(0, vertexNumber - 1)
        end = randomNumber(0, vertexNumber - 1)
        cost = randomNumber(1, 100)
        if graph.addEdge(start, end, cost):
            i += 1
    return graph

#Prints the outbound and inbound neighbors of each vertex along with edge costs
def displayGraph(graph):
    print("Outbound edges:")
    for vertex in graph.getVertices():
        neighbors = " ".join(f"{nbr}({graph.getCost(vertex, nbr)})" for nbr in graph.getOutboundNeighbors(vertex))
        print(f"{vertex}: {neighbors}")
    print("Inbound edges:")
    for vertex in graph.getVertices():
        neighbors = " ".join(map(str, graph.getInboundNeighbors(vertex)))
        print(f"{vertex}: {neighbors}")

#Prints the costs of all edges in the graph
def displayEdgeCosts(graph):
    print("Edge costs:")
    for (start, end), cost in graph.costs.items():
        print(f"Edge ({start} -> {end}) has cost: {cost}")

#Prints menu with 16 entries
def printMenu():
    print("\n1. Get number of vertices")
    print("2. Display graph")
    print("3. Get in degree of vertex")
    print("4. Get out degree of vertex")
    print("5. Create random graph")
    print("6. Read graph from text file")
    print("7. Write graph to text file")
    print("8. Add vertex")
    print("9. Add edge")
    print("10. Remove vertex")
    print("11. Remove edge")
    print("12. Set cost to an edge")
    print("13. Get cost of an edge")
    print("14. Show costs between all edges")
    print("15. Return copy")
    print("16. Find shortest path")
    print("0. Exit\n")


def runUi():
    graph = Graph(4)
    graph.addEdge(0, 1, 10)
    graph.addEdge(1, 2, 20)
    graph.addEdge(2, 3, 30)
    graph.addEdge(3, 0, 40)

    while True:
        printMenu()
        choice = input("Enter your choice: ")
        if choice == "0":
            break
        elif choice == "1":
            print(f"Number of vertices: {len(graph.getVertices())}")
        elif choice == "2":
            displayGraph(graph)
        elif choice == "3":
            vertex = int(input("Vertex: "))
            print(f"In degree: {graph.inDegree(vertex)}")
        elif choice == "4":
            vertex = int(input("Vertex: "))
            print(f"Out degree: {graph.outDegree(vertex)}")
        elif choice == "5":
            vertices = int(input("Vertices: "))
            edges = int(input("Edges: "))
            graph = generateRandomGraph(vertices, edges)
        elif choice == "6":
            filename = input("File name: ")
            readGraphFromFile(graph, filename)
        elif choice == "7":
            filename = input("File name: ")
            writeGraphToFile(graph, filename)
        elif choice == "8":
            graph.addVertex()
            print("Vertex added.")
        elif choice == "9":
            start = int(input("Start vertex: "))
            end = int(input("End vertex: "))
            cost = int(input("Cost: "))
            if graph.addEdge(start, end, cost):
                print("Edge added.")
            else:
                print("Edge already exists.")
        elif choice == "10":
            vertex = int(input("Vertex: "))
            graph.removeVertex(vertex)
            print("Vertex removed.")
        elif choice == "11":
            start = int(input("Start vertex: "))
            end = int(input("End vertex: "))
            graph.removeEdge(start, end)
            print("Edge removed.")
        elif choice == "12":
            start = int(input("Start vertex: "))
            end = int(input("End vertex: "))
            cost = int(input("New cost: "))
            graph.setCost(start, end, cost)
        elif choice == "13":
            start = int(input("Start vertex: "))
            end = int(input("End vertex: "))
            print(f"Cost: {graph.getCost(start, end)}")
        elif choice == "14":
            displayEdgeCosts(graph)
        elif choice == "15":
            copied_graph = graph.copyGraph()
            print("Graph copied. Displaying the copied graph:")
            displayGraph(copied_graph)
        elif choice == "16":
            start = int(input("Start vertex: "))
            end = int(input("End vertex: "))
            path = findShortestPath(graph, start, end)
            if path:
                print("Shortest path:", " to ".join(map(str, path)))
            else:
                print("No path exists between the given vertices")
        else:
            print("Invalid option.")

runUi()