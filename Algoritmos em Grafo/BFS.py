from Grafo import Grafo # importa a classe grafo

def bfs(grafo, vertice_fonte):
    visitados, fila = set(), [vertice_fonte] # uma lista para os vertices ja visitados
    while fila: # uma fila para inserir os vertices adjacentes ao recem visitado
        vertice = fila.pop(0) # retira o vertice visado da fila
        if vertice not in visitados:
            visitados.add(vertice) #coloca esse vertice na lista de visitados
            fila.extend(grafo[vertice] - visitados) # adiciona todos os vertices adjacentes não visitados
    return visitados


arestas = [(0, 1), (1, 2), (1, 3),(2, 1), (2, 4), (3, 0), (4, 1)] # arestas do grafo
grafo = Grafo(arestas, direcionado=True) # instancia o objeto da classe grafo, passando suas arestas
print(grafo)
print("BFS começando do vertice 0")
print(f'Visitando vertice {bfs(grafo, 0)}')
