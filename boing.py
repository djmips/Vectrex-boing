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

rotAngle = -22.5
cosra = cos(rotAngle)
sinra = sin(rotAngle)

def drawCircumference():

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

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )  # Full globe if using 360

        rx1 = rx2
        ry1 = ry2

def drawLatitude():

    scaledRadius = radius / 3.85

    latSeg = 0

    for longDeg in np.arange(sLong, 180.0, sLong ):

        print ("const signed char latSeg" + str(latSeg) + "[] = {")
        print ("0,")        

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

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )

        doffset = (latSeg+1) * 45
        x1 = sin(longDeg-doffset) * scaledRadius
        y1 = cos(longDeg-doffset) * scaledRadius

        rx1 = x1 * cosra - y1 * sinra
        ry1 = x1 * sinra + y1 * cosra

        rx2 = x2 * cosra - y2 * sinra
        ry2 = x2 * sinra + y2 * cosra

        dx = (rx1 - rx2)
        dy = (ry1 - ry2)

        print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )


        #dx = (x2 - x1)
        #dy = (y2 - y1)
        #print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )

        #line(x1,y1, -x1,y1)

        print ("};")
        latSeg = latSeg + 1

def drawLongitude():

    #latDeg = 0
    seg = 0

    for ani in range(0, 22, 2):

        print ("const signed char long" + str(seg) + "[] = {")
        print ("55,")

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

                    print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )
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

                    print(str(int(dy)) +  ",", str(int(dx * aspectConst)) + "," )

            negF = -negF

        seg = seg + 1
        print ("};")



#drawCircumference()
drawLatitude()
#drawLongitude()
