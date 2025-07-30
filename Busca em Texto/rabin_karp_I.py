def share(string, chave, q):
  m = len(chave)
  k = [ord(i) for i in chave]
  st = [ord(i) for i in string]
  vet = []
  
  for i in range(0, len(st) - len(k)):  # vetor com as sequencias de caracteres
    aux = st[i:i + m]
    join = int("".join(map(str, aux)))
    vet.append(join)
    
  vet2 = []
  
  for i in range(0, len(st) - len(k)):  # vetor após aplicar mod q
    aux = vet[i] % q
    vet2.append(aux)
    
  concatena = ''.join(map(str, k))  # junta os numeros da chave em um inteiro
  concatena = int(concatena)
  num = concatena % q
  
  for i in range(0, len(vet2)):
    if num == vet2[i]:
      for j in range(i, i + m):
        if st[j] == k[j - i]:
          print(i)
          break


string = "o rato roeu a roupa do rei de roma" 
key = input("Digite um palavra a ser buscada: ")
d = 256
q = 29
share(string, key, q)
