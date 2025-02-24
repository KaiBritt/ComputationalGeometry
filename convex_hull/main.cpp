#include <iostream>
#include "ConvexHull.h"
#include <random>
// #include <>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


// std::vector<point> generatePointSet(int size, int xMin=0, int xMax=1, int yMin=0, int yMax=1) {
//     std::vector<point> points;
//     std::random_device rd;   // Obtain a random seed
//     std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
//     // Define the range [1, 100]
//     std::uniform_real_distribution<double> dist(1.0, 100.0);
//
//
//     for (int i = 0; i < size; i++) {
//         points.emplace_back(dist(gen),dist(gen));
//     }
//     return points;
// }


int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    std::cout << "i = " << Utils::leftOf(point(0,0), point(0,1), point(-0,.5)) << std::endl;
    std::vector<point> points = {point(0,0), point(0,1), point(-0.5,.5), point(-0.24    ,.25)};
    std::vector<point> randomPts = Utils::generatePointSet(150, 0,1000,true);

    ConvexHull convexHull(randomPts);
    convexHull.findHull(Method::NAIVE);
    convexHull.displayHull("temps");
    convexHull.displayHull("figures/naiveHull.png",-1005,1005,-1005,1005);
    convexHull.findHull(Method::GRAHAM);
    convexHull.displayHull("figures/grahamHull.png",-1005,1005,-1005,1005);

    randomPts  = Utils::generatePointSet(150, 0,1000, false);
    ConvexHull squareConvexHull(randomPts);
    squareConvexHull.findHull(Method::NAIVE);
    squareConvexHull.displayHull("temps");
    squareConvexHull.displayHull("figures/naiveHullSquare.png",-1005,1005,-1005,1005);
    squareConvexHull.findHull(Method::GRAHAM);
    squareConvexHull.displayHull("figures/grahamHullSquare.png",-1005,1005,-1005,1005);

    return 0;
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.