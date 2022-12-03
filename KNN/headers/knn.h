//
// Created by root on 30/11/22.
//

#ifndef DIGIT_RECOGNITION_CPP_KNN_H
#define DIGIT_RECOGNITION_CPP_KNN_H

#include "../../headers/data.h"
#include <vector>
using namespace std;

class knn{
    int k;
    vector<class data*> *neighbors;
    vector<class data*> *training_data;
    vector<class data*> *test_data;
    vector<class data*> *val_data;

public:

    knn(int);
    knn();
    ~knn();

    void find_knearest(class data *queryPoint);
    void set_training_data(vector<class data *> *v);
    void set_test_data(vector<class data *> *v);
    void set_val_data(vector<class data *> *v);
    void set_k(int value);

    int predict();
    double calc_dist(class data *query_point, class data *input);
    double val_performance();
    double test_performance();
};


#endif //DIGIT_RECOGNITION_CPP_KNN_H

