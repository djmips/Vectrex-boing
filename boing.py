import numpy as np
import math

sLat = 180/8
sLong = 180/8
radius = 80.0

def cos(deg):
    return math.cos(math.radians(deg))

def sin(deg):
    return math.sin(math.radians(deg))

def drawExterior():
    for deg in np.arange (0.0,360.0,sLong):
        tx = sin(deg + sLong) * radius
        ty = cos(deg + sLong) * radius

        ty = ty * 1.25

        print(int(tx), ",", int(ty),"," )  # Full globe if using 360
       
def drawBall():

    #latDeg = 0
    seg = 0

    for latDeg in np.arange(12.0, 180.0, sLat ):
    #for latDeg in np.arange(12.0, 13.0, sLat ):

        print ("const signed char seg" + str(seg) + "[] = {")
        print ("5,")

        for deg in np.arange(sLong, (180-sLong), sLong):
            # ty = cos(deg+sLat) * radius
            # by = cos(deg) * radius
            # tx1 = cos(latDeg) * (radius * sin(deg + sLong))
            # bx1 = cos(latDeg) * (radius * sin(deg))

            x1 = cos(latDeg) * (radius * sin(deg))
            y1 = cos(deg) * radius
            x2 = cos(latDeg) * (radius * sin(deg + sLong))
            y2 = cos(deg+sLat) * radius

            y2 = y2 * 1.25
            print(int(x2), ",", int(y2),",")

        print ("};")
        seg = seg + 1



#drawExterior()
drawBall()