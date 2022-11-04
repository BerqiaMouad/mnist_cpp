//
// Created by mouad on 04/11/22.
//

#include "../headers/data.h"

data::data() {
    features_vector = new std::vector<uint8_t >;
}
data::~data() {
    // free stuff
}
void data::set_feature_vector(vector<uint8_t>* vect){
    features_vector = vect;
}
void data::append_to_feature_vector(uint8_t val){
    features_vector->push_back(val);
}
void data::set_label(uint8_t val){
    label = val;
}
void data::set_enum_label(int val){
    enum_label = val;
}

int data::get_feature_vector_size(){
    return features_vector->size();
}
uint8_t data::get_label(){
    return label;
}
uint8_t data::get_enum_label(){
    return enum_label;
}
vector<uint8_t > * data::get_features_vector() {
    return features_vector;
}