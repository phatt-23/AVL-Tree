#include "include/bin_tree.h"

#include <iostream>
#include <iomanip>
#include <functional>
#include <string.h>
#include <limits.h>
#include <cmath>

#if 0
#define DEBUG 1
#else
#define DEBUG 0
#endif

#if 1
#define USEFUL 1
#else
#define USEFUL 0
#endif

#define INFO_T "[INFO] "
#define ERR_T "[ERROR] "
#define BREAK_LINE(len, txt) { for(size_t i{}; i<len; ++i) std::cout << txt; std::cout << std::endl; }
template<typename T> T max(const T& a_val, const T& b_val) { return (a_val > b_val) ? a_val : b_val; }
#define KEY_DEFAULT 0
#define VAL_DEFAULT "none"
#define ROOT_KEY_DEFAULT __INT32_MAX__
#define ROOT_VAL_DEFAULT "roooooooot"

BinTree::BinTree() { // reserved for root initialisation
    this->key_m = KEY_DEFAULT;
    this->value_m = VAL_DEFAULT;
    this->right_m = nullptr;
    this->left_m = nullptr;
}

BinTree::BinTree(const char* type_t) {
    if(!strcmp(type_t, "ROOT")) {
        this->key_m = ROOT_KEY_DEFAULT;
        this->value_m = ROOT_VAL_DEFAULT;
        this->right_m = nullptr;
        this->left_m = nullptr;
    } else BinTree{};
}

BinTree::BinTree(int key_t, const char* value_t) {
    this->key_m = key_t;
    this->value_m = value_t;
    this->right_m = nullptr;
    this->left_m = nullptr;
}

BinTree::BinTree(int key_t, const std::string& value_t) {
    this->key_m = key_t;
    this->value_m = value_t;
    this->right_m = nullptr;
    this->left_m = nullptr;
}

BinTree::BinTree(int key_t) {
    this->key_m = key_t;
    this->value_m = VAL_DEFAULT;
    this->right_m = nullptr;
    this->left_m = nullptr;
}

BinTree::~BinTree() {}

BinTree*& BinTree::gleft() { return this->left_m; }
BinTree*& BinTree::grght() { return this->right_m; }
const int& BinTree::gkey() { return this->key_m; }
const std::string& BinTree::gval() { return this->value_m; }

const std::string NOT_FOUND_STRING_DEFAULT = "(default message) The function 'gval(int key)' found no match!";
const std::string& BinTree::gval(int key_t) {
    BinTree* _node = this->search(key_t);
    return ((key_t != _node->key_m) ? NOT_FOUND_STRING_DEFAULT : _node->value_m);
}


int BinTree::find_depth() {
    std::function<int(BinTree*, int)> find_depth_rec =
    [&](BinTree* tree_lmb, int depth_lmb) -> int {
        if(tree_lmb == nullptr) return depth_lmb;
        else return max(
            find_depth_rec(tree_lmb->left_m, depth_lmb+1), 
            find_depth_rec(tree_lmb->right_m, depth_lmb+1)
        );
    };
    return find_depth_rec(this, 0);
}

int BinTree::count_at_depth(int depth_t) {
    std::function<int(BinTree*, int)> _count_at_depth = [&](BinTree* node_lm, int depth_lm) -> int {
        if(node_lm == nullptr) return 0;
        if(node_lm != nullptr && depth_lm == 0) return 1;
        else return _count_at_depth(node_lm->grght(), depth_lm - 1) + _count_at_depth(node_lm->gleft(), depth_lm - 1); 
    };
    int n_nodes = _count_at_depth(this, depth_t);
    if(DEBUG||USEFUL) 
        std::cout <<INFO_T<<"There "<<((n_nodes == 1) ? "is " : "are ")<<n_nodes
                  <<((n_nodes == 1) ? " node" : " nodes")<<" at depth "<<depth_t<<"."
                  << std::endl;
    return n_nodes;
}

