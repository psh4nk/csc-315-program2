#include "transform.c"


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

int checkintersection(float* vp, int points){
    // Check if the new vertex can make a line that intersects with any of the preceding vertices.
    // Returns 1 if no intersection, 0 if there is an intersection

    int value = 0;
    for(int i = 0; i < points; i+=4){
        float x1 = *((vp+i)+0), y1 = *((vp+i)+1), x2 = *((vp+i+1)+0), y2 = *((vp+i+1)+1),
               x3 = *((vp+i+2)+0), y3 = *((vp+i+2)+1), x4 = *((vp+i+3)+0), y4 = *((vp+i+3)+1);
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
                if(isccw(*((vp+i)+0), *((vp+i)+1), *((vp+i+1)+0), *((vp+i+1)+1), *((vp+i+2)+0), *((vp+i+2)+1)) == 1){
                    // check if vertices are ccw while checking if they intersect
                    // if ccw and no intersection, the vertices are added to the triangle list
                    triangle t = {{ *((vp+i)+0), *((vp+i)+1)}, { *((vp+i+1)+0), *((vp+i+1)+1)}, { *((vp+i+2)+0), *((vp+i+2)+1)}};
                    triangles.push_back(t);
                }
            }
        }
        else    // denom = 0, so intersection does not occur.
            value = 1;
    }
    return value;
    
    
    /*glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i < points; i++){
            glVertex2f((*(vp+i*4)+0), (*(vp+i*4)+1));
        }
    glEnd();
    */
}

