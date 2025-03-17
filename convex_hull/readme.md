Notes : realized i could use cross product for left of a little bit late so there are 2 functions : (
In figures points with larger circles around them are considered to be on the hull
also my comparison of angles is a little weird if the anchor point is passed it will
return inf for magnitude so it's put at the end of the sorted list

Notabale issues:
Numerical stability was an issue I decided to use an epsilon value (1e-9)
when comparing numbers for added stability 
In the colinear case for graham scan I just made it so closer points would be processed first
adn if they were colinear with the next point remove them from the hull

In the colinear case for naive approach in the construct polygon function it removes
colinear points.

Runtime Results (all in seconds): 
[ RUN ] Timing.hundred
Grham took : 0
Naive took : 0
[       OK ] Timing.hundred (1 ms)
[ RUN      ] Timing.thousand
Grham took : 0
Naive took : 0
[       OK ] Timing.thousand (94 ms)
[ RUN      ] Timing.tenThousand
Grham took : 0
Naive took : 8
[       OK ] Timing.tenThousand (7347 ms)
[ RUN      ] Timing.hundredThousand
Grham took : 0
Naive took : 702
[       OK ] Timing.hundredThousand (702280 ms)


Test selection: 
I wanted to mainly test graham scan edge cases as I can't see the naive hull not 
unless the left of function is wrong Note: poor assumption I did not handle colinearity for the naive case now fixed
test run on both algorithims


Test 1 colinearity one point off hull, wanted ot test thato only the furthest point colinear with respec to the
anchor was added to the hull

Test 2 colinearity all points on hull, wanted to test that only the endpoints were added to the hull 

Test 3 wanted to have a degenerate test case to make sure it works properly when < 3 points are passed

General test, main can generate random point sets either around a circle or square
