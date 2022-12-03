//
// Created by root on 30/11/22.
//

#include "../headers/knn.h"
#include <cmath>
#include <limits>
#include <map>
#include <iostream>
#include "stdint.h"
#include "../../headers/data_handler.h"

knn::knn(int val) {
    k = val;
}
knn::knn()=default;
knn::~knn()=default;


void knn::find_knearest(class data *queryPoint) {
    neighbors = new vector<class data*>;
    double min = numeric_limits<double>::max();
    double prev_min = min;
    int ind = 0;
    for(int i = 0; i< k; i++){
        if(!i){
            for(int j = 0; j < training_data->size(); j++){
                double dist = calc_dist(queryPoint, training_data->at(j));
                training_data->at(j)->set_dist(dist);
                if(dist < min){
                    min = dist;
                    ind = j;
                }
            }
            neighbors->push_back(training_data->at(ind));
            prev_min = min;
            min = numeric_limits<double>::max();
        }
        else {
            for(int j = 0; j< training_data->size(); j++){
                double dist = training_data->at(j)->get_distance();
                if(dist > prev_min && dist < min){
                    min = dist;
                    ind = j;
                }
            }
            neighbors->push_back(training_data->at(ind));
            prev_min = min;
            min = numeric_limits<double>::max();
        }
    }
}
void knn::set_training_data(vector<class data *> *v) {
    training_data = v;
}
void knn::set_test_data(vector<class data *> *v) {
    test_data = v;
}
void knn::set_val_data(vector<class data *> *v) {
    val_data = v;
}
void knn::set_k(int value) {
    k = value;
}

int knn::predict() {
    map<uint8_t, int> class_freq;
    for(int i = 0; i < neighbors->size(); i++){
        if(class_freq.find(neighbors->at(i)->get_label()) == class_freq.end()){
            class_freq[neighbors->at(i)->get_label()] = 1;
        }
        else {
            class_freq[neighbors->at(i)->get_label()]++;
        }
    }
    int best = 0, max = 0;
    for(auto it: class_freq){
        if(it.second > max){
            max = it.second;
            best = it.first;
        }
    }

    neighbors->clear();
    return best;
}
double knn::calc_dist(class data *query_point, class data *input) {
    double distance = 0.0;

    if(query_point->get_feature_vector_size() != input->get_feature_vector_size()){
        cout << "ERROR! Size mismatch\n";
        exit(1);
    }
#ifdef EUCLID

    for(unsigned i = 0; i < query_point->get_feature_vector_size(); i++){
        distance += pow((query_point->get_features_vector()->at(i) - input->get_features_vector()->at(i)), 2);
    }
    distance = sqrt(distance);

    return distance;

#elif defined MANHATTEN
    // implement manhatten
#endif

    return distance;
}
double knn::val_performance() {
    double curr_perf = 0;
    int cnt = 0;
    int data_ind = 0;
    for(class data *query_point: *val_data){
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label()){
            cnt++;
        }
        data_ind++;
    }
    curr_perf = ((double)cnt * 100.0) / (double)val_data->size();
    cout << "Validation Accuracy for K =  " << k << ": " << curr_perf << "\n";

    return curr_perf;
}
double knn::test_performance() {
    double curr_perf = 0;
    int cnt = 0;
    for(class data* query_point: *test_data){
        find_knearest(query_point);
        int prediction = predict();
        if(prediction == query_point->get_label())
            cnt++;
    }
    curr_perf = cnt * 100.0 / (double)test_data->size();
    cout << "Test Accuracy: " << curr_perf << "\n";
    return curr_perf;
}