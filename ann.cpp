//
//  ann.cpp
//  
//
//  Created by Muhammad S Maromi on 9/26/13.
//
//

#include "ann.h"
#define MaximumIteration 10
#define LearningRate 0.1f
#define MSEThereshold 0.2f
#define ThresholdStep 0
#define Epsilon 0.0f

ANN::ANN() {
    
}

ANN::ANN(Training tr, int optFunction, int optMode) { // optFunction=pilihan fungsi aktivasi, optMode=pilihan mode iterasi
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
//    output = outputFunction(optFunction);
    if (optMode==1) {
        annBatch(tr, optFunction);
    } else if (optMode==2) {
        annIncremental(tr, optFunction);
    }
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
        if (y>ThresholdStep) {
            return 1;
        } else {
            return 0;
        }
    } else if (opt==3) {//sign
        if (y>0) {
            return 1;
        } else {
            return -1;
        }
    } else if (opt==4) {//linear
        return y;
    }
}

void ANN::setListX(vector<int> list) {
    for (int i=0; i<listX.size(); i++) {
        listX[i] = list[i];
    }
}

vector<double> ANN::getListW() {
    return listW;
}

void ANN::annBatch(Training tr, int optFunction) {
	vector<double> deltaW;
	int counter = 0;
    double MSE = 999;
    double pow;
    int oF;
    //isi delta w dengan 0
    for (int i = 0 ; i < listW.size(); i++){
        deltaW.push_back(0);    
    }
	while (counter < MaximumIteration && MSE > Epsilon) {
        cout << "===================" << endl;
        cout << "==== epoch " << counter+1 << " =====" << endl;
        cout << "===================" << endl;
        
        cout << "  x0  x1  x2  x3  x4       w0       w1       w2       w3       w4        y        o        t  deltaW0  deltaW1  deltaW2  deltaW3  deltaW4";
//        cout << "  x0  x1  x2       w0       w1       w2        y        o        t  deltaW0  deltaW1  deltaW2";
        cout << endl;
        //satu batch
        MSE = 0;
		for (int i = 0; i < tr.getNumberData() ; i++){
            for (int j=0; j<listX.size(); j++) {
                printf("%4d", listX[j]);
            }
            for (int j=0; j<listW.size(); j++) {
                printf("%9.2f", listW[j]);
            }
            
            oF = outputFunction(optFunction);
            printf("%9.2f", activeFunction());
            printf("%9d", oF);
            printf("%9d", tr.getDataValueConverted(i, tr.getTargetAttribute()));
            
			for (int j = 0 ; j < listW.size() ; j++){
                deltaW[j] = deltaW[j] + LearningRate * (tr.getDataValueConverted(i, tr.getTargetAttribute()) - oF) * listX[j];
			}                                               
            
            if (i+1<tr.getNumberData()) {
                for (int j=0; j<listX.size(); j++) {
                    if (j>0) {
                        listX[j] = tr.getDataValueConverted(i+1, tr.getAttribute(j-1));
                    } else {
                        listX[j] = 1;
                    }
                }
            } else {
                for (int j=0; j<listX.size(); j++) {
                    if (j>0) {
                        listX[j] = tr.getDataValueConverted(0, tr.getAttribute(j-1));
                    } else {
                        listX[j] = 1;
                    }
                }
            }
            
            for (int j=0; j<deltaW.size(); j++) {
                printf("%9.2f", deltaW[j]);
            }
            cout << endl;
            
            pow = tr.getDataValueConverted(i, tr.getTargetAttribute()) - oF ;
			pow = pow * pow;
			MSE = MSE + pow;
		}
        
        MSE = (MSE / tr.getNumberData());
        cout << "MSE : " << MSE << endl;
        cout << endl;
        
		//update
		for (int i = 0 ; i < listW.size() ; i++){
			listW[i] = listW[i] + deltaW[i];
		}               
        
        //isi delta w dengan 0
        for (int i = 0 ; i < listW.size(); i++){
            //deltaW.push_back(0);
            deltaW[i] = 0;
        }
        
		counter++;
	}	
}

void ANN::annIncremental(Training tr, int optFunction){
    vector<double> deltaW;
	//isi delta dengan 0
	int counter = 0;
    double MSE = 999;
    double pow;
    int oF;
    for (int i = 0 ; i < listW.size(); i++){
        deltaW.push_back(0);
    }
	while (counter < MaximumIteration && MSE>Epsilon) {
        cout << "===================" << endl;
        cout << "==== epoch " << counter+1 << " =====" << endl;
        cout << "===================" << endl;
        
        cout << "  x0  x1  x2  x3  x4       w0       w1       w2       w3       w4        y        o        t  deltaW0  deltaW1  deltaW2  deltaW3  deltaW4";
        cout << endl;
        //satu batch
        MSE = 0;
		for (int i = 0; i < tr.getNumberData() ; i++){
            for (int j=0; j<listX.size(); j++) {
                printf("%4d", listX[j]);
            }
            for (int j=0; j<listW.size(); j++) {
                printf("%9.2f", listW[j]);
            }
            
            oF = outputFunction(optFunction);
            printf("%9.2f", activeFunction());
            printf("%9d", oF);
            printf("%9d", tr.getDataValueConverted(i, tr.getTargetAttribute()));
            
            for (int j = 0 ; j < listW.size() ; j++){
                deltaW[j] = LearningRate * (tr.getDataValueConverted(i, tr.getTargetAttribute()) - oF) * listX[j];
                //update w
                listW[j] = listW[j] + deltaW[j];
			}
            
            for (int j=0; j<deltaW.size(); j++) {
                printf("%9.2f", deltaW[j]);
            }
            cout << endl;
            
            if (i+1<tr.getNumberData()) {
                for (int j=0; j<listX.size(); j++) {
                    if (j>0) {
                        listX[j] = tr.getDataValueConverted(i+1, tr.getAttribute(j-1));
                    } else {
                        listX[j] = 1;
                    }
                }
            } else {
                for (int j=0; j<listX.size(); j++) {
                    if (j>0) {
                        listX[j] = tr.getDataValueConverted(0, tr.getAttribute(j-1));
                    } else {
                        listX[j] = 1;
                    }
                }
            }
            
            pow = tr.getDataValueConverted(i, tr.getTargetAttribute()) - oF ;
			pow = pow * pow;
			MSE = MSE + pow;
		}
        
		MSE = (MSE / tr.getNumberData());
        printf("MSE : %9.2f", MSE);
        cout << endl;
        
        //isi delta w dengan 0
        for (int i = 0 ; i < listW.size(); i++){
            //deltaW.push_back(0);
            deltaW[i] = 0;
        }
		counter++;
	}
}
