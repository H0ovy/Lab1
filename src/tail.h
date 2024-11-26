#ifndef TAIL_H
#define TAIL_H

#include <vector>

class Tail
{
public:
    Tail(int x, int y);
    void reset();
    int end_X, end_Y;
    void Update(int x, int y);
    void Expand(int x, int y);
    std::vector<std::pair<int, int>> GetHistory();

private:
    std::vector<std::pair<int, int>> TailHistory;
    int size = 0;
};

#endif