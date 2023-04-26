from random import *
mode = ["insert","insert","delete","find"]

n = 1000
a = open("./in","w")
a.write(str(n))
a.write("\n")
for i in range(n):
    m = randint(0,3)
    a.write(mode[m])
    a.write(" ")
    a.write(str(randint(1,10)))
    a.write(" ")
    if (m != 3):
        a.write(str(randint(1,1000)))
    a.write("\n")
a.flush()
