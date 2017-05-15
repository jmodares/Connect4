#include <iostream>
#include <string>

#include "node.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Welcome to the world of happiness! " << endl;

    cout << "Let's determine your turn (First/Second)? ";

    int w;
    int step = 0;
    Node* root = new Node();

    string str;
    bool valid;
    do {
        valid = true;
        cin >> str;

        switch (str[0]) {
        case 'f':
        case 'F':
            break;
        case 's':
        case 'S':
            do {
                cout << "What was your friend move index (0 to exit)? ";
                cin >> w;
                if (!w) {
                    cout << "Thank you for using me to be with you throu " << step << " steps of the game. Good Luck!" << endl;

                    return -1;
                }
            } while (!root->addCell(false, w));
            break;
        default:
            cout << "Please choose your turn (First/Second)? ";
            valid = false;
            break;
        }
    } while (!valid);

    while (true) {
        cout << "Next move index recommendation (0 for no recommendation): " << root->nextMove() << endl;

        do {
            cout << "What was your move index (0 to exit)? ";
            cin >> w;
            if (!w) {
                cout << "Thank you for using me to be with you throu " << step << " steps of the game. Good Luck!" << endl;

                return -1;
            }
        } while (!root->addCell(true, w));

        if (root->matchCell(true, w)) {
            cout << "Congradulations, you won!" << endl;
            break;
        }

        do {
            cout << "What was your friend move index (0 to exit)? ";
            cin >> w;
            if (!w) {
                cout << "Thank you for using me to be with you throu " << step << " steps of the game. Good Luck!" << endl;

                return -1;
            }
        } while (!root->addCell(false, w));

        if (root->matchCell(false, w)) {
            cout << "Sorry, next time you will win!" << endl;
            break;
        }

        step++;
    }

    return 0;
}
