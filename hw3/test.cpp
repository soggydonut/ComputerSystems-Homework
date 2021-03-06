#include "catch.h"
#include "cache.h"
#include <cstdlib>
#include <iostream>

TEST_CASE("Setting") {
    Cache* cache = new Cache(10);

    // set first key-value-size
    cache->set("a", "a", 1);

    // set subsequent key-value-size
    cache->set("b", "b", 2);
}

TEST_CASE("Setting and Tracking Memory Used") {
    Cache* cache = new Cache(10);
    REQUIRE(cache->space_used() == 0);

    // add first value
    cache->set("a", "a", 1);
    REQUIRE(cache->space_used() == 1);

    // add new value
    cache->set("b", "b", 1);
    REQUIRE(cache->space_used() == 2);

    // rewrite size of value
    cache->set("a", "a", 2);
    REQUIRE(cache->space_used() == 3);
}

TEST_CASE("Evicting (arbitrary implementation)") {
    Cache* cache = new Cache(10);

    cache->set("a", "a", 5);
    cache->set("b", "b", 10);

    REQUIRE(cache->space_used() <= 10);
}

TEST_CASE("Respecting Max Memory") {
    Cache* cache = new Cache(10);

    cache->set("a", "a", 5);
    cache->set("b", "b", 5);
    REQUIRE(cache->space_used() == 10);

    cache->set("c", "c", 5);
    REQUIRE(cache->space_used() == 10);
}

TEST_CASE("Getting") {
    Cache* cache = new Cache(10);
    Cache::index_type size;

    // get newly added value
    cache->set("a", "a", 1);
    cache->get("a", size);

    // get previous values
    cache->set("b", "b", 1);
    cache->get("b", size);
    cache->get("a", size);
}

TEST_CASE("Getting Size") {
    Cache* cache = new Cache(10);
    Cache::index_type size;

    // retrieve size appropriately
    cache->set("a", "a", 1);
    cache->get("a", size);
    REQUIRE(size == 1);

    // rewrite size appropriately
    cache->set("a", "b", 4);
    cache->get("a", size);
    REQUIRE(size == 4);
}

TEST_CASE("Deleting") {
    Cache* cache = new Cache(10);
    Cache::index_type size;

    cache->set("a", "a", 1);
    cache->set("b", "b", 4);

    // deleting different values
    cache->del("a");
    REQUIRE(cache->get("a", size) == NULL);
    cache->del("b");
    REQUIRE(cache->get("b", size) == NULL);

    // re-add-del a deleted value
    cache->set("a", "a", 1);
    cache->del("a");
    REQUIRE(cache->get("a", size) == NULL);
}

TEST_CASE("Deleting and Tracking Memory Used") {
    Cache* cache = new Cache(10);

    cache->set("a", "a", 1);
    cache->set("b", "b", 4);

    cache->del("a");
    REQUIRE(cache->space_used() == 4);
    cache->del("b");
    REQUIRE(cache->space_used() == 0);

    // re-add-del a deleted value
    cache->set("a", "a", 1);
    cache->del("a");
    REQUIRE(cache->space_used() == 0);
}