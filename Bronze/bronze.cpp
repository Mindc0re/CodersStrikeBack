#include <iostream>
#include <string>
#include <cmath>
#include <cfloat>

using namespace std;

class Vector2D
{
public:
	Vector2D() : x(0), y(0) { return ; }
	Vector2D(float nx, float ny) : x(nx), y(ny) { return ; }
	Vector2D(Vector2D &v) : x(v.getX()), y(v.getY()) { return ; }
	~Vector2D() { return ; }

    Vector2D	operator- (Vector2D const &v) const { 
		return Vector2D(this->x - v.getX(), this->y - v.getY()); 
	}

	float		getX() const { return this->x ; }
	float		getY() const { return this->y ; }

	float		length() const { 
		return sqrt( pow(x, 2) + pow(y, 2) ); 
	}
	
	Vector2D	normalize() {
		if (this->x == 0 && this->y == 0)
			return *this;
		float len = this->length();
		return Vector2D(this->x / len, this->y / len);
	}

private:
	float x;
    float y;

};

Vector2D   currentVelocity(Vector2D const &desiredVelocity, float angle) {
	    float radian = (angle * M_PI) / 180;
	    float sinAng = sin(angle);
	    float cosAng = cos(angle);
	    
	    return Vector2D( desiredVelocity.getX() * cosAng - desiredVelocity.getY() * sinAng, desiredVelocity.getY() * cosAng + desiredVelocity.getX() * sinAng);
}

float euclidianDistance(float opX, float opY, float myX, float myY)
{
    float   x = (opX - myX);
    float   y = (opY - myY);
    
    float   d = pow(x, 2) + pow(y, 2);
    return sqrt(d);
}

int main()
{

    int thrust = 100;
    bool boostAvailable = true;
    bool useBoost = false;
    float opDist = 0.0;

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

        useBoost = false;
        thrust = 100;
        
        opDist = euclidianDistance(opponentX, opponentY, x, y);

        if (nextCheckpointAngle != 0)
        {
            Vector2D desiredVel(nextCheckpointX - x, nextCheckpointY - y);

            Vector2D currentVel = currentVelocity(desiredVel, nextCheckpointAngle);
    
            Vector2D steeringVector = desiredVel - currentVel;
            steeringVector = steeringVector.normalize();
            steeringVector = Vector2D(steeringVector.getX() * 100, steeringVector.getY() * 100);
            
            nextCheckpointX += steeringVector.getX();
            nextCheckpointY += steeringVector.getY();
            
            if (nextCheckpointAngle < -60 || nextCheckpointAngle > 60)
                thrust = 0;
            else
            {
                thrust = nextCheckpointDist < 4000 ? 60 : 100;
                cerr << thrust << endl;
            }
            cerr << "Steering" << endl;
        }
        else if (boostAvailable && opDist > 2000 && nextCheckpointDist > opDist * 2)
        {    
            cout << nextCheckpointX << " " << nextCheckpointY << " BOOST" << endl;
            useBoost = true;
            boostAvailable = false;
        }

        cout << nextCheckpointX << " " << nextCheckpointY << " ";
        if (useBoost)
            cout << "BOOST" << endl;
        else
            cout << thrust << endl;
    }
}