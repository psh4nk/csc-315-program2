#    // Perform the rotation operation
    //buildRotateZ( SPIN, TM );
    //applyTransformation( vp, vpts, TM );

#include "tessellate.c"

// From Foley et al., Introduction to Computer Graphics, Prog 3.9

//typedef vertex edge[2];
typedef vertex vertexArray[MAX];    /* MAX is a declared constant */

void Intersect(vertex first, vertex second, vertex *clipBoundary,
        vertex *intersectPt){
    /*if (clipBoundary[0].y == clipBoundary[1].y) {       //horizontal
        intersectPt->y = clipBoundary[0].y;
        intersectPt->x = first.x + (clipBoundary[0].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } else {                                            //vertical
        intersectPt->x = clipBoundary[0].x;
        intersectPt->y = first.y + (clipBoundary[0].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }
    
    if (clipBoundary[0].y == clipBoundary[1].y) {       //horizontal
        intersectPt->y = clipBoundary[0].y;
        intersectPt->x = first.x + (clipBoundary[0].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } 
    else if(clipBoundary[0].x == clipBoundary[1].x){                                            //vertical
        intersectPt->x = clipBoundary[0].x;
        intersectPt->y = first.y + (clipBoundary[0].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }*/
    
    
    
    if (clipBoundary[3].y == clipBoundary[0].y) {       //horizontal
        intersectPt->y = clipBoundary[3].y;
        intersectPt->x = first.x + (clipBoundary[3].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } 
    if(clipBoundary[3].x == clipBoundary[0].x){                                            //vertical
        intersectPt->x = clipBoundary[3].x;
        intersectPt->y = first.y + (clipBoundary[3].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }
    if (clipBoundary[0].y == clipBoundary[1].y) {       //horizontal
        intersectPt->y = clipBoundary[0].y;
        intersectPt->x = first.x + (clipBoundary[0].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } 
    if(clipBoundary[0].x == clipBoundary[1].x){                                            //vertical
        intersectPt->x = clipBoundary[0].x;
        intersectPt->y = first.y + (clipBoundary[0].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }
    if (clipBoundary[1].y == clipBoundary[2].y) {       //horizontal
        intersectPt->y = clipBoundary[1].y;
        intersectPt->x = first.x + (clipBoundary[1].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } 
    if(clipBoundary[1].x == clipBoundary[2].x){                                            //vertical
        intersectPt->x = clipBoundary[1].x;
        intersectPt->y = first.y + (clipBoundary[1].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }
    if (clipBoundary[2].y == clipBoundary[3].y) {       //horizontal
        intersectPt->y = clipBoundary[2].y;
        intersectPt->x = first.x + (clipBoundary[2].y - first.y) *
            (second.x - first.x) / (second.y - first.y);
    } 
    if(clipBoundary[2].x == clipBoundary[3].x){                                            //vertical
        intersectPt->x = clipBoundary[2].x;
        intersectPt->y = first.y + (clipBoundary[2].x - first.x) *
            (second.y - first.y) / (second.x - first.x);
    }
}

bool Inside(vertex testVertex, vertex *clipBoundary){
    
    // check bottom border of window
    if (clipBoundary[0].x > clipBoundary[3].x)  //bottom
        if (testVertex.y >= clipBoundary[3].y)
            return true;
    if (clipBoundary[0].x < clipBoundary[3].x)  //top
        if (testVertex.y <= clipBoundary[3].y)
            return true;
    if (clipBoundary[0].y > clipBoundary[3].y)  //right
        if (testVertex.x <= clipBoundary[0].x)
            return true;
    if (clipBoundary[0].y < clipBoundary[3].y)  //left
        if (testVertex.x >= clipBoundary[0].x)
            return true;

    // check left border of window
    if (clipBoundary[1].x > clipBoundary[0].x)  //bottom
        if (testVertex.y >= clipBoundary[0].y)
            return true;
    if (clipBoundary[1].x < clipBoundary[0].x)  //top
        if (testVertex.y <= clipBoundary[0].y)
            return true;
    if (clipBoundary[1].y > clipBoundary[0].y)  //right
        if (testVertex.x <= clipBoundary[1].x)
            return true;
    if (clipBoundary[1].y < clipBoundary[0].y)  //left
        if (testVertex.x >= clipBoundary[1].x)
            return true;
    
    // check top border of window
    if (clipBoundary[2].x > clipBoundary[1].x)  //bottom
        if (testVertex.y >= clipBoundary[1].y)
            return true;
    if (clipBoundary[2].x < clipBoundary[1].x)  //top
        if (testVertex.y <= clipBoundary[1].y)
            return true;
    if (clipBoundary[2].y > clipBoundary[1].y)  //right
        if (testVertex.x <= clipBoundary[2].x)
            return true;
    if (clipBoundary[2].y < clipBoundary[1].y)  //left
        if (testVertex.x >= clipBoundary[2].x)
            return true;
    
    // check right border of window
    if (clipBoundary[3].x > clipBoundary[2].x)  //bottom
        if (testVertex.y >= clipBoundary[2].y)
            return true;
    if (clipBoundary[3].x < clipBoundary[2].x)  //top
        if (testVertex.y <= clipBoundary[2].y)
            return true;
    if (clipBoundary[3].y > clipBoundary[2].y)  //right
        if (testVertex.x <= clipBoundary[3].x)
            return true;
    if (clipBoundary[3].y < clipBoundary[2].y)  //left
        if (testVertex.x >= clipBoundary[3].x)
            return true; 
    return false;
}

void Output(vertex newVertex, int outLength, vertex *outVertexArray){
    outLength++;
    outVertexArray[outLength - 1].x = newVertex.x;
    outVertexArray[outLength - 1].y = newVertex.y;
}

void SutherlandHodgmanPolygonClip(vertex *inVertexArray,
        vertex *outVertexArray, int inLength, int outLength, vertex *clip_boundary){
    vertex s, p, i;
    int j;

    outLength = 0;
    s = inVertexArray[inLength - 1];    /* Start with the last vertex in inVertexArray */
    for (j = 0; j < inLength; j++) {
        p = inVertexArray[j];   /* Now s and p correspond to the vertices in Fig.3.33 */
        if (Inside(p, clip_boundary)) { /* Cases 1 and 4 */
            if (Inside(s, clip_boundary))
                Output(p, outLength, outVertexArray);   /* Case 1 */
            else {                      /* Case 4 */
                Intersect(s, p, clip_boundary, &i);
                Output(i, outLength, outVertexArray);
                Output(p, outLength, outVertexArray);
            }
        } else if(Inside(s, clip_boundary)) {           /* Cases 2 and 3 */
            Intersect(s, p, clip_boundary, &i);     /* Case 2 */
            Output(i, outLength, outVertexArray);
        }                           /* No action for case 3 */
        s = p;                  /* Advance to next pair of vertices */
    }
}
