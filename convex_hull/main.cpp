#include <iostream>
#include "ConvexHull.h"
#include <random>
// #include <>



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