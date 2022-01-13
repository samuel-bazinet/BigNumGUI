#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <stack>
#include <map>
#include "LLBigNum.h"

std::map<std::string, BigNum> container;

Fl_Input inputName(150, 10, 180, 40, "Number name: ");
Fl_Input inputValue(150, 60, 180, 40, "Number value: ");
Fl_Output output(150, 330, 180, 40, "Output : ");
Fl_Browser browser(150, 110, 180, 200);
short counter = 0;

void buttonAddBN_cb(Fl_Widget* buttonptr) {

    container.insert(std::pair<std::string, BigNum>(inputName.value(), BigNum(std::stoi(inputValue.value()))));
    browser.insert(++counter, inputName.value());
    inputName.value("");
    inputValue.value("");
    

}

void buttonAddOperator_cb(Fl_Widget* buttonptr) {

    browser.insert(++counter, "+");

}

void buttonMulOperator_cb(Fl_Widget* buttonptr) {

    browser.insert(++counter, "*");

}

void buttonFactOperator_cb(Fl_Widget* buttonptr) {

    browser.insert(++counter, "!");

}

void buttonCalculate_cb(Fl_Widget* buttonptr) {

    std::stack<BigNum> numbers;

    std::string browserOut;

    for (short i = 1; i <= counter; i++) {

        browserOut = browser.text(i);

        if (browserOut == "+") {

            BigNum a = numbers.top();
            numbers.pop();
            BigNum b = numbers.top();
            numbers.pop();
            numbers.push(a + b);

        } else if (browserOut == "*") {

            BigNum a = numbers.top();
            numbers.pop();
            BigNum b = numbers.top();
            numbers.pop();
            numbers.push(a * b);

        } else if (browserOut == "!") {

            BigNum a = numbers.top();
            numbers.pop();
            numbers.push(factorial(a));

        } else {

            numbers.push(container.at(browserOut));

        }

    }
    output.value(numbers.top().toString().c_str());

}

void buttonClear_cb(Fl_Widget* buttonptr) {

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

    return Fl::run();
}