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
#include "Training.h"

class ANN {
    ANN();
    ANN(Training);
    ANN(const ANN&);
    operator=(ANN&);
    ~ANN();
    
    activeFunction();
    output(int); // 1=sigmoid, 2=step
    annBatch(Training);
    annIncremental(Training);        
    
private:
    int N;// banyak atr
    vector<int> listW; // array of w
    vector<int> listX; // array of x
    int output;
}

#endif /* defined(____ann__) */
