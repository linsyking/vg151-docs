#ifndef _MEM_H_
#define _MEM_H_

#include <iostream>
#include <map>
#include <string>

std::map<std::string, double> variable_map;

void set_variable(char *index, double val) {
    // add variables
    variable_map[index] = val;
    std::cout << "var " << index << " set\n";
}

double get_variable(char * index) { return variable_map[index]; }

#endif
