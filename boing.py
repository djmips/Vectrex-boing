import numpy as np
import math
from pathlib import Path

sLat = 180/8
sLong = 180/8
radius = 220.0

aspectConst = 1.15

def cos(deg):
    return math.cos(math.radians(deg))

def sin(deg):
    return math.sin(math.radians(deg))

rotAngle = -22.5
cosra = cos(rotAngle)
sinra = sin(rotAngle)

data_folder = Path("BoingSrc/source/")

def drawCircumference():

    latfile = data_folder / "circ.h"
    
    with open(latfile, 'w') as f:

        print ("const signed char ball[] = {", file=f)
        print ("15,", file=f)

        x1 = 0
        y1 = radius

        rx1 = x1 * cosra - y1 * sinra
        ry1 = x1 * sinra + y1 * cosra

        for deg in np.arange (0.0,360.0,sLong):
            x2 = sin(deg + sLong) * radius
            y2 = cos(deg + sLong) * radius
        
            # rotate
            rx2 = x2 * cosra - y2 * sinra
            ry2 = x2 * sinra + y2 * cosra
            
            dx = (rx2 - rx1)
            dy = (ry2 - ry1)

            print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + ",", file=f )  # Full globe if using 360

            rx1 = rx2
            ry1 = ry2

        print ("};", file=f)

def drawLatitude():

    latfile = data_folder / "lat.h"
    
    with open(latfile, 'w') as f:

        scaledRadius = radius / 3.85

        latSeg = 0

        for longDeg in np.arange(sLong, 180.0, sLong ):

            print ("const signed char latSeg" + str(latSeg) + "[] = {", file=f)
            print ("0,", file=f)        

            x1 = 0
            y1 = scaledRadius

            x2 = sin(longDeg) * scaledRadius
            y2 = cos(longDeg) * scaledRadius

            rx1 = x1 * cosra - y1 * sinra
            ry1 = x1 * sinra + y1 * cosra

            rx2 = x2 * cosra - y2 * sinra
            ry2 = x2 * sinra + y2 * cosra

            dx = (rx2 - rx1)
            dy = (ry2 - ry1)

            print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + ",", file=f )

            doffset = (latSeg+1) * 45
            x1 = sin(longDeg-doffset) * scaledRadius
            y1 = cos(longDeg-doffset) * scaledRadius

            rx1 = x1 * cosra - y1 * sinra
            ry1 = x1 * sinra + y1 * cosra

            rx2 = x2 * cosra - y2 * sinra
            ry2 = x2 * sinra + y2 * cosra

            dx = (rx1 - rx2)
            dy = (ry1 - ry2)

            print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + ",", file=f )

            print ("};", file=f)
            latSeg = latSeg + 1

def drawLongitude():

    #latDeg = 0
    seg = 0

    latfile = data_folder / "long.h"
    
    with open(latfile, 'w') as f:

        for ani in range(0, 22, 2):

            print ("const signed char long" + str(seg) + "[] = {", file=f)
            print ("55,", file=f)

            negF = 1

            for latDeg in np.arange((ani + (sLat/2)), (180.0 - sLat/2), sLat ):

            
                if (negF > 0):
                    for deg in np.arange(0.0, (180.001-sLong), sLong):
                        x1 = cos(latDeg) * (radius * sin(deg))
                        y1 = cos(deg) * radius
                        
                        x2 = cos(latDeg) * (radius * sin(deg + sLong))
                        y2 = cos(deg+sLat) * radius

                        rx1 = x1 * cosra - y1 * sinra
                        ry1 = x1 * sinra + y1 * cosra

                        rx2 = x2 * cosra - y2 * sinra
                        ry2 = x2 * sinra + y2 * cosra

                        dx = (rx2 - rx1)
                        dy = (ry2 - ry1)

                        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + ",", file=f)
                else:
                    for deg in np.arange((180 - sLong),-0.001 , -sLong):
                        x1 = cos(latDeg) * (radius * sin(deg))
                        y1 = cos(deg) * radius
                        
                        x2 = cos(latDeg) * (radius * sin(deg + sLong))
                        y2 = cos(deg+sLat) * radius

                        rx1 = x1 * cosra - y1 * sinra
                        ry1 = x1 * sinra + y1 * cosra

                        rx2 = x2 * cosra - y2 * sinra
                        ry2 = x2 * sinra + y2 * cosra

                        dx = (rx1 - rx2)
                        dy = (ry1 - ry2)

                        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + ",", file=f)

                negF = -negF

            seg = seg + 1
            print ("};", file=f)

drawCircumference()
drawLatitude()
drawLongitude()
