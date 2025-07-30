def tranformacao_da_raiz(cidade, p):
    asc = sum(ord(caractere) for caractere in cidade)
    algarismos = []
    while asc > 0:
        resto = asc % 16
        algarismos.insert(0, resto)
        asc = asc // 16
    base = int(''.join(map(str, algarismos)))
    indice_hash = base % p
    return indice_hash

p = 19
tabela_hash = ['\0'] * 20
colisoes = [0] * 20
colisoes_totais = 0

with open('cidades.txt', 'r') as arquivo:
    for linha in arquivo:
        op = tranformacao_da_raiz(linha.strip(), p)
        if tabela_hash[op] == '\0':
            tabela_hash[op] = linha.strip()
        else:
            colisoes[op] += 1
            
for i in range(len(colisoes)):
    colisoes_totais += colisoes[i] 
    if colisoes[i] > 0:
        print(f'\tColisoes na posicao {i}: {colisoes[i]} \tTotal de chaves associadas a posicao {i}: {colisoes[i] + 1}')

print(f'\n\n\tNumero total de colisoes: {colisoes_totais}\n\n') 
for i in range(len(tabela_hash)):
    print(f'\tChave: {i} \tValor: {tabela_hash[i]}') 