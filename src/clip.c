// From Foley et al., Introduction to Computer Graphics, Prog 3.9

#include "tessellate.c"

void Intersect(vertex first, vertex second, vertex *clipBoundary, vertex *intersectPt){
    // Finds the point of intersection 
    
    float m;
    vertex temp;
    if(first.x != second.x)
        m = (first.y - second.y) / (first.x - second.x); 

    if (clipBoundary[0].x == VIEWPORT_MIN && clipBoundary[1].x == VIEWPORT_MIN) {   //left
        intersectPt->x = clipBoundary[0].x;
        intersectPt->y = second.y + (clipBoundary[0].x - second.x) * m;
    } 
    if(clipBoundary[0].x == VIEWPORT_MAX && clipBoundary[1].x == VIEWPORT_MAX){     //right
        intersectPt->x = clipBoundary[1].x;
        intersectPt->y = second.y + (clipBoundary[1].x - second.x) * m;
    }
    if(clipBoundary[0].y == VIEWPORT_MIN && clipBoundary[1].y == VIEWPORT_MIN){     // bottom
        intersectPt->y = clipBoundary[0].y;
        if(first.x != second.x)
            intersectPt->x = second.x + (clipBoundary[0].y - second.y) / m;
        else
            intersectPt->x = second.x;
    }
    if(clipBoundary[0].y == VIEWPORT_MAX && clipBoundary[1].y == VIEWPORT_MAX){     //top  
        intersectPt->y = clipBoundary[1].y;
        if(first.x != second.x)
            intersectPt->x = second.x + (clipBoundary[1].y - second.y) / m;
        else
            intersectPt->x = second.x;
    } 

}

bool Inside(vertex testVertex, vertex *clipBoundary){
    // Checks if a given vertex is inside the viewport
    
    if (clipBoundary[1].x > clipBoundary[0].x)  /*bottom*/
        if (testVertex.y >= clipBoundary[0].y)
            return true;
    if (clipBoundary[1].x < clipBoundary[0].x)  /*top*/
        if (testVertex.y <= clipBoundary[0].y)
            return true;
    if (clipBoundary[1].y > clipBoundary[0].y)  /*right*/
        if (testVertex.x <= clipBoundary[1].x)
            return true;
    if (clipBoundary[1].y < clipBoundary[0].y)  /*left*/
        if (testVertex.x >= clipBoundary[1].x)
            return true;
    return false;
}

void Output(vertex newVertex, int *outLength, vertex *outVertexArray){
    (*outLength)++;
    outVertexArray[*outLength-1].x = newVertex.x;
    outVertexArray[*outLength-1].y = newVertex.y;
}

void SutherlandHodgmanPolygonClip(vertex *inVertexArray, vertex *outVertexArray, int inLength, int *outLength, vertex *clip_boundary){
    vertex s, p, i;
    int j;

    *outLength = 0;
    s = inVertexArray[inLength-1];    /* Start with the last vertex in inVertexArray */
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

