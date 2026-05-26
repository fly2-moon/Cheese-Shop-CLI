# Cheese-Shop-CLI
sample programming project with splashkit library in C++

goal: cheese shop manages cheese stock and customer orders

cheese-shop-cli.c++: user interface for command line program that runs in terminal \
cheese-shop-test.c++: unit test program for member functions in cheese-shop.c++ \
cheese-shop.c++: main procedures for cheese and order management \
cheese-shop.h: essential utilities \

0.   required tools to setup splashkit: <code> curl git clang </code>

1.    Follow guide to install libraries "splashkit" and "splashkit-arrays" with any terminal for your OS \
for GNU/Linux: https://programmers.guide/book/appendix/0-manual-installation/2-0-setup-linux/ \
for Windows: https://programmers.guide/book/appendix/0-manual-installation/2-5-setup-win-msys/ \
for Mac OS: https://programmers.guide/book/appendix/0-manual-installation/2-1-setup-macos/

2.    clone the repository: \
<code>git clone https://github.com/twilight-24-7/Cheese-Shop-CLI.git</code>

4.    compile and run: \
(cheese-shop-cli.c++) \
<code>clang++ cheese-shop.c++ cheese-shop-cli.c++ -o cheese-shop-cli -std=c++23 -l SplashKit -Wall </code> \
<code>./cheese-shop-cli</code>

(cheese-shop-test.c++) \
<code>clang++ cheese-shop.c++ cheese-shop-test.c++ -o cheese-shop-test -std=c++23 -l SplashKit  -Wall</code> \
<code>./cheese-shop-test</code>
