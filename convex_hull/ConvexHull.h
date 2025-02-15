    //
    // Created by kai on 2/14/25.
    //

    #ifndef CONVEXHULL_H
    #define CONVEXHULL_H
    #include <vector>
    #include <cmath>
    #include <limits>

enum class Method {
        NAIVE,
        GRAHAM,
    };

    struct point {
        point(const double _x , const double _y) : x(_x), y(_y) {};
        double x,y;
    };

    struct segment {
        segment(const point _a, const point _b) : a(_a), b(_b) {};
        point a,b;
    };

    class ConvexHull{
        public:
            ConvexHull();
            void findHull(Method function);
            void displayHull();
            std::vector<point> points;
            std::vector<point> hullPoints;
            std::vector<segment> hullSegments;

        private:
            static bool leftOf(point A, point B, point C);
            static double slope(point A,point B);
            void naive_hull();
            void graham_scan();
    };



    #endif //CONVEXHULL_H
