//
// Created by mouad on 04/11/22.
//

#ifndef DIGIT_RECOGNITION_CPP_DATA_HANDLER_H
#define DIGIT_RECOGNITION_CPP_DATA_HANDLER_H

#include <fstream>
#include <cstdint>
#include "data.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
using namespace std;

class data_handler{
    vector<class data *> *data_array;
    vector<class data *> *training_data;
    vector<class data *> *test_data;
    vector<class data *> *validation_data;

    int num_classes;
    int feature_vector_size;
    map<uint8_t , int> class_map;

    const double TRAIN_SET_PERCENT = 0.75;
    const double TEST_SET_PERCENT = 0.20;
    const double VALIDATION_SET_PERCENT = 0.05;

public:
    data_handler();
    ~data_handler();

    void read_feature_vector(string path);
    void read_feature_labels(string path);
    void split_data();
    void count_classes();

    uint32_t convert_to_little_indian(const unsigned char* bytes);
    vector<class data *> *get_training_data();
    vector<class data *> *get_test_data();
    vector<class data *> *get_validation_data();

};

#endif //DIGIT_RECOGNITION_CPP_DATA_HANDLER_H
