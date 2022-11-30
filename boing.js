var sDiv = 8;
var sLat = (180/sDiv);
var sLong = (180/sDiv);
var radius = 90;
var bx = 204;
var by = 171.3;
var n = 3.8;
var dn = 0.16;
var xs = 1.5;
var lpf = 0;
var tlen = 0;


var circleTab = [];

var zbuffer;

frameRate(50);

var pic = createGraphics(400, 400, JAVA2D);

// Define some common functions for working with vectors
//var add = function(a, b) {  return (a.x + b.x, a.y + b.y);};
//var sub = function(a, b) {  return (a.x - b.x, a.y - b.y);};
//var dot = function(a, b) {  return a.x * b.x + a.y * b.y;};
//var hypot2 = function(a, b) { return dot(sub(a, b), sub(a, b));};
    
//var v1 = new PVector(40, 20);
//var v2 = new PVector(25, 50);     

//PVector.multiply = function(a, b) {
//	if (b instanceof PVector){
//	    return new PVector(a.x * b.x, a.y * b.y);
//	}
//	else {
//	    return new PVector(a.x * b, a.y * b);
//	}
//};

var perpdot = function(a, b) {
	return -a.y * b.x + a.x * b.y;
};

//v1.mult(v2);

//var dd = v1.dot(v2);

//debug(dd);
//debug(v1.z);
    
var ipoint = function(x,y,debug)
{
    var xb = x; // + 30;
    var yb = y; // + 31;
    
    var zval = zbuffer[yb*400*4 + xb*4];
    if (zval===0)
    {
        point(x,y);
    }
};

var drawLine = function(x1, y1, x2, y2, debug)
{
    var x = Math.trunc(x1);
    var y = Math.trunc(y1);
    x2 = Math.trunc(x2);
    y2 = Math.trunc(y2);

    var dx = abs(x-x2);
    var dy = abs(y-y2);

    var hy = dy;
    var hx = dx;
    var ddy = 0;
    var ddx = 0;
    var ix = 1;
    var iy = 1;
    
    if (x1 > x2){
        ix = -1;
    }

    if (y1 > y2){
        iy = -1;
    }

    if (dy > dx)
    {
        while(hy)
        {
            point(x, y);
            ddy = ddy - dx;
    
            if (ddy < 0){
                x = x + ix;
                ddy = ddy + dy;
            }    
            y = y + iy;
            hy = hy  - 1;
        }
    } else {

        while(hx)
        {
            point(x, y);        
            ddx = ddx - dy;
    
            if (ddx < 0){
                y = y + iy;
                ddx = ddx + dx;
            }    
            x = x + ix;
            hx = hx - 1;
        }        
    }    
};


var length = function(x1, y1, x2, y2) {
    
    var vx = x1 - x2;
    var vy = y1 - y2;
    
    return sqrt(sq(vx) + sq(vy));
};

var cline = function(x1, y1, x2, y2) {
    line (x1,y1,x2,y2);
    lpf++;
    tlen += length(x1,y1,x2,y2);
};


var lineCircleCollision = function(circlePos, radius, line1, line2) {
    
    var c = new PVector(circlePos.x,circlePos.y);
    var l2 = new PVector(line2.x, line2.y);
    
    c.sub(line1);
    l2.sub(line1);
    
    var t = l2.dot(c) / l2.dot(l2);

    if (t < 0) {
        t = 0;
    }
    else if (t > 1) {
        t = 1;
    }

    l2.mult(t);
    l2.sub(c);

    return l2.dot(l2) <= sq(radius);
};




var fillCircleTable = function(x1, y1, x2, y2)
{
    var x = Math.trunc(x1);
    var y = Math.trunc(y1);
    x2 = Math.trunc(x2);
    y2 = Math.trunc(y2);

    var dx = abs(x-x2);
    var dy = abs(y-y2);

    var hy = dy;
    var hx = dx;
    var ddy = 0;
    var ddx = 0;
    var ix = 1;
    var iy = 1;
    
    if (x1 > x2){
        ix = -1;
    }

    if (y1 > y2){
        iy = -1;
    }

    if (dy > dx)
    {
        while(hy)
        {
            point(x, y);
            circleTab[y] = x;
            ddy = ddy - dx;
    
            if (ddy < 0){
                x = x + ix;
                ddy = ddy + dy;
            }    
            y = y + iy;
            hy = hy  - 1;
        }
    } else {

        while(hx)
        {
            point(x, y);
            circleTab[y] = x;
            
            ddx = ddx - dy;
    
            if (ddx < 0){
                y = y + iy;
                ddx = ddx + dx;
            }    
            x = x + ix;
            hx = hx - 1;
        }        
    }    
};


var createCircleTable = function() {

    //stroke(40, 186, 7);
    //translate(200,200);
    
    var x1 = 0;
    var y1 = radius;
    
    for (var deg = 0; deg < 90; deg += sLong)
    {
        var x2 = sin(deg + sLong) * radius;
        var y2 = cos(deg + sLong) * radius;

        fillCircleTable(x1, y1, x2,y2);
        line(x1, y1, x2,y2);

        x1 = x2;
        y1 = y2;
    }
    
    // HACK
    circleTab[0]=90;
};


