#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

struct quadNode{
    int x_Quad;
    int y_Quad;
    string city;
	quadNode * NE;
	quadNode * NW;
	quadNode * SE;
	quadNode * SW;
    quadNode(): NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr){}
    quadNode(quadNode* northWest = NULL, quadNode* northEast = NULL, quadNode* soutWest = NULL, quadNode* southEast = NULL, int xCor = 0, int yCor = 0, string name = "") :
    NW(northWest), NE(northEast), SW(soutWest), SE(southEast), x_Quad(xCor), y_Quad(yCor), city(name){}
};

class PointQuadtree{
    public:
        PointQuadtree();
        void getPoint(int, int);
        void pretty_print (quadNode* temp);
        void findCity(vector<string> &, quadNode*, int, int, int);
        quadNode * returnHead();
        quadNode * addCity(string, int, int);
    
    private:
        quadNode * head;
        int x_limit;
        int y_limit;
};


