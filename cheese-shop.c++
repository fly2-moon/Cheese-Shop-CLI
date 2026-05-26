/* cheese-shop.cpp */

#include "splashkit.h"
#include "splashkit-arrays.h"
#include "cheese-shop.h"

#include <format>
using std::format, std::invalid_argument;

/* 
        {function}(): public member function
        run_{function}(): private member function
*/


/* utilities */
string formatted_string(string name, double weight, double price)
{
        return format("{}: {:.2f} kg, ${:.2f}", name, weight, price);
}

void draw_title(string title)
{
        for(int i=0; i<35; i++)
                write("=");
        write_line('\n' + title);
        for(int i=0; i<35; i++)
                write("=");
        write('\n');
}

string read_string(string prompt)
{
        write(prompt);
        return read_line();
}

int read_integer(string prompt)
{
        string input = read_string(prompt);
        while (!is_integer(input) || to_integer(input) < 0)
        {
                write_line("Please enter a positive number");
                input = read_string(prompt);
        }
        return to_integer(input);
}

int read_integer_range(string prompt, int min, int max)
{
        string input = read_string(prompt);
        while (!is_integer(input) && !(to_integer(input) < min || to_integer(input) > max))
        {
                write_line("Please enter a number in range (" + to_string(min) + "-" + to_string(max) + ").");
                input = read_string(prompt);
        }
        return to_integer(input);
}

double read_double(string prompt)
{
        string input = read_string(prompt);
        while (!is_double(input) || to_double(input) < 0)
        {
                write_line("Please enter a positive number\n");
                input = read_string(prompt);
        }
        return to_double(input);
}

bool read_boolean(std::string prompt)
{
        string input = read_string(prompt);
        while(!is_integer(input) || (to_integer(input) < 0 && to_integer(input) > 1))
        {
                write_line("Please enter either 0 or 1.");
                input = read_string(input);
        }
        return (input == "1") ? true : false;

}

/* main menu */
void print_interface()
{
        draw_title("Main Menu: ");
        write_line(
                "0. Exit"
                "\n1. Add cheese"
                "\n2. Edit cheese"
                "\n3. Print cheese list"
                "\n4. Customer Order"
        );
}

/* Cheese */
Cheese::Cheese(const std::string &name, double weight, double price_per_kg)
        : name_(name), weight_(weight), price_per_kg_(price_per_kg) {} 

/* get cheese input */
void Cheese::read_cheese()
{
        run_read_cheese();
}

void Cheese::run_read_cheese()
{
        name_ = read_string("Enter cheese name: ");
        weight_ = read_double("Enter weight in stock (kg): ");
        price_per_kg_ = read_double("Enter price per kg (cents): ") / 100;
}

/* update cheese name */
void Cheese::update_name()
{
        run_update_name();
}

void Cheese::run_update_name()
{
        name_ = read_string("Enter new cheese name: ");
}

/* update cheese weight */
void Cheese::update_weight()
{
        run_update_weight();
}

void Cheese::run_update_weight()
{
        weight_ = read_double("Enter new weight in stock (kg): ");
}

/* update cheese price */
void Cheese::update_price()
{
        run_update_price();
}

void Cheese::run_update_price()
{
        price_per_kg_ = read_double("Enter new price per kg (cents): ") / 100;
}

/* decrease cheese weight after adding order*/
void Cheese::decrease_stock(double order_weight)
{
        run_decrease_stock(order_weight);
}

void Cheese::run_decrease_stock(double order_weight)
{
        weight_ -= order_weight;
}

/* Cheese Shop */
Cheese_Shop::Cheese_Shop(const dynamic_array<Cheese> &cheese)
        : cheese_shop_(cheese) {}

const dynamic_array<Cheese> &Cheese_Shop::cheese_shop() const
{
        return cheese_shop_;
}

/* add cheese */
void Cheese_Shop::add_cheese(const Cheese &cheese)
{
        run_add_cheese(cheese);
}

void Cheese_Shop::run_add_cheese(const Cheese &cheese)
{
        add(this->cheese_shop_, cheese);
}

/* edit cheese information */
void Cheese_Shop::edit_cheese()
{
        run_edit_cheese();
}

