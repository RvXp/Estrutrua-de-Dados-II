def rabinkarp(txt, pal):
  
  n = len(txt)
  m = len(pal)
  d = 256
  q = 13
  h = (d**(m-1))%q

  p = 0
  t = 0

  for i in range(0, m):
    p = (d*p + pal[i])%q
    t = (d*t + txt[i])%q
  for i in range(0, n-m):
    if p == t and pal[1:m] == txt[i+1:i+m]:
        print("posicao:", i)
    if i < n-m:
      t = (d*(t-txt[i]*h) + txt[i+m])%q
      
txt = "o rato roeu a roupa do rei de roma"
pal = "rei"

txt = [ord(i) for i in txt]
pal = [ord(i) for i in pal]
rabinkarp(txt, pal)
