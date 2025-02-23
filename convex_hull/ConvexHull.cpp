//
// Created by kai on 2/14/25.
//

#include "ConvexHull.h"

#include <iostream>
#include <ostream>
#include <ranges>
#include <unordered_set>


ConvexHull::ConvexHull(std::vector<point> points) {
    this->points = points;
}

/**
 * @brief computes slope between two points
 *
 * @param A point
 * @param B point
 * @return slope between A,B
 */
double Utils::slope(point A, point B) {
    // need to check if x == x
    if (A.x == B.x) {
        return __builtin_inf();
    }
    return ((A.y - B.y)/(A.x - B.x));
}

/**
 * @brief performs left of test on point C using linesegment AB
 *
 * @param A line segment
 * @param B line segment
 * @param C target of the test
 * @return C is left of AB
 */

bool Utils::leftOf(point A, point B, point C) {
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
    // double cross = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    // return cross > 0;  // Positive means C is to the left of AB
}

/**
 *
 * @brief run naive convex hull algorithim
 *
 * mutates hullSegements outputting a convex hull based on this->points
 */
void ConvexHull::naive_hull() {
    for (int A = 0; A < points.size(); A++) {
        for (int B = 0; B < points.size(); B++) {
            bool allLeftOf = true;
            if (A == B) continue;
            for (int C = 0; C < points.size(); C++) {
                bool isLeftOf = Utils::leftOf(points[A],points[B],points[C]);
                if (B!=C && C!=A && !isLeftOf) {
                    allLeftOf = false;
                    break;
                }
            }
            if (allLeftOf) {
                hullSegments.emplace_back(points[A], points[B]);
                hullPoints.push_back(points[A]);
                hullPoints.push_back(points[B]);
            }
        }
    }
   // remove_hullPoint_duplicates();
}


void ConvexHull::remove_hullPoint_duplicates() {
    std::unordered_set<point,PointHash> hullSet;
    std::vector<point> temp_vector;
    for (auto & pt : hullPoints) {
        if (!hullSet.contains(pt)) {
            hullSet.insert(pt);
            temp_vector.push_back(pt);
        }
    }
    this->hullPoints = temp_vector;
};

void ConvexHull::displayHull(std::string outPath) {
    for (const auto &a : this->hullSegments) {
        std::cout << a.a.x << " " << a.a.y << "," << a.b.x  << " " <<a.b.y << std::endl;
    }
}


void ConvexHull::findHull(Method function) {
    switch (function) {
    case Method::NAIVE:
        this->naive_hull();
        break;

    case Method::GRAHAM:
        // ConvexHull::graham_scan();
            break;
    }
}

/**
 *@brief export points in a desmos compatible format (for testing)
 *
 * @param points
 * @return
 */
std::string pointToDesmos(std::vector<point> points) {
    std::string out;

    out = "[";
    for (auto & pt : points) {
        out += "(" +std::to_string(pt.x) + "," + std::to_string(pt.y) +"),";
    }
    out.pop_back();
    out += "]";
    return out;
}
