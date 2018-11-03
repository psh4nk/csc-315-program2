#include "tessellate.c"

void clip(struct vertex *vp, int points){
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
}
