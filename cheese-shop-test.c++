/* cheese-shop-test.cpp */

#include <cassert>
#include <iostream>
#include "cheese-shop.h"

int main() {
    // --- Create sample cheeses ---
    Cheese brie("Brie", 5.0, 20.0);       // 5 kg in stock, $20/kg
    Cheese cheddar("Cheddar", 3.0, 15.0); // 3 kg in stock, $15/kg

    // --- Initialize shop and add cheeses ---
    dynamic_array<Cheese> initial_cheeses({});
    Cheese_Shop shop(initial_cheeses);

    assert(length(shop.cheese_shop()) == 0);

    shop.add_cheese(brie);
    shop.add_cheese(cheddar);

    assert(length(shop.cheese_shop()) == 2);
    assert(Cheese_Shop::find_cheese(shop.cheese_shop(), "Brie") != -1);
    assert(Cheese_Shop::find_cheese(shop.cheese_shop(), "Cheddar") != -1);
    assert(Cheese_Shop::find_cheese(shop.cheese_shop(), "Gouda") == -1);

    // --- Test decreasing stock on a Cheese (cast away const if necessary) ---
    int idx_brie = Cheese_Shop::find_cheese(shop.cheese_shop(), "Brie");
    assert(idx_brie != -1);
    double brie_before = shop.cheese_shop()[idx_brie].weight();
    // shop.cheese_shop() may return a const array or element; cast to non-const to call mutating method
    const_cast<Cheese&>(shop.cheese_shop()[idx_brie]).decrease_stock(1.5);
    double brie_after = shop.cheese_shop()[idx_brie].weight();
    assert(brie_after == brie_before - 1.5);

    // --- Orders and Order_List basic operations ---
    dynamic_array<Order> empty_orders({});
    Order_List orders(empty_orders);
    assert(length(orders.order_list()) == 0);

    // Create an Order for 1 kg Cheddar and add it to orders
    Order cheddar_order("Alice", "Cheddar", 1.0, 1.0 * cheddar.price_per_kg());
    orders.add_cheese_order(const_cast<dynamic_array<Cheese>&>(shop.cheese_shop()), cheddar_order);

    assert(length(orders.order_list()) == 1);
    assert(orders.order_list()[0].name() == "Cheddar");
    assert(orders.order_list()[0].weight() == 1.0);

    // save_order should reduce stock of the corresponding cheese
    int cheddar_idx = Cheese_Shop::find_cheese(shop.cheese_shop(), "Cheddar");
    assert(cheddar_idx != -1);
    double cheddar_before = shop.cheese_shop()[cheddar_idx].weight();
    orders.save_order(const_cast<dynamic_array<Cheese>&>(shop.cheese_shop()), 0);
    double cheddar_after = shop.cheese_shop()[cheddar_idx].weight();
    assert(cheddar_after == cheddar_before - 1.0);

    // --- Order price update (cast element to non-const for method that expects non-const Cheese&) ---
    Order o2("Bob", "Brie", 2.0, 0.0); // price initially 0
    o2.update_order_price(const_cast<Cheese&>(shop.cheese_shop()[idx_brie]));
    assert(o2.price() == shop.cheese_shop()[idx_brie].price_per_kg() * o2.weight());

    // --- Find order and basic list behaviour ---
    // Add another cheddar order to test find_order
    orders.add_cheese_order(const_cast<dynamic_array<Cheese>&>(shop.cheese_shop()), cheddar_order);
    assert(length(orders.order_list()) == 2);

    std::cout << "All tests passed.\n";
    return 0;
}
