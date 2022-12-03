#include <iostream>
#include "headers/data_handler.h"
#include "KNN/headers/knn.h"

int main() {
    data_handler *dh = new data_handler();
    dh->read_feature_vector("/home/mouad/Documents/mnist_cpp/Data/train-images-idx3-ubyte");
    dh->read_feature_labels("/home/mouad/Documents/mnist_cpp/Data/train-labels-idx1-ubyte");
    dh->split_data();
    dh->count_classes();

    knn *knearst = new knn();
    knearst->set_training_data(dh->get_training_data());
    knearst->set_test_data(dh->get_test_data());
    knearst->set_val_data(dh->get_validation_data());
    double accuracy = 0;
    double best_accuracy = 0;
    int bestK = 1;
    for(int i = 1; i<= 4; i++){
        if(i == 1){
            knearst->set_k(i);
            accuracy = knearst->val_performance();
            best_accuracy = accuracy;
        }
        else {
            knearst->set_k(i);
            accuracy = knearst->val_performance();
            if(accuracy > best_accuracy){
                best_accuracy = accuracy;
                bestK = i;
            }
        }
    }
    knearst->set_k(bestK);
    knearst->test_performance();

    return 0;
}
