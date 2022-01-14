#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <stack>
#include <map>
#include "LLBigNum.h"

// we set up global variables that will be used by the functions
std::map<std::string, BigNum> container;

Fl_Input inputName(150, 10, 180, 40, "Number name: ");
Fl_Input inputValue(150, 60, 180, 40, "Number value: ");
Fl_Output output(150, 330, 180, 40, "Output : ");
Fl_Browser browser(150, 110, 180, 200);
short counter = 0;

/**
 * @brief This button function will add a number to the browser and the map
 * 
 * @param buttonptr The button calling the function
 */
void buttonAddBN_cb(Fl_Widget* buttonptr) {

    // the number is inserted into the map using the user chosen name as the key
    container.insert(std::pair<std::string, BigNum>(inputName.value(), BigNum(std::stoi(inputValue.value()))));

    // the name is added to the browser
    browser.insert(++counter, inputName.value());

    // the input fields are cleared
    inputName.value("");
    inputValue.value("");
    

}

/**
 * @brief This button adds a + to the browser
 * 
 * @param buttonptr  The button calling the function
 */
void buttonAddOperator_cb(Fl_Widget* buttonptr) {

    // the + operator is added to the browser
    browser.insert(++counter, "+");

}

/**
 * @brief This button adds a * to the browser
 * 
 * @param buttonptr  The button calling the function
 */
void buttonMulOperator_cb(Fl_Widget* buttonptr) {

    // the * operator is added to the browser
    browser.insert(++counter, "*");

}

/**
 * @brief This button adds a ! to the browser
 * 
 * @param buttonptr The button calling the function
 */
void buttonFactOperator_cb(Fl_Widget* buttonptr) {

    // the ! operator is added to the browser
    browser.insert(++counter, "!");

}

/**
 * @brief This button calculates the operation defined in the browser 
 * 
 * @param buttonptr The button calling the function
 */
void buttonCalculate_cb(Fl_Widget* buttonptr) {

    // a stack is used to store the numbers for the RPN style operation
    std::stack<BigNum> numbers;

    // this string will be used to store the names coming out of the browser
    std::string browserOut;


    // a for loop is used to iterate through the browser
    for (short i = 1; i <= counter; i++) {

        // the text at the line is extracted
        browserOut = browser.text(i);

        // the text is matched against the operators
        if (browserOut == "+") {

            // if it is a +, then the first 2 elements from the stack are popped, then the addition is performed
            BigNum a = numbers.top();
            numbers.pop();
            BigNum b = numbers.top();
            numbers.pop();
            // the result of the addition is pushed back onto the stack
            numbers.push(a + b);

        } else if (browserOut == "*") {

            // if it is a *, then the first 2 elements from the stack are popped, then the multiplication is performed
            BigNum a = numbers.top();
            numbers.pop();
            BigNum b = numbers.top();
            numbers.pop();
            // the result of the multiplication is pushed back onto the stack
            numbers.push(a * b);

        } else if (browserOut == "!") {
            
            // if it is a !, then the first element is popped from the stack, then the factorial is performed
            BigNum a = numbers.top();
            numbers.pop();
            // the result is pushed back onto the stack
            numbers.push(factorial(a));

        } else {

            // any number is pushed onto the stack
            numbers.push(container.at(browserOut));

        }

    }

    // the remaining element of the stack is outputted in the output field
    output.value(numbers.top().toString().c_str());

}

/**
 * @brief This button clears the fields 
 * 
 * @param buttonptr The button calling the function
 */
void buttonClear_cb(Fl_Widget* buttonptr) {

    // the browser, output, map and counter are reset
    browser.clear();
    output.value("");
    container = std::map<std::string, BigNum>();
    counter = 0;

}

int main() {

    Fl_Window win(550, 400, "BigNum");
    // Setup the editor

    win.begin();

        // add the UI elements
        win.add(inputName);
        win.add(inputValue);
        win.add(output);
        win.add(browser);

        // adding all of the buttons
        Fl_Button *buttonAddBN = new Fl_Button(360, 10, 140, 40, "Add Number");
        buttonAddBN->callback(buttonAddBN_cb);

        Fl_Button *buttonAddOperator = new Fl_Button(360, 60, 140, 40, "Add + operator");
        buttonAddOperator->callback(buttonAddOperator_cb);

        Fl_Button *buttonMulOperator = new Fl_Button(360, 110, 140, 40, "Add * operator");
        buttonMulOperator->callback(buttonMulOperator_cb);

        Fl_Button *buttonFactOperator = new Fl_Button(360, 160, 140, 40, "Add ! operator");
        buttonFactOperator->callback(buttonFactOperator_cb);

        Fl_Button *buttonCalculate = new Fl_Button(360, 210, 140, 40, "Calculate");
        buttonCalculate->callback(buttonCalculate_cb);

        Fl_Button *buttonClear = new Fl_Button(360, 260, 140, 40, "Clear list");
        buttonClear->callback(buttonClear_cb);


    win.end();

    win.show();

    // running the UI
    return Fl::run();
}