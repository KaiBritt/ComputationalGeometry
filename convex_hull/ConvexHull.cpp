//
// Created by kai on 2/14/25.
//

#include "ConvexHull.h"

#include <ranges>


/**
 * @brief computes slope between two points
 *
 * @param A point
 * @param B point
 * @return slope between A,B
 */
double ConvexHull::slope(point A, point B) {
    // need to check if x == x
    if (A.x == B.x) {
        return __builtin_inf();
    }
    return (A.y - B.y/(A.x - B.x));
}

/**
 * @brief performs left of test on point C using linesegment AB
 *
 * @param A line segment
 * @param B line segment
 * @param C target of the test
 * @return C is left of AB
 */

bool ConvexHull::leftOf(point A, point B, point C) {
    // Calculate the line function given AB
    double m = slope(A,B);
    double pointOnLine = m * (C.x - A.x) + A.y;


    //vertical line
    if  (std::isinf(m)) {
        if (A.y > B.y) { // directed line is going down
            return C.x >  A.x;
        }
        return C.x < A.x;
    }
    // TWO Cases line is left to right or right to left,

    // left to right
    if ((m > 0 && C.y > pointOnLine || m < 0 && C.y < pointOnLine) && A.x < B.x)
        return true;

    //right to left
    if ((m > 0 && C.y < pointOnLine || m < 0 && C.y > pointOnLine) && A.x > B.x)
        return true;

    return false;
}

/**
 *
 * @brief run naive convex hull algorithim
 *
 * mutates hullSegements outputing a connvex hull based on this->points
 */
void ConvexHull::naive_hull() {
    for (int A = 0; A < points.size(); A++) {
        for (int B = A; B < points.size(); B++) {
            bool allLeftOf = true;
            for (int C = 0; C < points.size(); C++) {
                if ( B!=A and C!=A && !leftOf(points[A],points[B],points[C])) {
                    allLeftOf = false;
                }
            }
            if (allLeftOf) {
                hullSegments.emplace_back(points[A], points[B]);
            }
        }
    }
}


void ConvexHull::findHull(Method function) {
    switch (function) {
    case Method::NAIVE:
        ConvexHull::naive_hull();
        break;

    case Method::GRAHAM:
        ConvexHull::graham_scan();
        break;
    }
}


