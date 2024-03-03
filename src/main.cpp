#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include "include/bin_tree.h"

void err_n_die(const char* fmt, ...) {
    int errno_save;
    va_list ap;
    errno_save = errno;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);
    if(errno_save != 0) {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);
    exit(EXIT_FAILURE);
}

int main2() {
    srand(time(NULL));
    BinTree* root = new BinTree{"ROOT"};
    
    std::string filename = "names.txt";
    std::stringstream buffer;

    std::ifstream file{filename};
    if(file.fail()) err_n_die("Error opening a file.");
    buffer << file.rdbuf();
    file.close();

    std::string __string__;
    for(int i = 0; !buffer.eof() || i < 100; ++i) {
        buffer >>__string__;
        root->avl_insert(root, i, __string__);
    }

    root->print_ver();
    root->count_nodes();

    root->delete_at(100);
    root->delete_at(120);
    root->delete_at(80);
    root->delete_at(90);

    std::cout << root->gval(123) << std::endl;

    return 0;
}

int main() {
    BinTree* root = new BinTree{"ROOT"};
    
    std::string filename = "names.txt";
    std::stringstream buffer;

    std::ifstream file{filename};
    if(file.fail()) err_n_die("Error opening a file.");
    buffer << file.rdbuf();
    file.close();

    std::string __string__;
    for(int i = 0; !buffer.eof() && i < 31; ++i) {
        buffer >>__string__;
        root->avl_insert(root, i, __string__);
    }
    root->print_ver();

    int deeepth = 7; // root->find_depth();

    int screen_length = 0;
    for(int i = 0; i < deeepth; ++i)
        screen_length += powf(2, i);

    for(int j = 0; j < deeepth; ++j) {
        int n_nodes = pow(2, j);
        int ks     = (pow(2, deeepth - 1) - n_nodes) / 2; 
        int step_l = float(screen_length) / n_nodes;
        int step_v = pow(2, deeepth - j) / 2.0;

        for(int i = 0; i < step_v; ++i) std::cout <<" ";
        for(int i = 0; i < n_nodes; ++i) {
            std::cout <<"*";
            for(int k = 0; k < step_l && i != n_nodes - 1; ++k) std::cout <<" ";
        }
        std::cout<<std::endl;
    }


    return 0;
}