int BinTree::count_nodes() {
    std::function<int(BinTree*)> _count_nodes = [&](BinTree* node_lm) -> int {
        if(node_lm == nullptr) return 0;
        else return 1 + _count_nodes(node_lm->grght()) 
                      + _count_nodes(node_lm->gleft()); 
    };
    int n_nodes = _count_nodes(this);
    if(DEBUG||USEFUL) 
        std::cout <<INFO_T<<"There "<<((n_nodes == 1) ? "is " : "are ")<<n_nodes
                  <<((n_nodes == 1) ? " node" : " nodes")<<" in total."
                  << std::endl;
    return n_nodes; 
}

void BinTree::create_left(int key_t, const char* value_t) { 
    if(this->left_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<< "Creating left node: ("<<this->key_m<<", "<<this->value_m
        <<") -> ("<<key_t<<", "<<value_t<<")"<< std::endl;
        this->left_m = new BinTree(key_t, value_t); 
    } else {
        std::cerr <<ERR_T<< "Left node already set: ("<<this->key_m<<", "<<this->value_m
        <<") \\> ("<<key_t<<", "<<value_t<<")" << std::endl;
    }
}

void BinTree::create_rght(int key_t, const char* value_t) { 
    if(this->right_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<< "Creating right node: ("<<this->key_m<<", "<<this->value_m
        <<") -> ("<<key_t<<", "<<value_t<<")"<< std::endl;
        this->right_m = new BinTree(key_t, value_t); 
    } else {
        std::cerr <<ERR_T<< "Right node already set: ("<<this->key_m<<", "<<this->value_m
        <<") \\> ("<<key_t<<", "<<value_t<<")." << std::endl;
    }
}

void BinTree::create_left(int key_t) { 
    if(this->left_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<< "Creating left node: ("<<this->key_m<<", "<<this->value_m
        <<") -> ("<<key_t<<", "<<VAL_DEFAULT<<")."<< std::endl;
        this->left_m = new BinTree(key_t); 
    } else {
        std::cerr <<ERR_T<< "Left node already set: ("<<this->key_m<<", "<<this->value_m
        <<") \\> ("<<key_t<<", "<<VAL_DEFAULT<<")." << std::endl;
    }
}

void BinTree::create_rght(int key_t) { 
    if(this->right_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<< "Creating right node: ("<<this->key_m<<", "<<this->value_m
        <<") -> ("<<key_t<<", "<<VAL_DEFAULT<<")."<< std::endl;
        this->right_m = new BinTree(key_t); 
    } else {
        std::cerr <<ERR_T<< "Right node already set: ("<<this->key_m<<", "<<this->value_m
        <<") \\> ("<<key_t<<", "<<VAL_DEFAULT<<")." << std::endl;
    }
}

void BinTree::_create_left(int key_t, const char* value_t) { 
    if(this->left_m == nullptr) this->left_m = new BinTree(key_t, value_t); 
}

void BinTree::_create_rght(int key_t, const char* value_t) { 
    if(this->right_m == nullptr) this->right_m = new BinTree(key_t, value_t); 
}

