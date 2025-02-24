    //
    // Created by kai on 2/14/25.
    //

    #ifndef CONVEXHULL_H
    #define CONVEXHULL_H
    #include <vector>
    #include <cmath>
    #include <limits>
    #include <string>
    #include <matplot/matplot.h>

enum class Method {
        NAIVE,
        GRAHAM,
    };

    struct point {
        point(const double _x , const double _y) : x(_x), y(_y) {};
        point() : x(0), y(0) {};

        bool operator==(const point& other) const {
            return x == other.x && y == other.y;
        }
        double x,y;

    };

    // struct segment {
    //     segment(const point _a, const point _b) : a(_a), b(_b) {};
    //     point a,b;
    // };

    struct PointHash {
        std::size_t operator()(const point& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
    class ConvexHull{
        public:
            ConvexHull(std::vector<point> points);
            void findHull(Method function);
            void displayHull(const std::string &outPath, double xmin=0, double xmax=100, double ymin=0, double ymax=100);
            std::vector<point> points;
            std::vector<point> hullPoints;
        private:
            void remove_duplicates(std::vector<point>& points);
            void naive_hull();
            void graham_scan();
    };

std::string pointToDesmos(std::vector<point> points);

namespace Utils {
    bool leftOf(point A, point B, point C);
    static double slope(point A,point B);
    bool angularCompare(const point& a, const point& b, const point& c);
    std::pair<double,double> computeAngle(const point& a, const point& b, const point& c);
    std::vector<point> generatePointSet(int size, int xMin=0, int xMax=1, bool circular = false);
    point * constructPolygon(std::vector<point> &points);
}

    #endif //CONVEXHULL_H
    