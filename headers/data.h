//
// Created by mouad on 04/11/22.
//

#ifndef DIGIT_RECOGNITION_CPP_DATA_H
#define DIGIT_RECOGNITION_CPP_DATA_H

#include <vector>
#include "stdio.h"
#include "stdint.h"
using namespace std;

class data {
    vector<uint8_t> * features_vector;

    uint8_t label;
    int enum_label;

public:
    data();
    ~data();
    void set_feature_vector(vector<uint8_t>*);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enum_label(int);

    int get_feature_vector_size();
    uint8_t get_label();
    uint8_t get_enum_label();
    vector<uint8_t> *get_features_vector();
};


#endif //DIGIT_RECOGNITION_CPP_DATA_H
