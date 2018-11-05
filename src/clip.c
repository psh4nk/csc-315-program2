#include "tessellate.c"

/*void clip(struct vertex *vp, int points){
    vertex *clipPolygon;

    //define clipping polygon
    (clipPolygon+0)->x = VIEWPORT_MIN;
    (clipPolygon+0)->y = VIEWPORT_MIN;
    (clipPolygon+1)->x = VIEWPORT_MIN;
    (clipPolygon+1)->y = VIEWPORT_MAX;
    (clipPolygon+2)->x = VIEWPORT_MAX;
    (clipPolygon+2)->y = VIEWPORT_MAX;
    (clipPolygon+3)->x = VIEWPORT_MAX;
    (clipPolygon+3)->y = VIEWPORT_MIN;
    for(int i = 0; i < 4; i++){
        vertex *tmp = vp;
        for(i = 0; i < points; i++){
            //clear points out of original polygon
            (vp+i)->x = 0;
            (vp+i)->y = 0;
        }
        //use inpoints for #points
        vertex S = {(tmp+points-1)->x, (tmp+points-1)->y, (tmp+points-1)->z, (tmp+points-1)->w};
        for(int i = 0; i < points; i++){
            if( (tmp+i)->x > (clipPolygon+0)->x && (tmp+i)->y > (clipPolygon+0)->y &&
                    (tmp+i)->x > (clipPolygon+1)->x && (tmp+i)->y < (clipPolygon+1)->y &&
                    (tmp+i)->x < (clipPolygon+1)->x && (tmp+i)->y < (clipPolygon+1)->y &&
                    (tmp+i)->x < (clipPolygon+1)->x && (tmp+i)->y > (clipPolygon+1)->y){
                if( S.x < (clipPolygon+0)->x || S.y < (clipPolygon+0)->y ||
                        S.x < (clipPolygon+1)->x || S.y > (clipPolygon+1)->y ||
                        S.x > (clipPolygon+1)->x || S.y > (clipPolygon+1)->y ||
                        S.x > (clipPolygon+1)->x || S.y < (clipPolygon+1)->y){
                    //outputList.add(ComputeIntersection(S,E,clipEdge));
                }
            }
        }
    }
}*/

// From Foley et al., Introduction to Computer Graphics, Prog 3.7

void swap(float x, float y){
    float tmp;
    x = tmp;
    x = y;
    y = tmp;
}

void midpointline(float x1,float y1,float x2,float y2, int value){
	float dx,dy,d,incry,incre,incrne,slopegt1=0;
	dx=abs(x1-x2);dy=abs(y1-y2);
	if(dy>dx)
	{
        swap(x1,y1);
        swap(x2,y2);
        swap(dx,dy);
		slopegt1=1;
	}
	if(x1>x2)
	{
        swap(x1,x2);
        swap(y1,y2);
	}
	if(y1>y2)
		incry=-1;
	else
		incry=1;
	d=2*dy-dx;
	incre=2*dy;
	incrne=2*(dy-dx);
	while(x1<x2)
	{
		if(d<=0)
			d+=incre;
		else
		{
			d+=incrne;
			y1+=incry;
		}
		x1++;
		//if(slopegt1)
		//	putpixel(y1,x1,WHITE);
		//else
		//	putpixel(x1,y1,WHITE);
	}
}


outcode CompOutCode(float x, float y,
				    float xmin, float xmax, float ymin, float ymax)
{
	outcode code;
	code.top = 0, code.bottom = 0, code.right = 0, code.left = 0, code.all = 0;
	if (y > ymax) {
		code.top = 8;
		code.all += code.top;
	} else if(y < ymin) {
		code.bottom = 4;
		code.all += code.bottom;
	}
	if (x > xmax) {
		code.right = 2;
		code.all += code.right;
	} else if(x < xmin) {
		code.left = 1;
		code.all += code.left;
	}
	return code;
}


void CHClip(/*float x0, float y0, float x1, float y1,*/ float *vp, int vpts,
				float xmin, float xmax, float ymin, float ymax, int value)
/* Cohen-Sutherland clipping algorithm for line P0=(x0, y0) to P1=(x1,y1) and */
/* clip rectangle with diagonal from (xmin, ymin) to (xmax, ymax) */
{
    float x0, y0, x1, y1;
    for (int i=0;i<vpts;i++)
    {
    
        x0= *(vp+(i*4)+0);
        y0= *(vp+(i*4)+1);
        x1= *(vp+(i*4)+4);
        y1= *(vp+(i*4)+5);
        i+=8;
    }

	bool accept, done;
	outcode outcode0, outcode1, outcodeOut;
	float x, y;

	accept = false;
	done = false;
	outcode0 = CompOutCode(x0, y0, xmin, xmax, ymin, ymax);
	outcode1 = CompOutCode(x1, y1, xmin, xmax, ymin, ymax);
	do {
		if (outcode0.all == 0 && outcode1.all == 0) {
			accept = true;
			done = true;
		} else if((outcode0.all & outcode1.all) != 0)
			done = true;	/* Logical intersection is true,so trivial reject and exit */
		else {
			if (outcode0.all != 0)
				outcodeOut = outcode0;
			else
				outcodeOut = outcode1;
			if (outcodeOut.top) {			/* Divide line at top of clip rectangle */
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if(outcodeOut.bottom) {	/* Divide line at bottom of clip rectangle */
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if(outcodeOut.right) {	/* Divide line at right edge of clip rectangle */
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if(outcodeOut.left) {	/* Divide line at left edge of clip rectangle */
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}
			if (outcodeOut.all == outcode0.all) {
				x0 = x;
				y0 = y;
				outcode0 = CompOutCode(x0, y0, xmin, xmax, ymin, ymax);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = CompOutCode(x1, y1, xmin, xmax, ymin, ymax);
			}
		}						/* Subdivide */
	} while (!done);
	if (accept)
        midpointline(x0, y0, x1, y1, value);		/* Version for float coordinates */
    for (int i=0;i<vpts;i++){
        *(vp+(i*4)+0) = x0;
        *(vp+(i*4)+1) = y0;
        *(vp+(i*4)+4) = x1;
        *(vp+(i*4)+5) = y1;
        i+=8;
    }

}

