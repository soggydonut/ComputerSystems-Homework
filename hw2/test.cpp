#include <cstdlib>
#include <cassert>
#include <iostream>
#include <exception>

#include "cache.h"

using namespace std;

void pass(string name) {
    cout << "[*] PASSED " << name << "\n";
}

void fail(string name) {
    cout << "[X] FAILED " << name << "\n";
}

/*
 * Component tests
 */

// test vanilla cache functions (before part 5)
// requires: USING_CUSTOM_EVICTION_ = false
void vanilla_test() {
    string testname = "vanilla test";
    
    Cache* cache = new Cache(4);
    
    // setting
    cache->set("a", "a", 3);
    cache->set("b", "b", 1);

    // getting
    cache->get("a", 3);
    cache->get("b", 1);
        
    // space used
    assert (cache->space_used() == 3 + 1);
    
    // eviction (remove largest)
    cache->set("c", "c", 1);
    assert (cache->space_used() == 2);
    
    // deleting
    cache->del("b");
    cache->del("c");
    cache->space_used();
    assert (cache->space_used() == 0);
        
    cache = new Cache(3);
    
    cache->set("b", "b", 1);
    cache->set("a", "a", 2);
    cache->set("c", "c", 1);
    
    assert (cache->space_used() == 2);
    
    // should have evicted "a"
    try {
        cache->get("a", 2);
        pass(testname);
    } catch (char const* msg) {
        fail(testname);
    }
}

void eviction_FIFO_test() {
    string testname = "eviction FIFO test";
    
    Cache * cache = new Cache(3);
    
    cache->set("a", "a", 2);
    cache->set("b", "b", 1);
    cache->set("c", "c", 1);
    
    // should have evicted the "a"
    // as it was put in first
        
    try {
        cache->get("a", 2);
        fail(testname);
    } catch (char const* msg) {
        pass(testname);
    }
    
}

// resizing test (part 5)
// requires: USING_RESIZING_ = true
void resizing_test() {
    
    Cache* cache = new Cache(2);
    
    cache->set("a", "a", 1);
    cache->set("b", "b", 1);
    assert (cache->space_used() == 2);
    
    cache->set("c", "c", 1);
    assert (cache->space_used() == 3);
    
    pass("resizing test");
}


/*
 * UNIT TEST
 */
void unit_test() {
    cout << "UNIT TEST:\n";
    vanilla_test();
    // resizing_test();
    // eviction_FIFO_test();
}