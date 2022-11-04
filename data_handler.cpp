//
// Created by mouad on 04/11/22.
//

#include "data_handler.h"
#include <iostream>

data_handler::data_handler(){
    data_array = new std::vector<class data *>;
    test_data = new std::vector<class data *>;
    training_data = new std::vector<class data *>;
    validation_data = new std::vector<class data *>;
}
data_handler::~data_handler(){
    // FREE the stuff allocated
}

void data_handler::read_feature_vector(string path){
    uint32_t header[4]; // magic / num of images / row size / column size
    unsigned char bytes[4];
    FILE* f = fopen(path.c_str(), "r");
    if(f){
        for(int i = 0; i< 4; i++){
            if(fread(bytes, sizeof(bytes), 1, f)){
                header[i] = convert_to_little_indian(bytes);
            }
        }
        std::cout << "Got the file header!\n";

        int image_size = header[2] * header[3];
        for(int i = 0; i < header[1]; i++){
            class data * d = new class data();
            uint8_t element[1];
            for(int j = 0; j < image_size; j++){
                if(fread(element, sizeof(element), 1, f)){
                    d->append_to_feature_vector(element[0]);
                }
                else{
                    std::cout << "ERROR: couldn't read file! \n";
                    exit(1);
                }
            }
            data_array->push_back(d);
        }
        std::cout << "READ and STORED " << data_array->size() << " feature vectors! \n";
    }
    else {
        std::cout << "ERROR: couldn't read file! \n";
        exit(1);
    }
}
void data_handler::read_feature_labels(string path);
void data_handler::split_data();
void data_handler::count_classes();

uint32_t data_handler::convert_to_little_indian(const unsigned char* bytes);
vector<class data *> *data_handler::get_training_data();
vector<class data *> *data_handler::get_test_data();
vector<class data *> *data_handler::get_validation_data();