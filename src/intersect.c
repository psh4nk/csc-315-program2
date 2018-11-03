#include "move.c"


int isccw(float x1, float y1, float x2, float y2, float x3, float y3){
    // check if vertices are counter clockwise winding
    int value = 0;
    float z = ((x1 - x2 ) * ( y3 - y2 ) - ( y1 - y2 ) * ( x3 - x2 ));
    if(z < 0)
        value = 1;
    else
        value = 0;
    return value;
}

int checkintersection(coords pos, vertex *vp, int points){
    // Check if the new vertex can make a line that intersects with any of the preceding vertices.
    // Returns 1 if no intersection, 0 if there is an intersection

    int value = 0;
    for(int i = 0; i < points; i++){
        float x1 = (vp+i)->x, y1 = (vp+i)->y, x2 = (vp+i+1)->x, y2 = (vp+i+1)->y,
               x3 = (vp+i+2)->x, y3 = (vp+i+2)->y, x4 = (float)pos.x, y4 = (float)pos.y;
        float denom = (((x2 - x1)* -1*(y4-y3) - -1*(x4-x3)*(y2-y1)));
        float ua, ub;

        if(denom != 0.0){
            // calcluate ua and ub in order to check for intersection
            ua = ((((x3-x1)*-1*(y4-y3)- -1*(x4-x3)*(y3-y1))/denom));
            ub = ((((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/denom));
            if((ua > 0.0 && ua < 1.0) && (ub > 0.0 && ub < 1.0)){
                value = 0;
            }
            else{
                value = 1;
                if(isccw((vp+i)->x, (vp+i)->y, (vp+i+1)->x, (vp+i+1)->y, (vp+i+2)->x, (vp+i+2)->y) == 1){
                    // check if vertices are ccw while checking if they intersect
                    // if ccw and no intersection, the vertices are added to the triangle list
                    triangle t = {{(float) vp[i].x, (float) vp[i].y}, {(float) vp[i+1].x, vp[i+1].y}, {(float) vp[i+2].x, (float) vp[i+2].y}};
                    triangles.push_back(t);
                }

            }
        }
        else    // denom = 0, so intersection does not occur.
            value = 1;
    }
    return value;
}

