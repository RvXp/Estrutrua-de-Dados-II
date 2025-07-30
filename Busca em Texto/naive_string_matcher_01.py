def share(string, key, i, sizeK):
  sizeK += i
  if string[i:sizeK] == key:
    print(i)
  else:
    return
    
string = "o rato roeu a roupa do rei de roma"
key = input("Digite a palavra a ser buscada: ")
for i in range(len(string) - len(key) + 1):
  share(string, key, i, len(key))