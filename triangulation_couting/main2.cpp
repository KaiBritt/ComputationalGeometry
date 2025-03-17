#include <algorithm>
#include <float.h>
#include <iostream>
#include <format>
#include <map>
#include <set>
#include<vector>
// //
// // Created by kai on 3/7/25.
// //
//
std::string diagnoalToStr(std::map<int, std::vector<int>> diagonals) {
    std::string out;
    std::string diagToAdd;
    std::pmr::set<std::string> diagonalSet;
    for (auto &diagonal : diagonals) {
        int v1 =  diagonal.first;
        for (auto &v2 : diagonal.second) {
            if (v1 > v2) {
                diagToAdd = std::format("({}, {})", v2,v1);
            }
            else {
                diagToAdd = std::format("({}, {})", v1,v2);
            }
            if (!diagonalSet.contains(diagToAdd)) {
                out += diagToAdd;
                diagonalSet.insert(diagToAdd);
            }
        }
    }
    return out;
}

std::string diagnoalToStr(std::vector<std::pair<int,int>>diagonals) {
    std::string out;
    std::string diagToAdd;
    std::pmr::set<std::string> diagonalSet;
    std::sort(diagonals.begin(), diagonals.end());
    for (auto &diagonal : diagonals) {
        if (diagonal.first > diagonal.second) {
            diagToAdd = std::format("({}, {})", diagonal.second,diagonal.first);
        }
        else {
            diagToAdd = std::format("({}, {})", diagonal.first,diagonal.second);
        }
        if (!diagonalSet.contains(diagToAdd)) {
            out += diagToAdd;
            diagonalSet.insert(diagToAdd);
        }
    }
    return out;
}


bool is3edges(int l,int r, std::map<int,std::pmr::vector<int>> &map, int pgon) {
    int size;
    if (l < r)
        size = r - l + 1;
    else
        size = pgon - l + r + 1;

    if (size  == 3) {
        return true;
    }

    int temp = l;
    for (int i = 0; i < 3; i++) {
        if (!map[temp].empty()) {
            temp = map[temp].back();
        }
        else {
            temp = (temp+1)%pgon;
        }
    }
    return temp == l;
}
static int numTriag = 0;
std::map<int,std::pmr::vector<int>> diagonals{};

// //attempt 1 actualyl goign to design an algorithim now
// // int countTriangulations(int l, int r,int pgon) {
// //     int count = 0;
// //
// //     if (is3edges(l,r,diagonal,pgon)) { //base case
// //         numTriag++;
// //         // parseDiagonals(diagonal);
// //         return 1;
// //     }
// //     int diagTo;
// //     if (diagonal[l].empty()) {
// //         diagTo = (l+2)%pgon;
// //     }
// //     else {
// //         diagTo = diagonal[l].back();
// //     }
// //     int t1Size;
// //     int t2Size;
// //     while (diagTo != r){
// //         diagonal[l].push_back(diagTo);
// //         // diagonal[diagTo].push_back(l);
// //         t1Size = countTriangulations(l, diagTo, pgon);
// //         t2Size = countTriangulations(diagTo, l, pgon);
// //         count += t1Size * t2Size;
// //         // diagonal[diagTo].pop_back();
// //         diagonal[l].pop_back();
// //         if (!diagonal[diagTo].empty()) {
// //             diagTo = diagonal[diagTo].back();
// //         }
// //         else {
// //             diagTo = (diagTo + 1) % pgon;
// //         }
// //     }
// //
// //     return count;
// // }
//
//
// int countDiag(std::map<int, std::pmr::vector<int>> diagonals) {
//     int numDiag = 0;
//     for (auto &diagonal : diagonals) {
//         numDiag += diagonal.second.size();
//     }
//     return numDiag;
// }

std::set<int> removed;
std::vector<std::pair<int,int>> diag;
std::set<std::string> seen;
void earCutting(int pgon) {
    if (diag.size() == pgon - 3) {
        std::string str = diagnoalToStr(diag);
        // std::cout << diagnoalToStr(diag) <<  " " << diag.size() << std::endl;
        ;
        if (seen.insert(str).second) {
            // std::cout << str <<std::endl;
        }

        return;
    }
    int l,r;

    for (int i = 0; i < pgon; i++) {
        if (removed.contains(i))  {
            continue;
        }
        l = ((i-1) + pgon)%pgon;
        r = (i+1)%pgon;
        while (removed.contains(l)) {
            l =  ((l-1) + pgon)%pgon;
        }
        while (removed.contains(r)) {
            r = (r+1)%pgon;
        }
        // if (!first) {
        //     if (l != 0 && r != 0) continue;
        //     if (l == 0 && r == pgon - 1) continue;  // avoid largest first diagonal (symmetry)
        // }
        diag.emplace_back(std::min(l,r),std::max(l,r));
        removed.insert(i);
        earCutting(pgon);
        diag.pop_back();
        removed.erase(i);
    }
}


int  main(){
  // countTriangulations(0,5,6,0);
  //
  //   std::cout << triCount << " " << triagcount << std::endl;


    earCutting(13);


    std::cout << "printing diagonals" << std::endl;
    for (auto &diagonalStr : seen) {
        std::cout << diagonalStr << std::endl;
    }
    std::cout << "fin" << std::endl;

  }