void Cheese_Shop::run_edit_cheese()
{
        if(length(cheese_shop_) == 0) 
        {
                write_line("No cheese added yet. ");
                return;
        }

        draw_title("Select Cheese: ");
        write_line("0: Select none");
        for(int i = 0; i < length(cheese_shop_); ++i)
        {
                const Cheese &cheese = cheese_shop_[i];
                write_line(
                        to_string(i+1) + ": " +\
                        formatted_string(
                                cheese.name(),\
                                cheese.weight(), \
                                cheese.price_per_kg()
                        )
                );
        }

        int target = read_integer_range(
                "Select Cheese (0-" +\
                to_string(length(cheese_shop_)) + "): ",\
                0, length(cheese_shop_)
        );
        
        if(target == 0){
                write_line("No cheese selected, returning to main menu...");
                return;
        }

        write('\n');
        draw_title("Edit Cheese: ");
        
        Cheese &selected_cheese = cheese_shop_[target-1];
        write_line(
                "Editing Cheese: " +\
                formatted_string(
                        selected_cheese.name(),\
                        selected_cheese.weight(),\
                        selected_cheese.price_per_kg()
                )
        );

        if(read_boolean("Do you want to edit the name? (1 for yes, 0 for no): "))
                selected_cheese.update_name();

        if(read_boolean("Do you want to edit the weight? (1 for yes, 0 for no): "))
                selected_cheese.update_weight();

        if(read_boolean("Do you want to edit the price? (1 for yes, 0 for no): "))
                selected_cheese.update_price();

}

/* print available cheeses */
void Cheese_Shop::print_cheese_list()
{
        run_print_cheese_list();
}

void Cheese_Shop::run_print_cheese_list()
{
        if(length(cheese_shop_) == 0)
        {
                write_line("No cheese added yet. ");
                return;
        }

        draw_title("Cheese stock list: ");
        for(int i = 0; i < length(cheese_shop_); ++i)
        {
                const Cheese &cheese = cheese_shop_[i];
                write_line(
                        formatted_string(
                                cheese.name(),\
                                cheese.weight(), \
                                cheese.price_per_kg()
                        )
                );
        }
}

/* find cheese index in stock */
int Cheese_Shop::find_cheese(const dynamic_array<Cheese> &cheese_shop, const string NAME)
{
        for(int i = 0; i < length(cheese_shop); ++i)
        {
                if(cheese_shop[i].name() == NAME)
                        return i;
        }
        return -1;
}

/* customer menu */
enum menu_order
{
        DONE_ORDER = 0,
        ADD_CHEESE_ORDER = 1,
        EDIT_CHEESE_ORDER = 2,
        REMOVE_CHEESE_ORDER = 3,
        PRINT_ORDER_LIST = 4
};

void print_order_menu()
{
        draw_title("Order Menu: ");
        write_line(
                "0. Done order"
                "\n1. Add cheese to an order"
                "\n2. Edit cheese in an order"
                "\n3. Remove cheese from an order"
                "\n4. Print order list"
        );
}

/* Cheese Shop - option: add customer orders */
void Cheese_Shop::customer_order()
{
        run_customer_order();
}

void Cheese_Shop::run_customer_order()
{
        Order_List order_list({});
        Order new_order("", "", 0, 0);
        menu_order choose_order;
        do
        {
                print_order_menu();
                try
                {
                        choose_order = (menu_order)read_integer_range("Select an option (0-4): ", 0, 4);
                }
                catch (const invalid_argument&)
                {
                        write_line("Please enter a valid option\n");
                        continue;
                }
                write('\n');
                switch (choose_order)
                {
                        case DONE_ORDER:
                                for (int i = 0; i < length(order_list.order_list()); ++i)
                                        order_list.save_order(this->cheese_shop_, i);
                                write_line("Returning to main menu...");
                                return;


                        case ADD_CHEESE_ORDER:
                                if (new_order.read_order(cheese_shop_) != -1)
                                        order_list.add_cheese_order(cheese_shop_, new_order);
                                break;

                        case EDIT_CHEESE_ORDER:
                                order_list.edit_cheese_order(cheese_shop_);
                                break;
                        
                        case REMOVE_CHEESE_ORDER:
                                order_list.remove_cheese_order();
                                break;
                        
                        case PRINT_ORDER_LIST:
                                order_list.print_order_list();
                                break;

                        default:
                                write_line("Please enter a valid option");
                }
                write('\n');

        } while(choose_order != DONE_ORDER);
}

