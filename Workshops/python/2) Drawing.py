
newPage(500, 400)


#rect(0, 0, 100, 100)

pad = 5;

for x in range(50):
    for y in range(40):
        fill(.5, y/40, x/50)
        rect (x*10, y*10, 10, 10)
        #oval(x*10, y*10, 10, 10)
        

fill(1, 1, 1)
font("Helvetica Neue Ultralight", 26)
text("check one three", (10, 10))