void BinTree::grow_by(int n_t) {
    if(DEBUG||USEFUL) {
        int depth_l = this->find_depth();
        float n_nodes = powf(2, n_t + depth_l) - powf(2, depth_l) + ((!depth_l) ? 1 : 0);
        n_nodes += powf(2, (depth_l - 1)) - this->count_at_depth(depth_l - 1);

        std::cout <<std::fixed<<std::setprecision(0)
                  <<INFO_T<<"This growth will result in "<<n_nodes
                  <<std::scientific<<std::setprecision(2)
                  <<" ("<<n_nodes<<")"
                  <<" new nodes."<< std::endl;
        while(1) {
            std::cout<<"Do you wish to proceed? (y or n) ";
            char reply;
            std::cin >>reply;
            if(reply == 'y' || reply == 'Y') break;
            else if(reply == 'n' || reply == 'N') return;
        }
    }
    int depth_l = this->find_depth();
    if(!n_t) std::cout <<INFO_T<<"Filling in the tree of depth "<<depth_l<<"."<< std::endl;
    else std::cout <<INFO_T<<"Growing the tree by "<<n_t<< ((n_t == 1) ? " layer." : " layers.") << std::endl;
    
    std::function<void(BinTree*, int)> grow_by_rec = 
    [&](BinTree* tree_lmb, int n_lmb) -> void {
        if(n_lmb == 0) return;
        else {
            if(tree_lmb->left_m == nullptr) {
                tree_lmb->_create_left(KEY_DEFAULT, VAL_DEFAULT);
                grow_by_rec(tree_lmb->left_m, n_lmb - 1);
            } else grow_by_rec(tree_lmb->left_m, n_lmb);
            if(tree_lmb->right_m == nullptr) {
                tree_lmb->_create_rght(KEY_DEFAULT, VAL_DEFAULT);
                grow_by_rec(tree_lmb->right_m, n_lmb - 1);
            } else grow_by_rec(tree_lmb->right_m, n_lmb);
        }
    };

    std::function<void(BinTree*, int)> grow_by_rec_fill = 
    [&](BinTree* tree_fill, int depth_fill) -> void {
        if(depth_fill == 0) return;
        else {
            if(tree_fill->left_m == nullptr)  tree_fill->_create_left(KEY_DEFAULT, VAL_DEFAULT);
            if(tree_fill->right_m == nullptr) tree_fill->_create_rght(KEY_DEFAULT, VAL_DEFAULT);
            grow_by_rec_fill(tree_fill->left_m, depth_fill - 1);
            grow_by_rec_fill(tree_fill->right_m, depth_fill - 1);
        }
    };

    grow_by_rec_fill(this, depth_l - 1);
    grow_by_rec(this, n_t);
}

void BinTree::grow_by_rand(int n_t, int high_t, int low_t) {
    int depth_l = this->find_depth();
    if(!n_t) std::cout <<INFO_T<<"Filling in the tree of depth "<<depth_l<<"."<< std::endl;
    else std::cout <<INFO_T<<"Growing the tree by "<<n_t<< ((n_t == 1) ? " layer. (rand key)" : " layers. (rand key)") << std::endl;
    std::function<void(BinTree*, int, int, int)> grow_by_rec = 
    [&](BinTree* tree_lmb, int n_lmb, int high_t, int low_t) -> void {
        if(n_lmb == 0) return;
        else {
            if(tree_lmb->left_m == nullptr) {
                tree_lmb->_create_left(rand() % (high_t - low_t) + low_t, VAL_DEFAULT);
                grow_by_rec(tree_lmb->left_m, n_lmb - 1, high_t, low_t);
            } else grow_by_rec(tree_lmb->left_m, n_lmb,  high_t, low_t);
            if(tree_lmb->right_m == nullptr) {
                tree_lmb->_create_rght(rand() % (high_t - low_t) + low_t, VAL_DEFAULT);
                grow_by_rec(tree_lmb->right_m, n_lmb - 1, high_t, low_t);
            } else grow_by_rec(tree_lmb->right_m, n_lmb,  high_t, low_t);
        }
    };

    std::function<void(BinTree*, int, int, int)> grow_by_rec_fill = 
    [&](BinTree* tree_fill, int depth_fill, int high_t, int low_t) -> void {
        if(depth_fill == 0) return;
        else {
            if(tree_fill->left_m == nullptr)  tree_fill->_create_left(rand() % (high_t - low_t) + low_t, VAL_DEFAULT);
            if(tree_fill->right_m == nullptr) tree_fill->_create_rght(rand() % (high_t - low_t) + low_t, VAL_DEFAULT);
            grow_by_rec_fill(tree_fill->left_m, depth_fill - 1,  high_t, low_t);
            grow_by_rec_fill(tree_fill->right_m, depth_fill - 1, high_t, low_t);
        }
    };

    grow_by_rec_fill(this, depth_l - 1, high_t, low_t);
    grow_by_rec(this, n_t, high_t, low_t);
}

