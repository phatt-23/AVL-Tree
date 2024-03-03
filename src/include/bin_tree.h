#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <string>
#include <bits/types.h>

class BinTree {
private:
    int         key_m;
    std::string value_m;
    BinTree*    left_m;
    BinTree*    right_m;
    void     _create_left(int key_t, const char* value_t);
    void     _create_rght(int key_t, const char* value_t);
    BinTree* delete_at(BinTree* node_t, int key_t);
    int      get_balance();
    BinTree* balance_out(BinTree* node_t, int key_t);
    BinTree* st_insert(BinTree* node_t, int key_t);
    BinTree* st_insert(BinTree* node_t, int key_t, const std::string& value_t);
    BinTree* st_right_rotate(BinTree* node_t);
    BinTree* st_left_rotate(BinTree* node_t);
    BinTree* min_key_node(const BinTree* node_t) const;

    void create_left(int key_t);
    void create_rght(int key_t);
    void create_left(int key_t, const char* value_t);
    void create_rght(int key_t, const char* value_t);

    void print_ver(int depth_t, int8_t wh_way);

public:
    BinTree();
    BinTree(const char* type_t); // insert "ROOT" as parameter to create root
    BinTree(int key_t);
    BinTree(int key_t, const char* value_t);
    BinTree(int key_t, const std::string& value_t);
    ~BinTree();

    const int& gkey(); 
    const std::string& gval();
    const std::string& gval(int key_t);
    BinTree*& gleft(); 
    BinTree*& grght(); 

    int find_depth();
    int count_at_depth(int depth_t); 
    int count_nodes();

    void grow_by(int n_t);
    void grow_by_rand(int n_t, int high_t, int low_t);
    void print_out();
    void print_ver();
    
    BinTree* search(int key_t);
    BinTree* delete_at(int key_t);

    void avl_insert(BinTree*& root_t, int key_t);
    void avl_insert(BinTree*& root_t, int key_t, const std::string& value_t);
    void random_populate(BinTree*& root_t, size_t n_t, int lo_b, int hi_b);
};

#endif//BIN_TREE_H
