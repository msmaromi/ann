//
//  robolearn.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"
#include "ann.h"
using namespace std;

int predict(ANN ann) { //menghasilkan "1" atau "0" yang berasosiasi dengan "yes" atau "no"
    return ann.outputFunction(1);
}

double accuracy(ANN ann, Training ref) {
    cout << "menghitung akurasi..." << endl;
    double correct = 0;
    for (int i=0; i<ref.getNumberData(); i++) {
        vector<int> list;
        for (int j=0; j<ref.getNumberAttribute(); j++) {
            list.push_back(ref.getDataValueConverted(i, ref.getAttribute(j)));
        }
        ann.setListX(list);
        if (predict(ann)==ref.getDataValueConverted(i, ref.getTargetAttribute())) {
            correct++;
        }
    }
    return 100*(correct/ref.getNumberData());
}

int main() {
    string namaFile;
    cout << "masukkan file training arff..." << endl;
    
    cin >> namaFile;
    Training tr(namaFile, 0);
    Training tr1 = tr;
    ANN ann(tr, 2, 2);
	vector <double> listW = ann.getListW();
    cout << "------------" << endl;
	for (int i = 0 ; i < listW.size() ; i++){
		//cout<<listW[i]<<endl;
        printf("w%d: ", i);
        printf("%.2f\n", listW[i]);
	}
//    for (int i=0; i<tr.getNumberAttribute(); i++) {
//        cout << tr.getDataValueConverted(2, tr.getAttribute(i)) << " ";
//    }
//    cout << endl;
    
}



