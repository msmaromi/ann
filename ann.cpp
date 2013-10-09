//
//  ann.cpp
//  
//
//  Created by Muhammad S Maromi on 9/26/13.
//
//

#include "ann.h"

ANN::ANN() {
    
}

ANN::ANN(Training tr) {
    dataset = tr;
    n = dataset.getNumberAttribute();
    //inisiasi W
    for (int i=0; i<=n; i++) {
        listW.push_back(0.5);
    }
    //inisiasi X
    listX.push_back(1);
    for (int i=0; i<n; i++) {
        string attribute = dataset.getAttribute(i);
        listX.push_back(dataset.getDataValueConverted(0, attribute));
    }
    output = outputFunction(1);
}

ANN::ANN(const ANN&) {
    
}

ANN& ANN::operator=(const ANN&) {
    
}

ANN::~ANN() {
    
}

double ANN::activeFunction() {
    double result = 0;
    for (int i=0; i<=n; i++) {
        result = listX[i]*listW[i] + result;
    }
    return result;
}

int ANN::outputFunction(int opt) {
    double y = activeFunction();
    if (opt==1) {//sigmoid
        if (y>0) {
            return 1;
        } else {
            return 0;
        }
    } else if (opt==2) {//step
        if (y>2) { // 2: threshold
            return 1;
        } else {
            return 0;
        }
    }
}
