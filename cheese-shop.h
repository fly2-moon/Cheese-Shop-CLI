#include "splashkit-arrays.h"

#ifndef CHEESE_SHOP_H
#define CHEESE_SHOP_H

/*
        {function}(): public member function
        run_{function}(): private member function
*/

class Cheese
{
        public:
                Cheese(const std::string &name, double weight, double price_per_kg);
                const std::string &name() const
                {
                        return name_;
                }
               
                const double weight() const
                {
                        return weight_;
                }
               
                const double price_per_kg() const
                {
                        return price_per_kg_;
                }

                void read_cheese();
                void update_name();
                void update_weight();
                void update_price();

                void update_cheese_weight(double old_value, double new_value);
                void update_cheese_price_per_kg(double old_value, double new_value);
                void decrease_stock(double order_weight);
     
        private:
                std::string name_;
                double weight_;
                double price_per_kg_;

                void run_read_cheese();
                void run_update_name();
                void run_update_weight();
                void run_update_price();

                void run_decrease_stock(double order_weight);
                void run_update_cheese_weight(double old_value, double new_value);
                void run_update_cheese_price_per_kg(double old_value, double new_value);
};

class Cheese_Shop
{
        public:
                Cheese_Shop(const dynamic_array<Cheese> &cheese_shop);
                const dynamic_array<Cheese> &cheese_shop() const;

                void add_cheese(const Cheese &cheese);
                void edit_cheese();
                void print_cheese_list();
                void customer_order();

                static int find_cheese(const dynamic_array<Cheese> &cheese_shop, const std::string name);
       
        private:
                dynamic_array<Cheese> cheese_shop_;

                void run_add_cheese(const Cheese &cheese);
                void run_edit_cheese();
                void run_print_cheese_list();
                void run_customer_order();
};

class Order
{
        public:
                Order(const std::string &customer, const std::string &name, double weight, double price);
                const std::string &customer() const
                {
                        return customer_;
                }

                const std::string &name() const
                {
                        return name_;
                }

                const double weight() const
                {
                        return weight_;
                }

                const double price() const
                {
                        return price_;
                }
                
                int read_order(dynamic_array<Cheese> &cheese_shop);
                void update_customer_name();
                void update_order_name(const dynamic_array<Order> &order_list, const dynamic_array<Cheese> &cheese_shop);
                void update_order_weight(Cheese &cheese);
                void update_order_price(Cheese &cheese);

        private:
                std::string customer_;
                std::string name_;
                double weight_;
                double price_;

                void read_customer_name();
                int read_order_name(const dynamic_array<Cheese> &cheese_shop);
                int read_order_weight(const Cheese &cheese);
                void run_update_customer_name();
                void run_update_order_name(const dynamic_array<Order> &order_list, const dynamic_array<Cheese> &cheese_shop);
                void run_update_order_weight(Cheese &cheese);
                void run_update_order_price(Cheese &cheese);
};

class Order_List
{
        public:
                Order_List(const dynamic_array<Order> &order_list);
                const dynamic_array<Order> &order_list() const;

                void add_cheese_order(dynamic_array<Cheese> &cheese_shop, const Order &new_order);
                void edit_cheese_order(dynamic_array<Cheese> &cheese_shop);
                void remove_cheese_order();
                void print_order_list();
                void save_order(dynamic_array<Cheese> &cheese_shop, int order_index);

        private:
                dynamic_array<Order> order_list_;
                std::string receipt(double total_price);
                void run_add_cheese_order(dynamic_array<Cheese> &cheese_shop, const Order &new_order);
                void run_edit_cheese_order(dynamic_array<Cheese> &cheese_shop);
                void run_remove_cheese_order();
                void run_print_order_list();
};

void print_interface();
void print_order_menu();

string formatted_string(string name, double weight, double price_per_kg);
std::string read_string(std::string prompt);

int read_integer(std::string prompt);
int read_integer_range(std::string prompt, int min, int max);

double read_double(std::string prompt);
bool read_boolean(std::string prompt);
#endif
