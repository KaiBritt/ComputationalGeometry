    //
    // Created by kai on 2/14/25.
    //

    #ifndef CONVEXHULL_H
    #define CONVEXHULL_H
    #include <vector>
    #include <cmath>
    #include <limits>
    #include <string>

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

    struct segment {
        segment(const point _a, const point _b) : a(_a), b(_b) {};
        point a,b;
    };

    struct PointHash {
        std::size_t operator()(const point& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
    class ConvexHull{
        public:
            ConvexHull(std::vector<point> points);
            void findHull(Method function);
            void displayHull(std::string outPath);
            std::vector<point> points;
            std::vector<point> hullPoints;
            std::vector<segment> hullSegments;
        private:
            void remove_hullPoint_duplicates();
            void naive_hull();
            void graham_scan();
    };

std::string pointToDesmos(std::vector<point> points);

namespace Utils {
    bool leftOf(point A, point B, point C);
    static double slope(point A,point B);
}

#endif //CONVEXHULL_H
    