void BinTree::print_out() {
    std::cout <<INFO_T<< "Printing out tree:" << std::endl;
    std::function<void(BinTree*, size_t, int)> print_out_rec = 
    [&](BinTree* tree_lm, size_t depth_lm, int wh_way) -> void {
        if(tree_lm == nullptr) return;
        else {
            std::cout << "(" <<depth_lm<< ")";
            for(size_t i=0; i < depth_lm; ++i) std::cout << "   ";
            std::string wh_way_str = (wh_way > 0) ? "RGHT " : "LEFT ";
            if(!wh_way) wh_way_str = "(ROOT) ";
            std::cout <<wh_way_str<< "(" <<tree_lm->key_m<< ", " <<tree_lm->value_m<< ")" << std::endl;
            if(tree_lm->left_m != nullptr)  print_out_rec(tree_lm->left_m, depth_lm+1, -1);
            if(tree_lm->right_m != nullptr) print_out_rec(tree_lm->right_m, depth_lm+1, 1);
        }
    };
    print_out_rec(this, 0, 0);
    BREAK_LINE(60, "-");
}

#define PADDING 5

void BinTree::print_ver(int depth_t, int8_t wh_way) {
    depth_t++; 
    if(this->right_m != nullptr) this->right_m->print_ver(depth_t, -1);

    std::cout <<" "<<(depth_t - 1)<<" ";
    std::cout <<( ( (depth_t - 1) < 100) ? ( ( (depth_t - 1) < 10 ) ? "  " : " ") : "" );
    std::cout <<( (!wh_way) ? "/    " : ((wh_way > 0) ? "l    " : "r    ") );
    for(int i=0; i<(depth_t - 1)*PADDING; ++i) {
        if(i % PADDING == 0) std::cout <<".";
        else std::cout <<" ";
    }
    std::cout <<"|"<<this->key_m<<" "<<this->value_m<<" "<< std::endl;

    if(this->left_m != nullptr) this->left_m->print_ver(depth_t, 1);
}

void BinTree::print_ver() {
    static auto show_levels = [](size_t n_depth){
        std::cout <<"(LEVELS) ";
        for(size_t i = 0; i < n_depth; ++i) {
            std::cout <<"{"<<i<<"}";
            for(size_t j = 3; j < PADDING; ++j) std::cout <<" ";
        }
        std::cout << std::endl;
    };

    static auto break_line = [](size_t n_depth) {
        for(size_t i = 0; i < (n_depth+5)*PADDING; ++i) std::cout <<"-";
        std::cout << std::endl;
    };

    size_t n_depth = this->find_depth();
    std::cout <<INFO_T<<"Printing a vertical diagram deep "<<n_depth<<" nodes."<< std::endl;

    break_line(n_depth);
    show_levels(n_depth);
    break_line(n_depth);
    
    this->print_ver(0,0);

    break_line(n_depth);
    show_levels(n_depth);
    break_line(n_depth);
}


int BinTree::get_balance() {  
    int l_d = (this->left_m != nullptr) ? this->left_m->find_depth() : 0;
    int r_d = (this->right_m != nullptr) ? this->right_m->find_depth() : 0;  
    return l_d - r_d;
}

BinTree* BinTree::st_right_rotate(BinTree* node_t) {
    if(node_t == nullptr) {
        if(DEBUG) std::cout <<INFO_T<< "rotate right -> node_t = null\n";
        return node_t;
    } 
    if(DEBUG) std::cout <<INFO_T<<"Right rotate on node ("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
    if(node_t->left_m == nullptr && node_t->right_m == nullptr) {
        std::cout <<INFO_T<<"node_t.right = null && node_t.left = null\n";
    } else if(node_t->left_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"node_t.left = null\n";
        BinTree *y, *x;
        y = node_t;
        x = node_t->left_m;  
        x = y;  
        y = x;  
        return x;  
    } else if(node_t->right_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"node_t.right = null\n";
    }
    BinTree *y, *x, *z;
    y = node_t;
    x = node_t->left_m;
    z = node_t->left_m->right_m;  
    x->right_m = y;  
    y->left_m = z;  
    return x;  
}

