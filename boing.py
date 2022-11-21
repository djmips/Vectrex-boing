import numpy as np
import math

sLat = 180/8
sLong = 180/8
radius = 200.0

def cos(deg):
    return math.cos(math.radians(deg))

def sin(deg):
    return math.sin(math.radians(deg))

def drawExterior():

    x1 = 0
    y1 = radius

    for deg in np.arange (0.0,360.0,sLong):
        x2 = sin(deg + sLong) * radius
        y2 = cos(deg + sLong) * radius

        dx = (x2 - x1)
        dy = (y2 - y1)

        print(str(int(dy)) +  ",", str(int(dx * 1.25)) + "," )  # Full globe if using 360

        x1 = x2
        y1 = y2

def drawBall():

    #latDeg = 0
    seg = 0

    #for latDeg in np.arange(12.0, 180.0, sLat ):
    #for latDeg in np.arange(12.0, 13.0, sLat ):

    latDeg = 45

    print ("const signed char seg" + str(seg) + "[] = {")
    print ("6,")
    print ("---------")
    for deg in np.arange(0.0, (180.001-sLong), sLong):
        # ty = cos(deg+sLat) * radius
        # by = cos(deg) * radius
        # tx1 = cos(latDeg) * (radius * sin(deg + sLong))
        # bx1 = cos(latDeg) * (radius * sin(deg))

        print (deg, latDeg)
        x1 = cos(latDeg) * (radius * sin(deg))
        y1 = cos(deg) * radius
        x2 = cos(latDeg) * (radius * sin(deg + sLong))
        y2 = cos(deg+sLat) * radius

        y1 = y1 * 1.25
        #print(str(int(x1)), ",", str(int(y1)),",")
    print ("---------")
    print ("};")
    seg = seg + 1



drawExterior()
drawBall()