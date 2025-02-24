//
// Created by kai on 2/14/25.
//

#include "ConvexHull.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <ranges>
#include <unordered_set>
#include <cmath>
#include <assert.h>
#include <bits/random.h>
#include <random>



std::vector<point> Utils::generatePointSet(int size, int xMin, int xMax, bool circular) {
    std::vector<point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(xMin, xMax);

    for (int i = 0; i < size; i++) {
        if (circular) {
            double t = dist(gen);
            points.emplace_back(double(xMax) * cos(t),double(xMax) * sin(t));
        }
        else {
            points.emplace_back(dist(gen),dist(gen));
        }
    }
    return points;
}

double crossProduct(const point& a, const point& b, const point& c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
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

}


bool compareByX(const point& a, const point& b) {
    if (a.x == b.x){
        return a.y < b.y;
    }
    return a.x < b.x;
}

std::pair<double,double> Utils::computeAngle(const point& a, const point& b, const point& c) {

    // point c = point(a.x-1,a.y); // creating a point inline with a to create angel abc
    double dotac = ((a.x - b.x) * (c.x - b.x)) + ((a.y - b.y) * (c.y - b.y));
    double cmag =  sqrt(pow((c.x-b.x),2) + pow((c.y-b.y),2));
    double amag  =  sqrt(pow((a.x-b.x),2) + pow((a.y-b.y),2));
    if (c == b) {
        return {0,std::numeric_limits<double>::infinity()};
    }
    double cosine_theta = std::clamp(dotac / (amag*cmag), -1.0, 1.0);
    double angle = acos(cosine_theta);
    return {angle,cmag};
}

/**
 * @brief function to compare angles dab and dac (d = (a.x-1,a.y))
 * @param a point to comapre with respect to
 * @param b
 * @param c
 * @return
 */
bool Utils::angularCompare(const point& a, const point&b, const point&c) {
    std::pair<double,double> angleB = computeAngle({a.x-1,a.y}, a,b);
    std::pair<double,double> angleC = computeAngle({a.x-1,a.y},a,c);
    //almost equal return the one with bigger magnitude attempt to deal with colinearity
    if (fabs(angleB.first- angleC.first) < 1e-9) {
        return angleB.second > angleC.second;
    }
    return angleB.first < angleC.first;
}


point * Utils::constructPolygon(std::vector<point>& points) {
    point * polygon = new point[points.size()];

    std::sort(points.begin(), points.end(), compareByX);
    const point left_point = points[0];
    const point right_point = points[points.size()-1];
    int l = 1;
    int r =  points.size() - 1;
    polygon[0]=left_point;
    for (int i  = 1; i < points.size(); i++) {
        if (crossProduct(left_point, right_point, points[i])>= 0) {
            polygon[r] = points[i];
            r -= 1;
        }
        else {
            polygon[l]= points[i];
            l += 1;
        }
    }

    return polygon;
}

std::vector<point> removeColinearFromPolygon(std::vector<point>& polygon) {
    if (polygon.size() < 3) return polygon;

    std::vector<point> newPolygon;
    newPolygon.push_back(polygon[0]);

    for (int i = 1; i < polygon.size() - 1; i++) {
        while (i < polygon.size() - 1 && fabs(crossProduct(newPolygon.back(), polygon[i], polygon[i + 1])) <= 1e-9) {
            i++;
        }
        newPolygon.push_back(polygon[i]);
    }
    // chck if last point is colinear
    if (fabs(crossProduct(newPolygon.back(), polygon.back(),polygon[0])) > 1e-9) {
        newPolygon.push_back(polygon.back());
    }
    return newPolygon;
}





ConvexHull::ConvexHull(std::vector<point> points) {
    this->points = points;
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
                double cp = crossProduct(points[A],points[B],points[C]);
                bool isLeftOf =  Utils::leftOf(points[A],points[B],points[C]);

                if (cp != 0 && B!=C && C!=A && !isLeftOf) {
                    allLeftOf = false;
                    break;
                }
            }
            if (allLeftOf) {
                hullPoints.push_back(points[A]);
                hullPoints.push_back(points[B]);
            }
        }
    }
    remove_duplicates(this->hullPoints);
    point * polygon = Utils::constructPolygon(this->hullPoints);
    std::vector<point> vPgon(polygon, polygon + this->hullPoints.size());
    this->hullPoints = removeColinearFromPolygon(vPgon);
