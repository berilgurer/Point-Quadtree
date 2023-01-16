//  Created by Beril Gürer on 9.11.2022.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "29201-BerilGurer-PointQuadtree.h"

using namespace std;

int main() {
    
    ifstream input;
    string filename = "cities.txt";
    input.open(filename.c_str());
    string s;
    
    int xr, yr, x, y;
    string city;
    
    int count = 0;
        
    PointQuadtree ourQuads;
    while (getline(input,s)){
        istringstream input(s);
        if(count == 0){
            input >> xr >> yr;
            ourQuads.getPoint(xr, yr);
        }
        
        else{
            input >> city >> x >> y;
            ourQuads.addCity(city, x, y);
        }
        count++;

    }
    ourQuads.pretty_print(ourQuads.returnHead());
    
    cout << endl;
    
    int x_cor, y_cor, radius;
    ifstream input2;
    string filename2 = "queries.txt";
    input2.open(filename2.c_str());
    string s2;
    
    while (getline(input2,s2)){
        vector<int> number;
        istringstream input2(s2);
        for (int i; input2 >> i;) {
            number.push_back(i);
               if (input2.peek() == ',')
                   input2.ignore();
           }
        
        x_cor = number[0];
        y_cor = number[1];
        radius = number[2];

        quadNode* myHead = ourQuads.returnHead();
        vector<string> visit;
        ourQuads.findCity(visit, myHead, radius, x_cor, y_cor);

    }
    return 0;
}
