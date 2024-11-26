#include "tail.h"

Tail::Tail(int x, int y){
    end_X = x;
    end_Y = y;
}

void Tail::reset(){
    end_X = 8;
    end_Y = 8;
    TailHistory.clear();
}

void Tail::Update(int x, int y){
    TailHistory.push_back(std::pair<int, int>(x, y));
    end_X = TailHistory[0].first;
    end_Y = TailHistory[0].second;
    TailHistory.erase(TailHistory.begin() + 0);
}
void Tail::Expand(int x, int y){
    TailHistory.push_back(std::pair<int, int>(x, y));
    size++;
    //end_X = TailHistory[0].first;
    //end_Y = TailHistory[0].second;
}

std::vector<std::pair<int, int>> Tail::GetHistory(){
    return TailHistory;
}