/* Customer Order */
Order::Order(const std::string &customer, const std::string &name, double weight, double price)
        : customer_(customer), name_(name), weight_(weight), price_(price) {} 

/* get order input */
int Order::read_order(dynamic_array<Cheese> &cheese_shop)
{
        read_customer_name();
        int target = read_order_name(cheese_shop);
        if (target != -1 && read_order_weight(cheese_shop[target]) != -1)
                return 0;
        return -1;
}

/* get customer name */
void Order::read_customer_name()
{
        customer_ = read_string("Enter customer name: ");
}

/* get order name */
int Order::read_order_name(const dynamic_array<Cheese> &cheese_shop)
{
        string new_order_name = read_string("Enter cheese name: ");

        /* check is order name available in stock */
        int target = Cheese_Shop::find_cheese(cheese_shop, new_order_name);
        if(target != -1)
        {
                name_ = new_order_name; 
                return target;
        } 
        write_line("No cheese named " + new_order_name + " found, order cancelled");
        return -1;
}

/* get order weight */
int Order::read_order_weight(const Cheese &cheese)
{
        double new_weight = read_double("Enter new weight in stock (kg): ");
        if(new_weight > cheese.weight())
        {
                write_line("Ordered cheese amount exceeds available amount, operation cancelled");
                return -1;
        }
        weight_ = new_weight;
        
        double new_order_price = weight_ * cheese.price_per_kg();
        price_ = new_order_price;
        return 0;
}

/* Order list */
Order_List::Order_List(const dynamic_array<Order> &order_list)
        : order_list_(order_list) {}

const dynamic_array<Order>& Order_List::order_list() const
{
        return order_list_;
}

/* add cheese to order */
void Order_List::add_cheese_order(dynamic_array<Cheese> &cheese_shop, const Order &new_order)
{
        run_add_cheese_order(cheese_shop, new_order);
}

void Order_List::run_add_cheese_order(dynamic_array<Cheese> &cheese_shop, const Order &new_order)
{
        string order_name = new_order.name();
        int target = Cheese_Shop::find_cheese(cheese_shop, order_name);
        if(target != -1) 
        {
                Order order(new_order.customer(), new_order.name(), new_order.weight(), new_order.price());
                add(this->order_list_, new_order);
                write_line("Order successfully added");
        }
}

/* edit customer name */
void Order::update_customer_name()
{
        run_update_customer_name();
}

void Order::run_update_customer_name()
{
        customer_ = read_string("Enter new customer name: ");
}

/* edit order name */
void Order::update_order_name(const dynamic_array<Order> &order_list, const dynamic_array<Cheese> &cheese_shop)
{
        run_update_order_name(order_list, cheese_shop);
}

void Order::run_update_order_name(const dynamic_array<Order> &order_list, const dynamic_array<Cheese> &cheese_shop)
{
        string new_order_name = read_string("Enter new cheese name: ");
        if(Cheese_Shop::find_cheese(cheese_shop, new_order_name) != -1)
        {
                name_ = new_order_name;
                return;
        }
        write_line("No order named \"" + new_order_name + "\" found in cheese shop");
}

/* edit order weight */
void Order::update_order_weight(Cheese &cheese)
{
        run_update_order_weight(cheese);
}

void Order::run_update_order_weight(Cheese &cheese)
{      
        double new_weight = read_double("Enter new weight in stock (kg): ");
        if(new_weight > cheese.weight())
        {
                write_line("Ordered cheese amount exceeds available amount, operation cancelled");
                return;
        }
        weight_ = new_weight;
        update_order_price(cheese);
}

/* update order price after edit weight */
void Order::update_order_price(Cheese &cheese)
{
        run_update_order_price(cheese);
}

void Order::run_update_order_price(Cheese &cheese)
{
        price_ = cheese.price_per_kg() * weight_;
}

