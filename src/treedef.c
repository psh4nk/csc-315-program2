#include "pipeline.c"
#include "includes.h"

void defineTree( float *apts ){

    float r = 200;
    float x,y;
    float TPI = 2 * M_PI;

    if(count == 0){
        count++;
        tree.push_back({200,600,0,1});
        tree.push_back({725,550,0,1});
        for (float i = 0.0; i <= TPI / 2; i += 0.001){
            x = (sin(i)*r)+650;
            y = (cos(i)*r)+500;
            tree.push_back({x,y,0,1});
        }
        tree.push_back({725,450,0,1});
        tree.push_back({200,400,0,1});
    }

    int vertmin = 0;
    for(int i = 0; i < tree.size(); i++){
        apts[vertmin] = tree[i].x;
        apts[vertmin+1] = tree[i].y;
        apts[vertmin+2] = tree[i].z;
        apts[vertmin+3] = tree[i].w;
        vertmin+=4;
    }
}

void toVertex ( float *apts, struct vertex *vp, int pts ){
    int i;

    for (i=0;i<pts;i++)
    {
        (vp+i)->x = *(apts+(i*4)+0);
        (vp+i)->y = *(apts+(i*4)+1);
        (vp+i)->z = *(apts+(i*4)+2);
        (vp+i)->w = *(apts+(i+4)+3);
    }
}


void drawTree( vertex *vp, int points ){
    vertex bounds[4];
    vertex *temp = &bounds[0];
    bounds[0] = {100,100,0,1};
    bounds[1] = {100,900,0,1};
    bounds[2] = {900,900,0,1};
    bounds[3] = {900,100,0,1}; 
    vertex outVertexArray[points];
    vertex *point = &outVertexArray[0];
    int *outLength; 
    *outLength = points*2;
    SutherlandHodgmanPolygonClip(vp,outVertexArray,points,outLength,bounds);
     
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<points;i++)
        glVertex2f( (outVertexArray+i)->x, (outVertexArray+i)->y );
    glEnd();
}

void fillTree(){
    //tesselation goes here
    //glBegin(GL_POLYGON);
    //for(int i = 0; i < tree.size(); i++)
    //    glVertex2f(tree[i].x, tree[i].y);
    //glEnd();
}                               
