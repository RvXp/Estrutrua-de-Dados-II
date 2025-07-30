def div(cidade, p):
    asc = sum(ord(caractere) for caractere in cidade)
    hash = asc % p
    return hash 
    

p = 19
tabela_hash = ['\0'] * 20
colisoes = [0] * 20
total_de_colisoes = 0

with open('cidades.txt', 'r') as arquivo:
    for linha in arquivo:
        op = div(linha.strip(), p)
        if tabela_hash[op] == '\0':
            tabela_hash[op] = linha.strip()
        else:
            colisoes[op] += 1
            
for i in range(len(colisoes)):
    total_de_colisoes += colisoes[i]
    if colisoes[i] > 0:
        print(f'Colisão na posição {i}: {colisoes[i]}\tNumero de cidades associadas a chave {i}: {colisoes[i]+1}')
        
print(f'\n\n\tNumero total de colisoes: {total_de_colisoes}\n\n')

for i in range(len(tabela_hash)):
    print(f'\tChave: {i} \tValor: {tabela_hash[i]}')
