class Grafo:
 
    def __init__(self, grafo):
        self.grafo = grafo
        self. ROW = len(grafo)
 
    def BFS(self, s, t, parente):
        visitado = [False]*(self.ROW)
        fila = []
        fila.appen(s)
        visitado[s] = True
        while fila:
            u = fila.pop(0)
            for ind, val in enumerate(self.grafo[u]):
                if visitado[ind] == False and val > 0:
                    fila.append(ind)
                    visitado[ind] = True
                    parente[ind] = u
                    if ind == t:
                        return True
        return False
             
    def FordFulkerson(self, source, sink):
        parente = [-1]*(self.ROW)
        max_flow = 0
        while self.BFS(source, sink, parente) :
            path_flow = float("Inf")
            s = sink
            while(s !=  source):
                path_flow = min (path_flow, self.grafo[parente[s]][s])
                s = parente[s]
            max_flow +=  path_flow
            v = sink
            while(v !=  source):
                u = parente[v]
                self.grafo[u][v] -= path_flow
                self.grafo[v][u] += path_flow
                v = parente[v]
 
        return max_flow
 
grafo = [[0, 16, 13, 0, 0, 0],
        [0, 0, 10, 12, 0, 0],
        [0, 4, 0, 0, 14, 0],
        [0, 0, 9, 0, 0, 20],
        [0, 0, 0, 7, 0, 4],
        [0, 0, 0, 0, 0, 0]]
 
g = Grafo(grafo)
 
source = 0; sink = 5
  
print ("The maximum possible flow is %d " % g.FordFulkerson(source, sink))