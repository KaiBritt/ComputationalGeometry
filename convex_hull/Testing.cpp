#include <iostream>
#include <gtest/gtest.h>
#include "ConvexHull.h"
#include <random>
#include <matplot/matplot.h>
// #include <>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


std::vector<point> generatePointSet(int size, int xMin=0, int xMax=1, int yMin=0, int yMax=1) {
    std::vector<point> points;
    std::random_device rd;   // Obtain a random seed
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    // Define the range [1, 100]
    std::uniform_real_distribution<double> dist(1.0, 100.0);


    for (int i = 0; i < size; i++) {
        points.emplace_back(dist(gen),dist(gen));
    }
    return points;
}

int main() {
    std::cout << __cplusplus;
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    std::cout << "i = " << Utils::leftOf(point(0,0), point(0,1), point(-0,.5)) << std::endl;
    std::vector<point> points = {point(0,0), point(0,1), point(-0.5,.5), point(-0.24    ,.25)};
    std::vector<point> randomPts = generatePointSet(1000, 0,100,0,100);

    ConvexHull convexHull(randomPts);
    convexHull.findHull(Method::NAIVE);
    convexHull.displayHull("temps");
    std::cout << pointToDesmos(convexHull.points) << std::endl;
    std::cout << pointToDesmos(convexHull.hullPoints) << std::endl;
    using namespace matplot;
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y = transform(x, [](auto x) { return sin(x); });

    // plot(x, y, "-o");
    // hold(on);
    // plot(x, transform(y, [](auto y) { return -y; }), "--xr");
    // plot(x, transform(x, [](auto x) { return x / pi - 1.; }), "-:gs");
    // plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");
    //
    // show();

    return 0;
}
// TEST(LeftOfTests, verticalLine) {
// #include "ConvexHull.h"
//     EXPECT_EQ(Utils::leftOf(point(0,0), point(0,1), point(-0.5,.5)),true);
// }

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.