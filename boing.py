import numpy as np
import math

sLat = 180/8
sLong = 180/8
radius = 200.0

aspectConst = 1.2

def cos(deg):
    return math.cos(math.radians(deg))

def sin(deg):
    return math.sin(math.radians(deg))

def drawCircumference():

    x1 = 0
    y1 = radius

    for deg in np.arange (0.0,360.0,sLong):
        x2 = sin(deg + sLong) * radius
        y2 = cos(deg + sLong) * radius

        dx = (x2 - x1)
        dy = (y2 - y1)

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )  # Full globe if using 360

        x1 = x2
        y1 = y2

def drawLatitude():

    latSeg = 0

    for longDeg in np.arange(sLong, 180.0, sLong ):

        print ("const signed char latSeg" + str(latSeg) + "[] = {")

        x1 = 0
        y1 = radius

        x2 = sin(longDeg) * radius
        y2 = cos(longDeg) * radius

        dx = (x2 - x1)
        dy = (y2 - y1)

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )

        x1 = -x2
        y1 = y2

        dx = (x2 - x1)
        dy = (y2 - y1)

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )

        #line(x1,y1, -x1,y1)

        print ("};")
        latSeg = latSeg + 1



def drawLongitude():

    #latDeg = 0
    seg = 0

    print ("const signed char long" + str(seg) + "[] = {")
    print ("55,")

    negF = 1

    for latDeg in np.arange(sLat, 180.0, sLat ):
    #for latDeg in np.arange(12.0, 13.0, sLat ):

        #latDeg = 45

        for deg in np.arange(0.0, (180.001-sLong), sLong):
            x1 = cos(latDeg) * (radius * sin(deg))
            y1 = cos(deg) * radius
            
            x2 = cos(latDeg) * (radius * sin(deg + sLong))
            y2 = cos(deg+sLat) * radius

            dx = (x2 - x1)
            dy = (y2 - y1)

            print(str(int(dy * negF)) +  ",", str(int(dx * aspectConst)) + "," )

        negF = -negF

    seg = seg + 1
    print ("};")



#drawCircumference()
drawLongitude()
#drawLatitude()