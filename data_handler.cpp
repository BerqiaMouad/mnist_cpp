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
data_handler::~data_handler() = default;

void data_handler::read_feature_vector(const string& path){
    uint32_t header[4]; // magic / num of images / row size / column size
    unsigned char bytes[4];
    FILE* f = fopen(path.c_str(), "r");
    if(f){
        for(auto& it: header){
            if(fread(bytes, sizeof(bytes), 1, f)){
                it = convert_to_little_indian(bytes);
            }
        }
        std::cout << "Got the input file header!\n";

        int image_size = header[2] * header[3];
        for(int i = 0; i < header[1]; i++){
            auto d = new class data();
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
void data_handler::read_feature_labels(const string& path){
    uint32_t header[2]; // magic / num of images
    unsigned char bytes[4];
    FILE* f = fopen(path.c_str(), "r");
    if(f){
        for(auto& it: header){
            if(fread(bytes, sizeof(bytes), 1, f)){
                it = convert_to_little_indian(bytes);
            }
        }
        std::cout << "Got the label file header!\n";

        for(int i = 0; i < header[1]; i++){
            uint8_t element[1];
            if(fread(element, sizeof(element), 1, f)){
                data_array->at(i)->set_label(element[0]);
            }
            else{
                std::cout << "ERROR: couldn't read file! \n";
                exit(1);
            }
        }
        std::cout << "READ and STORED label! \n";
    }
    else {
        std::cout << "ERROR: couldn't read file! \n";
        exit(1);
    }
}
void data_handler::split_data(){
    unordered_set<int> used_indexes;
    int train_size = data_array->size() * TRAIN_SET_PERCENT;
    int test_size = data_array->size() * TEST_SET_PERCENT;
    int validation_size = data_array->size() * VALIDATION_SET_PERCENT;

    // Train data set
    int count = 0;
    while(count < train_size){
        int rand_ind = random() % data_array->size();
        if(used_indexes.find(rand_ind) == used_indexes.end()){
            training_data->push_back(data_array->at(rand_ind));
            used_indexes.insert(rand_ind);
            count++;
        }
    }

    // Test data set
    count = 0;
    while(count < test_size){
        int rand_ind = random() % data_array->size();
        if(used_indexes.find(rand_ind) == used_indexes.end()){
            test_data->push_back(data_array->at(rand_ind));
            used_indexes.insert(rand_ind);
            count++;
        }
    }

    // validation data set
    count = 0;
    while(count < validation_size){
        int rand_ind = random() % data_array->size();
        if(used_indexes.find(rand_ind) == used_indexes.end()){
            validation_data->push_back(data_array->at(rand_ind));
            used_indexes.insert(rand_ind);
            count++;
        }
    }
}
void data_handler::count_classes(){
    int count = 0;
    for(auto& it: *data_array){
        if(class_map.find(it->get_label()) == class_map.end()){
            class_map[it->get_label()] = count;
            it->set_enum_label(count);
            count++;
        }
    }
    num_classes = count;
    cout << "Extracted " << num_classes << " classes successfully!\n";
}

uint32_t data_handler::convert_to_little_indian(const unsigned char* bytes){
    return (uint32_t) (
            (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3])
            );
}
vector<class data *> *data_handler::get_training_data(){
    return training_data;
}
vector<class data *> *data_handler::get_test_data(){
    return test_data;
}
vector<class data *> *data_handler::get_validation_data(){
    return validation_data;
}