;
}


void ConvexHull::graham_scan() {
    //process points

    auto cleanedPoints = points;
    remove_duplicates(cleanedPoints);
    // find lowest point
    point lowest_point = cleanedPoints[0];
    for (int i = 1; i < cleanedPoints.size(); i++) {
        if (cleanedPoints[i].y <= lowest_point.y) {
            if ((fabs(cleanedPoints[i].y - lowest_point.y) < 1e-9 && cleanedPoints[i].x > lowest_point.x)
            || (fabs(cleanedPoints[i].y - lowest_point.y) > 1e-9)){
                lowest_point = cleanedPoints[i];}
        }
    }

     auto fixedAnguluarCompare = [lowest_point](const point &a,const point &b){
        return Utils::angularCompare(lowest_point,a,b);};

    std::sort(cleanedPoints.begin(),cleanedPoints.end(),fixedAnguluarCompare);
    std::reverse(cleanedPoints.begin(),cleanedPoints.end());
    // now sorted angles in descending order, lowest point is at the end of the list remove it now
    hullPoints.push_back(cleanedPoints.back());
    cleanedPoints.pop_back();
    hullPoints.push_back(cleanedPoints[0]);
    cleanedPoints.erase(cleanedPoints.begin());

    point top = hullPoints.back();
    point secondTop = hullPoints[0];
    // std::cout << "size of cleanedPoints: " << cleanedPoints.size()  << "sizof hull points" << hullPoints.size() << std::endl;
    for (int i = 0; i < cleanedPoints.size(); i++) {
        double cp = crossProduct(secondTop,top,cleanedPoints[i]);
        while (cp <= 0 || fabs(cp < 1e-9)) {
            top = secondTop;
            hullPoints.pop_back();
            secondTop = hullPoints[hullPoints.size()-2];
            cp  = crossProduct(secondTop,top,cleanedPoints[i]);
        }
        secondTop = top;
        top = cleanedPoints[i];
        hullPoints.push_back(cleanedPoints[i]);
    }

    }




void ConvexHull::remove_duplicates(std::vector<point>& points) {
    std::unordered_set<point,PointHash> hullSet;
    std::vector<point> temp_vector;
    for (auto & pt : points) {
        if (!hullSet.contains(pt)) {
            hullSet.insert(pt);
            temp_vector.push_back(pt);
        }
    }
    points = temp_vector;
};

void ConvexHull::displayHull(const std::string &outPath,double xmin,double xmax,double ymin,double ymax) {
    point * polygon =  Utils::constructPolygon(this->hullPoints);
    using namespace matplot;
    std::vector<double> hull_x;
    std::vector<double> hull_y;
    std::vector<double> points_x;
    std::vector<double> points_y;
    for (auto point : this->points) {
        points_x.push_back(point.x);
        points_y.push_back(point.y);
    }
    for (auto point : this->hullPoints) {
        hull_x.push_back(point.x);
        hull_y.push_back(point.y);
    }
    hold(on);
    scatter(points_x,points_y)->color("blue").marker_size(2);
    scatter(hull_x,hull_y)->color("red").marker_size(5);
    int hull_size = this->hullPoints.size();
    for (size_t i = 0; i < hull_size;i++) {
        matplot::plot({polygon[i].x, polygon[(i+1)%hull_size].x}, {polygon[i].y, polygon[(i+1)%hull_size].y}, "r-")->line_width(1);
    }
    title(outPath);
    axis( {xmin, xmax, ymin, ymax});
    save(outPath);
    cla();
    delete [] polygon;
}


void ConvexHull::findHull(Method function) {
    switch (function) {
    case Method::NAIVE:
        this->naive_hull();
        break;

    case Method::GRAHAM:
        // ConvexHull::graham_scan();
            this->graham_scan();
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

