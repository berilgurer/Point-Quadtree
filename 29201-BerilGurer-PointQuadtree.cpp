#include "29201-BerilGurer-PointQuadtree.h"

PointQuadtree::PointQuadtree(){
    x_limit = 0;
    y_limit = 0;
	head = NULL;
};

quadNode * PointQuadtree:: returnHead(){
    return head;
};
void PointQuadtree:: getPoint(int x_max, int y_max){
    x_limit = x_max;
    y_limit = y_max;
};

quadNode* PTcompare(quadNode* temp, int xCor, int yCor){
    bool keepGoing = true;
    do{
        if(xCor < temp->x_Quad && yCor >= temp->y_Quad && temp->NW != NULL){temp = temp->NW;}
        else if(xCor >= temp->x_Quad && yCor >= temp->y_Quad && temp->NE != NULL){temp = temp->NE;}
        else if(xCor < temp->x_Quad && yCor < temp->y_Quad && temp->SW != NULL){temp = temp->SW;}
        else if(xCor >= temp->x_Quad && yCor < temp->y_Quad && temp->SE != NULL){temp = temp->SE;}
        else {keepGoing = false;}
    }while(keepGoing);
    return temp;
}

quadNode* goNextNode(quadNode* temp, quadNode* newNode, int xCor, int yCor){
    if(xCor < temp->x_Quad && yCor >= temp->y_Quad){temp->NW = newNode;}
    else if(xCor >= temp->x_Quad && yCor >= temp->y_Quad){temp->NE = newNode;}
    else if(xCor < temp->x_Quad && yCor < temp->y_Quad){temp->SW = newNode;}
    else if(xCor >= temp->x_Quad && yCor < temp->y_Quad){temp->SE = newNode;}
    return newNode;
}

quadNode * PointQuadtree::addCity(string cName, int xCor, int yCor){
    if(x_limit >= xCor && y_limit >= yCor){
        if(head == NULL){
            head = new quadNode(NULL, NULL, NULL, NULL, xCor, yCor, cName);
            return head;
        }
        else{
            quadNode * temp = head;
            temp = PTcompare(temp, xCor, yCor);
            
            quadNode * newNode = new quadNode(NULL, NULL, NULL, NULL, xCor, yCor, cName);

            newNode = goNextNode(temp, newNode, xCor, yCor);
            return newNode;
        }
    }
    else{
        return NULL;
    }
}

bool inVector (int tempX, int tempY, vector<double> isIncluded_x, vector<double> isIncluded_y, string quad){
    bool isInclusive = false;
    int i = 0;
    double iter = isIncluded_x.size();
    while (i < iter) {
        if ((quad == "NW" && isIncluded_x[i] <= tempX && isIncluded_y[i] >= tempY) ||
            (quad == "NE" && isIncluded_x[i] >= tempX && isIncluded_y[i] >= tempY) ||
            (quad == "SW" && isIncluded_x[i] <= tempX && isIncluded_y[i] <= tempY) ||
            (quad == "SE" && isIncluded_x[i] >= tempX && isIncluded_y[i] <= tempY)){
            isInclusive = true;
        }
        i++;
    }
    return isInclusive;
}

bool isIncluded (int tempX, int tempY, int x, int y, int radius, string quad){
    vector<double> isIncluded_x, isIncluded_y;
    int angle=0;
    while(angle<=90){
        double xCo, yCo;
        if (quad == "SE"){
            xCo = x + (cos(angle)*radius);
            yCo = y - (sin(angle)*radius);
        }else if (quad == "SW"){
            xCo = x - (cos(angle)*radius);
            yCo = y - (sin(angle)*radius);
        }else if (quad == "NE"){
            xCo = x + (cos(angle)*radius);
            yCo = y + (sin(angle)*radius);
        }else if (quad == "NW"){
            xCo = x - (cos(angle)*radius);
            yCo = y + (sin(angle)*radius);
        }
        isIncluded_x.push_back(xCo);
        isIncluded_y.push_back(yCo);
            
        angle++;
    }
    return inVector(tempX, tempY,isIncluded_x,isIncluded_y, quad);
}

void printPath(vector<string> & cities){
    int ind = 0;
    while(ind < cities.size()){
        if (ind == cities.size()-1) {
            cout << cities[ind];
        } else {
            cout << cities[ind] << ", ";
        }
        ind++;
    }
}
void inRang(quadNode* currCity, int radius, int x, int y, bool & firstCity){
    bool inRange = (radius)*(radius) >= (x - currCity->x_Quad)*(x - currCity->x_Quad) + (y - currCity->y_Quad)*(y - currCity->y_Quad);
    if(inRange){
        if(!firstCity){
            cout << currCity->city;
            firstCity = true;
        } else {
            cout << ", " << currCity->city;
        }
    }
}

bool firstCity = false;
void PointQuadtree::findCity(vector<string> & cities, quadNode* currCity, int radius, int x, int y){
	if (currCity == NULL) {
		return;
	}
    inRang(currCity, radius, x, y, firstCity);
	cities.push_back(currCity->city);

	if (isIncluded(currCity->x_Quad, currCity->y_Quad, x, y, radius, "SE")){findCity(cities, currCity->SE, radius, x, y);}
	if (isIncluded(currCity->x_Quad, currCity->y_Quad, x, y, radius, "SW")){findCity(cities, currCity->SW, radius, x, y);}
	if (isIncluded(currCity->x_Quad, currCity->y_Quad, x, y, radius, "NE")){findCity(cities, currCity->NE, radius, x, y);}
	if (isIncluded(currCity->x_Quad, currCity->y_Quad, x, y, radius, "NW")){findCity(cities, currCity->NW, radius, x, y);}
	
	if (currCity == head) {
		if (!firstCity) {
			cout << "<None>";
		}
        firstCity = false;
		cout << endl;
        printPath(cities);
		cout << endl << endl;
	}
}

void PointQuadtree::pretty_print (quadNode * temp){
    if (temp != NULL){
        cout << temp->city << endl ;
        pretty_print(temp->SE);
        pretty_print(temp->SW);
        pretty_print(temp->NE);
        pretty_print(temp->NW);
    }
}
