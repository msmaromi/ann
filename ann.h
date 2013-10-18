//
//  ann.h
//  
//
//  Created by Muhammad S Maromi on 9/26/13.
//
//

#ifndef ____ann__
#define ____ann__

#include <iostream>
#include "training.h"

class ANN {
public:
    ANN();
    ANN(Training, int, int);
    ANN(const ANN&);
    ANN& operator=(const ANN&);
    ~ANN();
    
    double activeFunction();
    int outputFunction(int); // 1=sigmoid, 2=step
    void annBatch(Training, int);
    void annIncremental(Training, int);
    
    void setListX(vector<int>);
    vector<double> getListW();
    
private:
    int n;// banyak atribut
    vector<double> listW; // array of w
    vector<int> listX; // array of x
    int output;
    Training dataset;
};

#endif /* defined(____ann__) */