/* edit cheese from an order */
void Order_List::edit_cheese_order(dynamic_array<Cheese> &cheese_shop)
{
        run_edit_cheese_order(cheese_shop);
}

void Order_List::run_edit_cheese_order(dynamic_array<Cheese> &cheese_shop)
{
        if(length(order_list_) == 0) 
        {
                write_line("No order added yet. ");
                return;
        }

        draw_title("Select Order: ");
        write_line("0: Select none");
        for(int i = 0; i < length(order_list_); ++i)
        {
                const Order &order = order_list_[i];
                write_line(
                        to_string(i+1) + ": " +\
                        order.customer() + " " +\
                        formatted_string(
                                order.name(),\
                                order.weight(), \
                                order.price()
                        )
                );
        }

        int target = read_integer_range(
                "Select Order (0-" +\
                to_string(length(order_list_)) + "): ",\
                0, length(order_list_)
        );
        
        if(target == 0){
                write_line("No order selected, returning to main menu...");
                return;
        }

        write('\n');
        draw_title("Edit Order: ");
        
        Order &selected_order = order_list_[target-1];
        write_line(
                "Editing Order: " +\
                selected_order.customer() + " " +\
                formatted_string(
                        selected_order.name(),\
                        selected_order.weight(),\
                        selected_order.price()
                )
        );

        if(read_boolean("Do you want to edit customer name? (1 for yes, 0 for no): "))
                selected_order.update_customer_name();

        if(read_boolean("Do you want to edit the name? (1 for yes, 0 for no): "))
                selected_order.update_order_name(order_list_, cheese_shop);

        if(read_boolean("Do you want to edit the weight? (1 for yes, 0 for no): "))
                selected_order.update_order_weight(cheese_shop[target-1]);
}

/* remove cheese from an order */
void Order_List::remove_cheese_order()
{
        run_remove_cheese_order();
}

void Order_List::run_remove_cheese_order()
{
        if(length(order_list_) == 0) 
        {
                write_line("No order added yet. ");
                return;
        }

        draw_title("Select Order: ");
        write_line("0: Select none");
        for(int i = 0; i < length(order_list_); ++i)
        {
                const Order &order = order_list_[i];
                write_line(
                        to_string(i+1) + ": " +\
                        order.customer() + " " +\
                        formatted_string(
                                order.name(),\
                                order.weight(), \
                                order.price()
                        )
                );
        }

        int target = read_integer_range(
                "Select Order (0-" +\
                to_string(length(order_list_)) + "): ",\
                0, length(order_list_)
        );
        
        if(target == 0){
                write_line("No order selected, returning to main menu...");
                return;
        }

        remove(this->order_list_, target - 1);
        write_line("Order removed");
        return;
}

/* view current orders */
void Order_List::print_order_list()
{
        run_print_order_list();
}

void Order_List::run_print_order_list()
{
        if(length(order_list_) == 0)
        {
                write_line("No order added yet. ");
                return;
        }

        draw_title("Order list: ");
        for(int i = 0; i < length(order_list_); ++i)
        {
                const Order &order = order_list_[i];
                write_line(
                        order.customer() + " " +\
                        formatted_string(
                                order.name(),\
                                order.weight(), \
                                order.price()
                        )
                );
        }       
}

/* build receipt for total price */
string Order_List::receipt(double price)
{
        return format("Total price: ${:.2f}", price);
}

/* confirm order, decrease cheese stock, view receipt */
void Order_List::save_order(dynamic_array<Cheese> &cheese_shop, int order_index)
{
        if(order_index < 0 || order_index >= length(order_list_)) return;

        const Order &order = order_list_[order_index];
        int cheese_idx = Cheese_Shop::find_cheese(cheese_shop, order.name());
        if(cheese_idx == -1) return;

        cheese_shop[cheese_idx].decrease_stock(order.weight());

        double total_price = 0;
        draw_title("Cart: ");

        for(int i=0; i<length(order_list_); ++i)
        {
                const Order &order = order_list_[i];
                write_line(
                        order.customer() + " "+\
                        formatted_string(
                                order.name(),\
                                order.weight(), \
                                order.price()
                        )
                );
                total_price += order_list_[i].price();
        }
        
        write_line(receipt(total_price));
}
