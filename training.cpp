//
//  training.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"

Training::Training() {
    
}

Training::Training(string file, int iteration) {
    maxIteration = iteration;
    extractAttribute(file);
    extractData(file);
    convert();
}

Training::Training(Training& tr) {
    targetAttribute = tr.targetAttribute;
    for (map<string, vector<string> >::const_iterator it=tr.attribute.begin(); it!=tr.attribute.end(); it++) {
        for (int i=0; i<it->second.size(); i++) {
            attribute[it->first].push_back(it->second[i]);
        }
    }
    for (int j=0; j<tr.getNumberData(); j++) {
        map<string, string> content;
        for (map<string, vector<string> >::const_iterator it=attribute.begin(); it!=attribute.end(); it++) {
                content[it->first] = (tr.data)[j][it->first];            
        }
        content[targetAttribute] = (tr.data)[j][targetAttribute];
        data.push_back(content);
    }
    for (int i=0; i<tr.attributeIndex.size(); i++) {
        attributeIndex.push_back(tr.getAttribute(i));
    }
    convert();
}

Training& Training::operator=(Training& tr) {
    targetAttribute = tr.targetAttribute;
    for (map<string, vector<string> >::const_iterator it=tr.attribute.begin(); it!=tr.attribute.end(); it++) {
        for (int i=0; i<it->second.size(); i++) {
            attribute[it->first].push_back(it->second[i]);
        }
    }
    for (int j=0; j<tr.getNumberData(); j++) {
        map<string, string> content;
        for (map<string, vector<string> >::const_iterator it=attribute.begin(); it!=attribute.end(); it++) {
            content[it->first] = (tr.data)[j][it->first];
        }
        content[targetAttribute] = (tr.data)[j][targetAttribute];
        data.push_back(content);
    }
    for (int i=0; i<tr.attributeIndex.size(); i++) {
        attributeIndex.push_back(tr.getAttribute(i));
    }
    convert();
    
    return *this;
}

Training::~Training() {
    
}

void Training::extractData(string file) {
    //initiate data
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        bool findData = false;
        while (!readFile.eof()) {
            getline(readFile, strLine);            
            if (findData) {
                char * token;
                char * cstr = new char[strLine.length()+1];
                strcpy(cstr, strLine.c_str());
                token = strtok(cstr, ",");
                int x = 0;
                map<string, string> content;
                while (token!=NULL && x<=getNumberAttribute()) {
                    string tokenStr(token);
                    if (x==getNumberAttribute()) {
                        content[targetAttribute] = tokenStr;
                    } else {
                        content[getAttribute(x)] = tokenStr;
                    }
                    token = strtok(NULL, ",");
                    x++;
                }
                
                data.push_back(content);
            } else if (strLine.find("@DATA")!=string::npos) {
                findData = true;
            }
        }
    }
}

void Training::extractAttribute(string file) {
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        bool findRelation = false;
        bool findAttribute = false;
        bool findData = false;
        int indexAttr = 0;
        while (!readFile.eof() && !findData) {            
            getline(readFile, strLine);
            char * token;
            char * cstr = new char[strLine.length()+1];
            strcpy(cstr, strLine.c_str());

            if (strLine.find("@RELATION")!=string::npos) {
                findRelation = true;
            } else if (strLine.find("@ATTRIBUTE")!=string::npos) {
                findAttribute = true;
                findRelation = false;
            } else if (strLine.find("@DATA")!=string::npos) {
                findData = true;
                findAttribute = false;
            }

            token = strtok(cstr, " "); // parse dalam satu line
            int x = 0;            
            while (token!=NULL && x<3) {
                string tokenStr(token);                
                if (x==1) {                    
                    if (findRelation) {
                        targetAttribute = tokenStr;
                    } else if (findAttribute) {
                        if (tokenStr=="class") {
                            attributeIndex.push_back(targetAttribute);
                        } else {
                            attributeIndex.push_back(tokenStr);
                        }
                    }
                } else if (x==2) { //memasukkan values
                    char * tokenValue = strtok(token, ","); //parse dalam kumpulan values
                    while (tokenValue!=NULL) {
                        string tokenValueStr(tokenValue);                        
                        attribute[attributeIndex[indexAttr]].push_back(tokenValueStr);
                        tokenValue = strtok(NULL, ",");
                    }
                    indexAttr++;
                }
                token = strtok(NULL, " ");
                x++;
            }
        }
    }
}

vector<string> Training::getAttributeValues(string attr){
    return attribute[attr];
}

void Training::setAttributeValues(string attr, vector<string> v) {
    attribute[attr] = v;
}

string Training::getTargetAttribute() {
    return targetAttribute;
}

string Training::getDataValue(int i, string attr) {
    if (i<getNumberData()) {
        return data[i][attr];
    }
}

int Training::getDataValueConverted(int i, string attr) {
    return convertValues[getDataValue(i, attr)];
}

vector< map<string, string> > Training::getDataVector() {
    return data;
}

string Training::getAttribute(int index) {  
    return attributeIndex[index];
}

int Training::getNumberAttribute() {
    return attributeIndex.size()-1;
}

int Training::getNumberData() {
    return data.size();
}

bool Training::isAll1() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="0") {
            return false;
        }
    }
    return true;
}

bool Training::isAll0() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="1") {
            return false;
        }
    }
    return true;
}

void Training::deleteAttribute(string attr) {
    attribute.erase(attr);
    int found = 0;
    while (attributeIndex[found]!=attr) {
        found++;
    }
    attributeIndex.erase(attributeIndex.begin()+found);
}

void Training::deleteInstance(int index) {
    data.erase(data.begin()+index);
}

int Training::getMaxIteration() {
    return maxIteration;
}

void Training::convert() {
    convertValues["sunny"] = 1;
    convertValues["overcast"] = 0;
    convertValues["rain"] = -1;
    
    convertValues["hot"] = 0;
    convertValues["mild"] = 1;
    convertValues["cold"] = -1;
    
    convertValues["high"] = 0;
    convertValues["normal"] = 1;
    
    convertValues["strong"] = 0;
    convertValues["weak"] = 1;
    
    convertValues["yes"] = 1;
    convertValues["no"] = 0;
}