BinTree* BinTree::st_left_rotate(BinTree* node_t) {
    if(node_t == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"rotate left -> node_t = null\n";
        return node_t;
    } else
    if(DEBUG) std::cout <<INFO_T<<"Left rotate on node ("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
    if(node_t->left_m == nullptr && node_t->right_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"node_t.right = null && node_t.left = null\n";
    } else if(node_t->left_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"node_t.left = null\n";
    } else if(node_t->right_m == nullptr) {
        if(DEBUG) std::cout <<INFO_T<<"node_t.right = null\n";
        BinTree *x, *y; 
        x = node_t;
        y = node_t->right_m;  
        y = x;  
        x = y;  
        return y;
    }
    BinTree *x, *y, *z; 
    x = node_t;
    y = node_t->right_m;  
    z = node_t->right_m->left_m;  
    y->left_m = x;  
    x->right_m = z;  
    return y;  
}

BinTree* BinTree::balance_out(BinTree* node_t, int key_t) {
    int balance = node_t->get_balance();
    if(DEBUG) std::cout <<INFO_T<<"Balance of "<<balance<<" at node ("<<node_t->key_m<<", "<<node_t->value_m<<")"<< std::endl;

    if(balance > 1 && key_t < node_t->left_m->key_m) {
        if(DEBUG) std::cout <<INFO_T<<"Performing left left case on "
                            <<"("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
        return st_right_rotate(node_t);  
    } else if(balance < -1 && key_t > node_t->right_m->key_m) {  
        if(DEBUG) std::cout <<INFO_T<<"Performing right right case on "
                            <<"("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
        return st_left_rotate(node_t);  
    } else if(balance > 1 && key_t > node_t->left_m->key_m) {  
        if(DEBUG) std::cout <<INFO_T<<"Performing left right case on "
                            <<"("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
        node_t->left_m = st_left_rotate(node_t->left_m);  
        return st_right_rotate(node_t);
    } else if(balance < -1 && key_t < node_t->right_m->key_m) {  
        if(DEBUG) std::cout <<INFO_T<<"Performing right left case on "<< std::endl
                            <<"("<<node_t->key_m<<", "<<node_t->value_m<<")."<< std::endl;
        node_t->right_m = st_right_rotate(node_t->right_m);
        return st_left_rotate(node_t);
    }      
    return node_t;  
}

BinTree* BinTree::st_insert(BinTree* node_t, int key_t) {
    if(node_t == nullptr) {
        if(DEBUG||USEFUL) std::cout <<INFO_T<<"Inserted node "<<"("<<key_t<<", "<<VAL_DEFAULT<<")."<< std::endl;
        return new BinTree(key_t);  
    }
    else if(node_t->key_m == ROOT_KEY_DEFAULT) {
        if(DEBUG||USEFUL) std::cout <<INFO_T<<"Inserted node "<<"("<<key_t<<", "<<VAL_DEFAULT<<")."<< std::endl;
        node_t->key_m = key_t;
        return node_t;
    }
    else if(key_t < node_t->key_m) node_t->left_m = st_insert(node_t->left_m, key_t);  
    else if(key_t > node_t->key_m) node_t->right_m = st_insert(node_t->right_m, key_t);  
    else {
        std::cout <<"Do nothing, already have "<<key_t<< std::endl;
        return node_t;  
    }
    return balance_out(node_t, key_t);
}

BinTree* BinTree::st_insert(BinTree* node_t, int key_t, const std::string& value_t) {
    if(node_t == nullptr) { 
        if(DEBUG||USEFUL) std::cout <<INFO_T<<"Inserted node "<<"("<<key_t<<", "<<value_t<<")."<< std::endl;
        return new BinTree(key_t, value_t);  
    }
    else if(node_t->key_m == ROOT_KEY_DEFAULT) {
        if(DEBUG||USEFUL) std::cout <<INFO_T<<"Inserted node "<<"("<<key_t<<", "<<value_t<<")."<< std::endl;
        node_t->key_m = key_t;
        node_t->value_m = value_t;
        return node_t;
    }
    else if(key_t < node_t->key_m) node_t->left_m = st_insert(node_t->left_m, key_t, value_t);  
    else if(key_t > node_t->key_m) node_t->right_m = st_insert(node_t->right_m, key_t, value_t);  
    else {
        std::cout <<"Do nothing, already have "<<key_t<< std::endl;
        return node_t;  
    }
    return balance_out(node_t, key_t);
}

