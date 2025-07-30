import random

vet = []
for i in range(100):
  vet.append(random.choice(range(100)))
  i = i + 1

print(f"{vet}\n")
#vet = sorted(vet)
#print(vet)
valor = int(input("Digite um valor para buscar: "))
cont = 1
flag = False
for i in range(100):  
  if vet[i] == valor:
    print(f"Valor encontrado na posição: {i}")
    print(f"Foram feitas {cont} comparações")
    flag = True
    break
  else:
    cont += 1
if flag is False:
  print("Valor não encontrado")