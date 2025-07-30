from Grafo import Grafo # importa a classe grafo

def dfs(grafo, vertice):
    visitados = set() # cria uma lista de visitados
    def dfs_recursiva(grafo, vertice): # recebe um grafo e um vertice
        visitados.add(vertice) # adiciona o vertice na lista de visitados
        for vizinho in grafo[vertice]: # percorre os visinhos do vertice ja visitado
            if vizinho not in visitados: # se esse vizinho não foi visitado 
                print(f'Visistando vertice {vizinho}')
                dfs_recursiva(grafo, vizinho) # chama a recursão pra realizar o mesmo processo com o vizinho
    dfs_recursiva(grafo, vertice)
    

arestas = [(0, 1), (1, 2), (1, 3),(2, 1), (2, 4), (3, 0), (4, 1)]
grafo = Grafo(arestas, direcionado=True)

print(grafo)
print(f'DFS começando do vertice 0')
dfs(grafo, 0)