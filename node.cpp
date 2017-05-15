#include <algorithm>
#include <iostream>
#include <queue>

#include "config.h"
#include "node.h"

using namespace std;

Node::Node() :
    m_table{TABLE_WIDTH}
{

}

bool Node::validCell(int w, int h) {
    if (w > TABLE_WIDTH || w < 1 || h > m_table[w - 1].size() || h < 1) {
        return false;
    }

    return true;
}

bool Node::addCell(bool cl, int w) {
    if (w > TABLE_WIDTH || w < 1 || m_table[w - 1].size() >= TABLE_HIGHT) {
        return false;
    }

    m_table[w - 1].push_back(cl);

    return true;
}

bool Node::removeCell(int w) {
    if (w > TABLE_WIDTH || w < 1 || m_table[w - 1].size() < 1) {
        return false;
    }

    m_table[w - 1].pop_back();

    return true;
}

bool Node::slashMatch(bool cl, int w) {
    int h = m_table[w - 1].size();

    int down = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w - i, h - i) || m_table[w - i - 1][h - i - 1] != cl) {
            break;
        }

        down++;
    }

    if (down >= 3) {
        return true;
    }

    int up = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w + i, h + i) || m_table[w + i - 1][h + i - 1] != cl) {
            break;
        }

        up++;
    }

    if (up + down >= 3) {
        return true;
    }

    return false;
}

bool Node::verticalMatch(bool cl, int w) {
    int h = m_table[w - 1].size();

    int down = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w, h - i) || m_table[w - 1][h - i - 1] != cl) {
            break;
        }

        down++;
    }

    if (down >= 3) {
        return true;
    }

    return false;
}

bool Node::backslashMatch(bool cl, int w) {
    int h = m_table[w - 1].size();

    int down = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w + i, h - i) || m_table[w + i - 1][h - i - 1] != cl) {
            break;
        }

        down++;
    }

    if (down >= 3) {
        return true;
    }

    int up = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w - i, h + i) || m_table[w - i - 1][h + i - 1] != cl) {
            break;
        }

        up++;
    }

    if (up + down >= 3) {
        return true;
    }

    return false;
}

bool Node::horizontalMatch(bool cl, int w) {
    int h = m_table[w - 1].size();

    int right = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w + i, h) || m_table[w + i - 1][h - 1] != cl) {
            break;
        }

        right++;
    }

    if (right >= 3) {
        return true;
    }

    int left = 0;
    for (int i = 1; i <= 3; i++) {
        if (!validCell(w - i, h) || m_table[w - i - 1][h - 1] != cl) {
            break;
        }

        left++;
    }

    if (left + right >= 3) {
        return true;
    }

    return false;
}

bool Node::matchCell(bool cl, int w) {
    if (slashMatch(cl, w) || verticalMatch(cl, w) || backslashMatch(cl, w) || horizontalMatch(cl, w)) {
        return true;
    }

    return false;
}

void Node::findMatch(vector<int>& win, vector<int>& lose, bool cl, int w, int d) {
    if (d > AI_DEPTH) {
        return;
    }

    bool c = false;

    if (d % 2) {
        c = true;
    }

    if (!addCell(c, w)) {
        return;
    }

    if (matchCell(c, w)) {
        if (c != cl) {
            lose.push_back(d);
        } else {
            win.push_back(d);
        }
    } else {
        for (int i = 1; i <= TABLE_WIDTH; i++) {
            findMatch(win, lose, cl, i, d + 1);
        }
    }

    removeCell(w);
}

int Node::nextMove() {
    int w = 0;
    int best = INT32_MIN;
    for (int i = 1; i <= TABLE_WIDTH; i++) {
        if (m_table[i - 1].size() >= TABLE_HIGHT) {
            continue;
        }

        vector<int> win;
        vector<int> lose;

        findMatch(win, lose, true, i, 1);

        if (win.size() && *min_element(win.begin(), win.end()) == 1) {
            return i;
        }

        if (lose.size() && *min_element(lose.begin(), lose.end()) == 2) {
            continue;
        }

        int dist = win.size() - lose.size();
        if (best < dist) {
            best = dist;
            w = i;
        }
    }

    return w;
}
