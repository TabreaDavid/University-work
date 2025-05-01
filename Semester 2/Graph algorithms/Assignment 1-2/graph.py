from copy import deepcopy

class Graph:
    def __init__(self, vertices):
        self.outgoingEdges = {}
        self.ingoingEdges = {}
        self.costs = {}

        for vertex in range(vertices):
            self.outgoingEdges[vertex] = set()
            self.ingoingEdges[vertex] = set()

    #Adds edge to the graph from given start vertex to end vertex, returns true if succesfully
    #returns false if edge already exists
    def addEdge(self, fromVertex, toVertex, cost=0):
        if toVertex in self.outgoingEdges[fromVertex]:
            return False
        if toVertex not in self.outgoingEdges or fromVertex not in self.outgoingEdges:
            raise ValueError("Vertex not in graph!")
        self.outgoingEdges[fromVertex].add(toVertex)
        self.ingoingEdges[toVertex].add(fromVertex)
        self.costs[(fromVertex, toVertex)] = cost
        return True

    #Removes edge from given start and end index
    def removeEdge(self, fromVertex, toVertex):
        self.outgoingEdges[fromVertex].remove(toVertex)
        self.ingoingEdges[toVertex].remove(fromVertex)
        self.costs.pop((fromVertex, toVertex), None)

    #returns true if there exists an edge from given vertices
    def isEdge(self, fromVertex, toVertex):
        return toVertex in self.outgoingEdges[fromVertex]

    #returns all outbound nehibors of a given vertex
    def getOutboundNeighbors(self, vertex):
        return self.outgoingEdges[vertex]

    #returns all inbound nehibors of a given vertex
    def getInboundNeighbors(self, vertex):
        return self.ingoingEdges[vertex]

    #returns true if givne vertex exists in our graph and false otherwise
    def isVertex(self, vertex):
        return vertex in self.outgoingEdges

    #returns all graph vertices
    def getVertices(self):
        return self.outgoingEdges.keys()

    #returns the in degree of a given vertex
    def inDegree(self, vertex):
        return len(self.ingoingEdges[vertex])

    #returns the out degree of a given vertex
    def outDegree(self, vertex):
        return len(self.outgoingEdges[vertex])

    #sets costs from given start and end vertices
    def setCost(self, startVertex, endVertex, cost):
        if (startVertex, endVertex) in self.costs:
            self.costs[(startVertex, endVertex)] = cost

    #returns costs of the edge between the given vertices
    def getCost(self, startVertex, endVertex):
        return self.costs.get((startVertex, endVertex), None)

    #returns the total edge count of the graph
    def edgesCount(self):
        return len(self.costs)


    #adds a new vertex with no edges to the graph
    def addVertex(self):
        newVertex = max(self.outgoingEdges.keys()) + 1
        self.outgoingEdges[newVertex] = set()
        self.ingoingEdges[newVertex] = set()

    #removes a vertex and all conected edges from the graph
    def removeVertex(self, vertex):
        for neighbor in list(self.outgoingEdges[vertex]):
            self.removeEdge(vertex, neighbor)
        for neighbor in list(self.ingoingEdges[vertex]):
            self.removeEdge(neighbor, vertex)
        del self.outgoingEdges[vertex]
        del self.ingoingEdges[vertex]

    #returns a deep copy of the graph
    def copyGraph(self):
        return deepcopy(self)