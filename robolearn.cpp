//
//  robolearn.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"
#include "ann.h"
//#include "ann.h"
using namespace std;

/*string predictTree(Tree tree, Training sample, int index) { // menghasilkan "yes" atau "no"
    if (tree.isLeaf()) {
        return tree.getData();
    } else {
        string optionValue = sample.getDataValue(index, tree.getData());
        Tree *child = tree.findTree(optionValue);
        return predictTree(*child, sample, index);
    }
}

double accuracy (Tree tree, Training ref) { // dalam %
    cout << "menghitung akurasi..." << endl;
    double correct = 0;
    for (int i=0; i<ref.getNumberData(); i++) {
        if (predictTree(tree, ref, i)==ref.getDataValue(i, ref.getTargetAttribute())) {
            correct++;
        }
    }
    return 100*(correct/ref.getNumberData());
}*/




int main() {
    string namaFile;
    cout << "masukkan file training arff..." << endl;
    
    cin >> namaFile;
    Training tr(namaFile, 0);
    Training tr1 = tr;
    ANN ann(tr);
    cout << ann.activeFunction() << endl;
    cout << ann.outputFunction(1) << endl;
}



