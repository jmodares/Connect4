#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
    Node();

    bool addCell(bool cl, int w);
    bool removeCell(int w);

    bool matchCell(bool cl, int w);

    int nextMove();

private:
    std::vector<std::vector<bool> > m_table;

    bool validCell(int w, int h);

    bool slashMatch(bool cl, int w);
    bool verticalMatch(bool cl, int w);
    bool backslashMatch(bool cl, int w);
    bool horizontalMatch(bool cl, int w);

    void findMatch(std::vector<int>& win, std::vector<int>& lose, bool cl, int w, int d);
};

#endif // NODE_H
