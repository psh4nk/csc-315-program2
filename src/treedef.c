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

    // define window boundaries
    vertex left[2],top[2],right[2],bottom[2];

    left[0] = {100,900,0,1};
    left[1] = {100,100,0,1};
    top[0] = {900,900,0,1};
    top[1] = {100,900,0,1};
    right[0] = {900,100,0,1};
    right[1] = {900,900,0,1};
    bottom[0] = {100,100,0,1};
    bottom[1] = {900,100,0,1};



    int i;
    int* outLength;
    outLength = &i;
    vertex *temp=vp;
    SutherlandHodgmanPolygonClip(vp,temp,points,outLength,left);
    SutherlandHodgmanPolygonClip(vp,temp,points,outLength,bottom);
    SutherlandHodgmanPolygonClip(vp,temp,points,outLength,right); 
    SutherlandHodgmanPolygonClip(vp,temp,points,outLength,top);

    glBegin(GL_LINE_LOOP);
    for (int i=0;i<*outLength;i++){
        glVertex2f( (temp+i)->x, (temp+i)->y ); 
    }
    glEnd();
}

void fillTree(){
    //tesselation goes here
    //glBegin(GL_POLYGON);
    //for(int i = 0; i < tree.size(); i++)
    //    glVertex2f(tree[i].x, tree[i].y);
    //glEnd();
}                               
