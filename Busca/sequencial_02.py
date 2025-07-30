import random

vet = []
for i in range(0, 101):
  vet.append(random.choice(range(100)))
#print(vet)
valor = int(input("Digite o valor a ser procurado: "))
cont = 1
flag = False
for i in range(0, 101):
  if vet[i] == valor:
    print(i)
    flag = True
  else:
    cont += 1 

if flag is False:
  print("Valor não encontrado")
else:
  print(f"Foram feitas {cont} comparações")