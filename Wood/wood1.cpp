#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{

    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();

        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
        bool boost = true;
        if ( nextCheckpointAngle > -10 && nextCheckpointAngle < 10 && nextCheckpointDist > 7000 && boost )
        {
            cout << nextCheckpointX << " " << nextCheckpointY << " BOOST" << endl;
            boost = false;
        }
        else if (nextCheckpointAngle > 60 || nextCheckpointAngle < -60 || nextCheckpointDist < 1500)
            cout << nextCheckpointX << " " << nextCheckpointY << " 0" << endl;
        else
            cout << nextCheckpointX << " " << nextCheckpointY << " 100" << endl;
    }
}