#ifndef __Gomoku__Computer__
#define __Gomoku__Computer__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Board.h"
#include <vector>
#include <unordered_map>
#include "time.h"
#include <chrono>



using namespace std;
using namespace chrono;

class Computer {
private:
	unordered_map<string, int> hashMap;

public:
	vector<int> nextMoveAlphaBeta(Board&, int depth, high_resolution_clock::time_point startTime, double inputTime);
	int minimaxAlphaBeta(Board&, int, bool, int, int, int, int, high_resolution_clock::time_point startTime, double inputTime);
	int evaluation(Board&, bool);
	bool adjacentPlaced(Board&, int, int);
	bool checkVisitedBoard(Board&);
	int getEvaluation(Board&);
	void insertToHashMap(Board&, int);
};

#endif 
