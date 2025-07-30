import random 

vet = []
for i in range(0,101):
  vet.append(random.choice(range(100)))
vet = sorted(vet)
print(vet)

valor = int(input("Digite o valor a ser buscado: "))
inicio = 0
fim = len(vet) - 1
cont = 0

vet = []
for i in range(0, 101):
  vet.append(random.choice(range(100)))
vet = sorted(vet)
print(vet)

valor = int(input("Digite um valor para ser buscado: "))
inicio = 0
fim = len(vet) - 1
cont =  0
flag = False

while inicio <= fim:
  meio = (inicio + fim)//2
  if vet[meio] == valor:
    print(meio)
    aux = meio + 1
    if aux <= len(vet) - 1:
      while vet[aux] == valor:
        print(aux)
        aux += 1
        cont += 1
    aux = meio - 1
    if aux >= 0:
      while vet[aux] == valor:
        print(aux)
        aux -= 1
        cont += 1
    flag = True
    break
  elif vet[meio] < valor:
    inicio = meio + 1
    cont += 1
  else:
    fim = meio - 1
    cont += 1
if flag is False:
  print("Valor não encontrado!")
else:
  print(f"Foram feitas {cont} verificações")
  



flag = False
while inicio <= fim:
  meio = (inicio + fim)//2
  if vet[meio] == valor:
    print(f"{valor} encontrado na posição {meio}")
    print(f"Foram feitas {cont} comparações")
    flag = True
    break
  elif vet[meio] < valor:
    inicio = meio + 1
    cont += 1
  else:
    fim = meio - 1
    cont += 1
if flag is False:
  print(f"{valor} não encontrado")