var drawGrid = function(size) {

    translate (30,30);
    var cx = bx-30;
    var cy = by-30; 
    
    stroke(0, 176, 62);

    var t;
    var cpos = new PVector(cx,cy);

    // Vertical lines
    
    for (var vlines = 0, xpos = 0; vlines < 8; vlines++) {

        if (xpos < (cpos.x-radius) || xpos > (cpos.x + radius)) {
            line(xpos, 0, xpos, size);
        }
        else
        {
            var bspacex = cx - xpos;
            var index = floor(abs(bspacex));
            var circleY = circleTab[index];
            line (xpos, 0, xpos, max(cy-circleY,0));
            line (xpos, min(circleY+cy,size), xpos, size);
        }
        xpos+=(size/7);
    }
    
    //for (var vlines = 0, xpos = 0; vlines < 8; vlines++) {
        //line(xpos, size, xpos*1.05-8, size+8);
        //xpos+=(size/7);
    //} 

    // Horizontal lines    

    for (var hlines = 0, ypos = 0; hlines < 7; hlines++) {

        if (ypos < (cpos.y-radius) || ypos > (cpos.y + radius)) {
            line(0, ypos, size, ypos);
        }
        else {
            var bspacey = cy - ypos;
            var index = floor(abs(bspacey));
            var circleX = circleTab[index];
            line (0, ypos, max(cx-circleX,0),ypos);
            line (min(circleX+cx,size), ypos, size,ypos);
        }

        ypos+=(size/6);

    }
    
    //ypos-=(size/6)-2;
    //line(-1, ypos, size+2, ypos);
    //ypos+=4;
    //line(-5, ypos, size+6, ypos);


};

var drawExterior = function() {

    //stroke(255, 60, 0);

    var bx = 0;
    var by = radius;

    var deg = 0;

    for (deg = 0; deg < (180-sLong); deg += sLong)
    {
        var tx = Math.round(sin(deg + sLong) * radius);
        var ty = Math.round(cos(deg + sLong) * radius);

        cline(tx, ty, bx, by);
        cline(-tx, ty, -bx, by);
        cline(tx,ty, -tx,ty);
        bx = tx;
        by = ty;

    }
    {
        var tx = Math.round(sin(deg + sLong) * radius);
        var ty = Math.round(cos(deg + sLong) * radius);
        cline(tx, ty, bx, by);
        cline(-tx, ty, -bx, by);
    }        

};

var drawBall = function( ani ) {

    //stroke(0, 250, 88);
    
    for ( var latDeg = ani + (sLat /2); latDeg < 180- (sLat/2); latDeg += sLat )
    //for ( var latDeg = ani ; latDeg < 180; latDeg += sLat )
    {
    
        for (var deg = sLong; deg < (180-sLong); deg += sLong)
        {
            var ty = cos(deg+sLat) * radius;
            var by = cos(deg) * radius;
            var tx1 = cos(latDeg) * (radius * sin(deg + sLong));
            var bx1 = cos(latDeg) * (radius * sin(deg));
            var tx2 = cos(latDeg + sLat) * (radius * sin(deg + sLong));
            var bx2 = cos(latDeg + sLat ) * (radius * sin(deg));
    
            cline(Math.round(tx1), Math.round(ty), Math.round(bx1), Math.round(by));
        }
    }
};

var imagePrep = function(x, y) {
  
    var r = radius*2;
    pic.beginDraw();
    pic.background(0, 0, 0);
    
    pic.fill(255, 255, 255);
    pic.ellipse (x,y,r,r);
    
    pic.endDraw();
    
};

//debug("---------NEW RUN----------");

//background(0, 0, 0);
createCircleTable();
//debug(circleTab);
//debug(circleTab[0]);
//debug(circleTab[90]);
//for (var xx = 0; xx < 90; xx++) {
//    debug (circleTab[xx]);
//}

var draw1 = function() {
};

var draw = function() {
    
    lpf = 0;
    tlen = 0;
    
    background(0, 0, 0);
    
    resetMatrix();

    //imagePrep(bx,by);
    //image(pic, 0, 0);
    //pic.loadPixels();
    //zbuffer = pic.imageData.data;

    strokeWeight(1);    
    drawGrid(342);

    resetMatrix();

    //point(bx,by);
    stroke(235, 17, 68);
    //ellipse(200,200,110,110);
  
    stroke(29, 133, 66);
    strokeWeight(2);

    translate(bx,by);
    rotate(22.5);

    drawExterior();
    var ani = Math.trunc(bx*1.5%sLat);
    drawBall(ani);
    //println(ani);
    
    bx = bx + xs;
    if (bx < 90){
        bx = bx - xs;
        xs = -xs;
    }
    if (bx > 310){
        bx =bx - xs;
        xs = -xs;
    }
    
    by = by + n;
    n = n + dn;
    if (by > 310 ){
        n = n - dn;
        n = - n;
    }
    
    //println(tlen);
    //println(lpf);
    
    
    
};

draw1();

