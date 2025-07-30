vetS = []
vetK = []

string = "o rato roeu a roupa do rei de roma"
key = input("Digite a palavra a ser buscada: ")

for i in string:
    vetS.append(i)
    
for i in key:
    vetK.append(i)


# print(vetS)
# print(vetK)

sizeK = len(key)
sizeS = len(string)
cont = 0

for i in range(sizeS - sizeK+1):
    if vetS[i:i+sizeK] == vetK:
        cont += 1
        if cont + 1 == sizeK:
            print(f"palavara encontrada a partir da posição {i - cont}")