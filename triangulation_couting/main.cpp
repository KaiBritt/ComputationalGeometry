#include <float.h>
#include <iostream>
#include <format>
#include <map>
#include <set>
#include<vector>
//
// Created by kai on 3/7/25.
//

std::string diagnoalToStr(std::map<int, std::pmr::vector<int>> diagonals) {
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

//attempt 1 actualyl goign to design an algorithim now
// int countTriangulations(int l, int r,int pgon) {
//     int count = 0;
//
//     if (is3edges(l,r,diagonal,pgon)) { //base case
//         numTriag++;
//         // parseDiagonals(diagonal);
//         return 1;
//     }
//     int diagTo;
//     if (diagonal[l].empty()) {
//         diagTo = (l+2)%pgon;
//     }
//     else {
//         diagTo = diagonal[l].back();
//     }
//     int t1Size;
//     int t2Size;
//     while (diagTo != r){
//         diagonal[l].push_back(diagTo);
//         // diagonal[diagTo].push_back(l);
//         t1Size = countTriangulations(l, diagTo, pgon);
//         t2Size = countTriangulations(diagTo, l, pgon);
//         count += t1Size * t2Size;
//         // diagonal[diagTo].pop_back();
//         diagonal[l].pop_back();
//         if (!diagonal[diagTo].empty()) {
//             diagTo = diagonal[diagTo].back();
//         }
//         else {
//             diagTo = (diagTo + 1) % pgon;
//         }
//     }
//
//     return count;
// }

std::pmr::set<std::string> triangulationMap{};
int triCount = 0;
void countTriangulations(int l, int r, int pgon, int numDiag) {
    std::cout << numDiag <<  "," << triangulationMap.size() << std::endl;
    if (numDiag == pgon-3) {
        // base case we (we have reached a valid triangulation that started with an ear :sob:)
        std::string triangulation = diagnoalToStr(diagonals);
        if (!triangulationMap.contains(triangulation)) {
            triangulationMap.insert(triangulation);
            // triCount +=1;
        }
        return ;
    }
    if (is3edges(l,r,diagonals,pgon)) {
        // in a triangle
        return;
    }
    // main-case just brute forcing :/

    // asigning diagTo's value either l+2 (nearest diagonal) or then next diagnol
    int diagTo;
    if (!diagonals[l].empty())
        diagTo = diagonals[l].back();
    else
        diagTo = (l+2)%pgon;
    while (diagTo != r) {
        std::cout <<  "Diagnoals:" <<diagnoalToStr(diagonals) << std::endl;

        diagonals[l].push_back(diagTo);
        countTriangulations(l,diagTo,pgon,numDiag + 1);
        countTriangulations(diagTo,l,pgon,numDiag + 1 );

        diagonals[l].pop_back();
        if (!diagonals[diagTo].empty())
            diagTo = diagonals[diagTo].back();
        else
            diagTo = (diagTo+1)%pgon;
    }
    return;
}

int  main(){
  countTriangulations(0,5,6,0);

    std::cout << triCount << std::endl;

  }
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.