# Pargs

Pargs, **P**arse **arg**ument**s**, is a light-weight, dependency-free library that parses and validates command-line arguments. It abstracts away the intricacies and provides a intuitive and powerful API to parse and validate arguments.

## Features
- `pargs::expect(arguement)`: notifies program if the expected argument is not present
- `pargs::expect(argument, validate_lambda)`: notifies program if the expected argument fails custom validation (for example: a string is passed when a float is expected; see Usage for more examples)
- `pargs::help_asked()`: Output a usage/help message when prompted
- `pargs::get_or_default(argument, default_value)`: If a non-required argument is missing, default to a pre-defined value

## Usage
##### test.cpp
```
#include <pargs>
#include <iostream>

int main(int argc, char** argv) {
    pargs_n::pargs args(argc, argv);
    args.expect("test");        // Expect a "test" flag
    args.expect("testString");  // Expect a "testString" argument
    args.expect("testInteger"); // Expect a "testInteger" argument

    pargs_n::functor lambda = [](std::string arg) {
        if (arg == "true") {
            return true;
        } else {
            return false;
        }
    };

	// Expect a "testFunctor" argument with a custom validation lambda
    args.expect("testFunctor", lambda);

    bool parse_valid = args.parse();

	// Check if expected arguments are provided
    if (!parse_valid) {
        std::cerr << "Invalid arguments" << std::endl;
        exit(1);
    } else {
    	// If non-required argument "someVal" is provided, get its value
        // or default to the string "default_val"
        std::string some_val = args.get_arg_or_default("someVal", "default_val");

        // Get expected (required) arguments
        std::string test_string = args.get_arg("testString");
        int test_integer = stoi(args.get_arg("testInteger"));
        std::string test_functor = args.get_arg("testFunctor");

        std::cout << "someVal: " << some_val << std::endl;
        std::cout << "testString: " << test_string << std::endl;
        std::cout << "testInteger: " << test_integer << std::endl;
        std::cout << "testFunctor: " << test_functor << std::endl;
    }

    return 0;
}
```
##### Output
Positive Example
```
$ ./test --testInteger=100 --testString=hello --test --testFunctor=true

someVal: default_val
testString: hello
testInteger: 100
testFunctor: true
```

Negative Example: Fail custom validation
```
$ ./test --testInteger=100 --testString=hello --test --testFunctor=false

Invalid arguments
```

Negative Example: Expected "test" flag missing
```
$ ./test --testInteger=100 --testString=hello --testFunctor=true

Invalid arguments
```

Positive Example: someVal flag passed
```
$ ./test --someVal=override_default_val --testInteger=100 --testString=hello --test --testFunctor=true

someVal: override_default_val
testString: hello
testInteger: 100
testFunctor: true
```
