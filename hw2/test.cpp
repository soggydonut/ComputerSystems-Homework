#include <cstdlib>
#include <cassert>
#include <iostream>
#include "cache.h"

/*
 * UNIT TEST
 */
void unit() {
    
}

// test basic cache functions
void basic() {
    
    Cache* cache = new Cache(6);
    
    Cache::key_type k0 = "a";
    Cache::val_type v0 = "a";
    Cache::index_type s0 = 1;
    
    Cache::key_type k1 = "b";
    Cache::val_type v1 = "b";
    Cache::index_type s1 = 2;
    
    // setting
    
    cache->set(k0, v0, s0);
    cache->set(k1, v1, s1);
    
    std::cout << &v0 << "\n" << cache->get(k0, s0);
            
    // getting
//    assert (cache->get("a", 1) == "a");
//    assert (cache->get("b", 2) == "b");
//    assert (cache->get("c", 3) == "c");
    
    // space used
    assert (cache->space_used() == s0 + s1);
    
    // deleting
    cache->del("a");
    cache->del("b");
    cache->del("c");
    assert (cache->space_used() == 0);
    
}