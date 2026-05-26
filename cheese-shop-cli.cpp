#include "splashkit.h"
#include "cheese-shop.h"

#include <stdexcept>
using std::invalid_argument;

enum option
{
        EXIT = 0,
        ADD_CHEESE = 1,
        EDIT_CHEESE = 2,
        PRINT_CHEESE_LIST = 3,
        CUSTOMER_ORDER = 4
};

int main(void)
{
        option choice;
        Cheese cheese("", 0, 0);
        Cheese_Shop cheese_shop({});
        do
        {
                print_interface();
                try
                {
                        choice = (option)read_integer_range("Select an option (0-4): ", 0, 4);
                }
                catch (const invalid_argument&)
                {
                        write_line("Please enter a valid option\n");
                        continue;
                }
                write('\n');
                switch (choice)
                {
                        case EXIT:
                                write_line("Exiting...");
                                return 0;

                        case ADD_CHEESE:
                                cheese.read_cheese();
                                cheese_shop.add_cheese(cheese);
                                break;

                        case EDIT_CHEESE:
                                cheese_shop.edit_cheese();
                                break;
                        
                        case PRINT_CHEESE_LIST:
                                cheese_shop.print_cheese_list();
                                break;

                        case CUSTOMER_ORDER:
                                cheese_shop.customer_order();
                                break;

                        default:
                                write_line("Please enter a valid option");
                }
                write('\n');
        } while (choice != EXIT);
}
