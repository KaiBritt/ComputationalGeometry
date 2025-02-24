//
// Created by kai on 2/23/25.
//

#include "ConvexHull.h"
#include <gtest/gtest.h>
#include  <random>
#include <ctime>
#include <chrono>

TEST(LeftOfTests, verticalLine) {
    EXPECT_EQ(Utils::leftOf(point(0,0), point(0,1), point(-0.5,.5)),true);
}

TEST(ComputeAngle,ninety) {
    EXPECT_EQ(abs(Utils::computeAngle({-1,0},{0,0},{0,1}).first - std::numbers::pi/2) < 1e9,true);
}

TEST(AngularCompare, colinearPoints) {
    // EXPECT_EQ(Utils::angularCompare({0,0},{2,2},{3,3}),true);
    EXPECT_EQ(Utils::angularCompare({0,0},{3,3},{3,3.000003}),false);
    EXPECT_EQ(Utils::angularCompare({0,0},{0,1},{1,1}),true);
}


TEST(AngluarSorting, points) {
    std::vector<point> points =  {{0,0},{0,1},{1,0},{-1,0}};
    ConvexHull simple = ConvexHull(points);
    simple.findHull(Method::GRAHAM);
    for (const auto & p:simple.hullPoints) {
        std::cout << p.x << ", " << p.y << std::endl;
    }
}

TEST(GrahamScan, colinearInnerVertex) {
    std::vector<point> points =  {{4,4},{4,0},{0,0},{2,2},{0,4}};
    ConvexHull simple = ConvexHull(points);
    simple.findHull(Method::GRAHAM);
    for (const auto & p:simple.hullPoints) {
        std::cout << p.x << ", " << p.y << std::endl;
    }
    // simple.displayHull("figures/ColinearInnerVertex.png",-1, 5, -1,5);
}

TEST(GrahamScan, colinearOnHull) {
    std::vector<point> points =  {{4,0},{0,0},{2,2},{0.6,3.4},{3.1,0.9},{0,4},{2,1},{1.5,2.5},{1.4,2.5}};
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(points), std::end(points), rng);
    ConvexHull simple = ConvexHull(points);

    simple.findHull(Method::GRAHAM);
    for (const auto & p:simple.hullPoints) {
        std::cout << "(" <<  p.x << ", " << p.y <<  ")" << std::endl;
    }
    // simple.displayHull("figures/colinearOnHull.png",-1, 5, -1,5);

}

TEST(GrahamScan, degenerate) {
    std::vector<point> points =  {{4,0},{0,0}};
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(points), std::end(points), rng);
    ConvexHull simple = ConvexHull(points);

    simple.findHull(Method::GRAHAM);
    for (const auto & p:simple.hullPoints) {
        std::cout << "(" <<  p.x << ", " << p.y <<  ")" << std::endl;
    }
    // simple.displayHull("figures/degenerate.png",-1, 5, -1,5);

}



TEST(Timing,hundred) {
std::vector<point>  points = Utils::generatePointSet(100, 0,100);
    ConvexHull hull = ConvexHull(points);
    std::time_t start = std::time(nullptr);
    hull.findHull(Method::GRAHAM);
    std::time_t end = std::time(nullptr);
    std::cout << "Grham took : " << end - start << std::endl;

    start = std::time(nullptr);
    hull.findHull(Method::NAIVE);
    end = std::time(nullptr);
    std::cout << "Naive took : " << end - start << std::endl;
}

TEST(Timing,thousand) {
    std::vector<point>  points = Utils::generatePointSet(1000, 0,1000);
    ConvexHull hull = ConvexHull(points);
    std::time_t start = std::time(nullptr);
    hull.findHull(Method::GRAHAM);
    std::time_t end = std::time(nullptr);
    std::cout << "Grham took : " << end - start << std::endl;

    start = std::time(nullptr);
    hull.findHull(Method::NAIVE);
    end = std::time(nullptr);
    std::cout << "Naive took : " << end - start << std::endl;
}

TEST(Timing,tenThousand) {
    std::vector<point>  points = Utils::generatePointSet(10000, 0,1000);
    ConvexHull hull = ConvexHull(points);
    std::time_t start = std::time(nullptr);
    hull.findHull(Method::GRAHAM);
    std::time_t end = std::time(nullptr);
    std::cout << "Grham took : " << end - start << std::endl;

    start = std::time(nullptr);
    hull.findHull(Method::NAIVE);
    end = std::time(nullptr);
    std::cout << "Naive took : " << end - start << std::endl;

}

TEST(Timing,hundredThousand) {
    std::vector<point>  points = Utils::generatePointSet(10000, 0,1000);
    ConvexHull hull = ConvexHull(points);
    std::time_t start = std::time(nullptr);
    hull.findHull(Method::GRAHAM);
    std::time_t end = std::time(nullptr);
    std::cout << "Grham took : " << end - start << std::endl;

    start = std::time(nullptr);
    hull.findHull(Method::NAIVE);
    end = std::time(nullptr);
    std::cout << "Naive took : " << end - start << std::endl;

}