BinTree* BinTree::search(int key_t) {
    if(key_t < this->key_m) {
        if(DEBUG) std::cout <<INFO_T<<"Less than "<<this->key_m<<"."<< std::endl;
        if(this->left_m != nullptr) return this->left_m->search(key_t);
    } else if(key_t > this->key_m) {
        if(DEBUG) std::cout <<INFO_T<<"Greater than "<<this->key_m<<"."<< std::endl;
        if(this->right_m != nullptr) return this->right_m->search(key_t);
    } else if(key_t == this->key_m) {
        if(DEBUG) std::cout <<INFO_T<<"Node with key "<<key_t<<" found."<< std::endl;
        return this;
    } 
    std::cout <<INFO_T<<"Element with key "<<key_t<<" not found!"<< std::endl;
    std::cout <<INFO_T<<"Returning the closest node -> ("<<this->key_m<<", "<<this->value_m<<")." << std::endl;
    return this;
}

BinTree* BinTree::min_key_node(const BinTree* node_t) const {
    if(node_t == nullptr) return const_cast<BinTree*>(node_t);
    const BinTree* curr = node_t;
    while(curr && curr->left_m != nullptr) {
        curr = curr->left_m;
    }
    return const_cast<BinTree*>(curr);
}

BinTree* BinTree::delete_at(BinTree* node_t, int key_t) {
    if(node_t == nullptr) {
        std::cout <<ERR_T<<"Node "<<"("<<key_t<<")"<<" for deletion not found!"<< std::endl;
        return node_t;
    } else if(key_t < node_t->key_m) {
        node_t->left_m = delete_at(node_t->left_m, key_t);
    } else if(key_t > node_t->key_m) {
        node_t->right_m = delete_at(node_t->right_m, key_t);
    } else if(key_t == node_t->key_m) {
        if(DEBUG||USEFUL) 
            std::cout <<INFO_T<<"Node ("<<node_t->key_m<<", "<<node_t->value_m<<") successfully deleted."<< std::endl;
        if((node_t->left_m == nullptr) || (node_t->right_m == nullptr)) {
            BinTree* tmp = node_t->left_m ? node_t->left_m : node_t->right_m;
            if (tmp == nullptr) {
                tmp = node_t;
                node_t = nullptr;
            } else *node_t = *tmp; 
            delete tmp; 
        } else {
            BinTree* tmp = min_key_node(node_t->right_m);
            node_t->key_m = tmp->key_m;
            node_t->value_m = tmp->value_m;
            node_t->right_m = delete_at(node_t->right_m, tmp->key_m);
        }
    }
    if(node_t == nullptr) return node_t;
    return balance_out(node_t, key_t);
}

BinTree* BinTree::delete_at(int key_t) {
    std::cout <<INFO_T<<"Deleting node ("<<key_t<<")."<< std::endl;
    BinTree* node_t = this;
    return node_t->delete_at(node_t, key_t);
}

void BinTree::avl_insert(BinTree*& root_t, int key_t, const std::string& value_t) {
    root_t = st_insert(root_t, key_t, value_t);
}

void BinTree::avl_insert(BinTree*& root_t, int key_t) {
    root_t = st_insert(root_t, key_t);
}

void BinTree::random_populate(BinTree*& root_t, size_t n_t, int lo_b, int hi_b) {
    for(size_t i=0; i<n_t; ++i) {
        int key_l = rand() % (hi_b - lo_b) + lo_b;
        root_t->avl_insert(root_t, key_l);
    }
}
