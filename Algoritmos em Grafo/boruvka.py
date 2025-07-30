from collections import defaultdict
class Grafo:

    def __init__(self, vertices):
        self.V = vertices
        self.grafo = []
          
    def adicionaAresta(self, u, v, w):
        self.grafo.append([u, v, w])

    def encontrar(self, pai, i):
        if pai[i] == i:
            return i
        return self.encontrar(pai, pai[i])

    def uniao(self, pai, classificacao, x, y):
        raizX = self.encontrar(pai, x)
        raizY = self.encontrar(pai, y)

        if classificacao[raizX] < classificacao[raizY]:
            pai[raizX] = raizY
        elif classificacao[raizX] > classificacao[raizY]:
            pai[raizY] = raizX
        else:
            pai[raizY] = raizX
            classificacao[raizX] += 1

    def boruvkaMST(self):
        pai = []
        classificacao = []
        maisBarata = []

        numArvores = self.V
        pesoMST = 0

        for node in range(self.V):
            pai.append(node)
            classificacao.append(0)
            maisBarata = [-1] * self.V

        while numArvores > 1:

            for i in range(len(self.grafo)):

                u, v, w = self.grafo[i]
                conjunto1 = self.encontrar(pai, u)
                conjunto2 = self.encontrar(pai, v)

                if conjunto1 != conjunto2:

                    if maisBarata[conjunto1] == -1 or maisBarata[conjunto1][2] > w:
                        maisBarata[conjunto1] = [u, v, w]

                    if maisBarata[conjunto2] == -1 or maisBarata[conjunto2][2] > w:
                        maisBarata[conjunto2] = [u, v, w]

            for node in range(self.V):

                if maisBarata[node] != -1:
                    u, v, w = maisBarata[node]
                    conjunto1 = self.encontrar(pai, u)
                    conjunto2 = self.encontrar(pai, v)

                    if conjunto1 != conjunto2:
                        pesoMST += w
                        self.uniao(pai, classificacao, conjunto1, conjunto2)
                        print(f"Aresta {u}-{v} com peso {w} incluída na MST")
                        numArvores = numArvores - 1
            maisBarata = [-1] * self.V

        print(f"Peso da MST é {pesoMST}")


g = Grafo(4)
g.adicionaAresta(0, 1, 10)
g.adicionaAresta(0, 2, 6)
g.adicionaAresta(0, 3, 5)
g.adicionaAresta(1, 3, 15)
g.adicionaAresta(2, 3, 4)

g.boruvkaMST()
