#include <pargs/pargs.h>
#include <iostream>

int main(int argc, char** argv) {
    pargs_n::pargs args(argc, argv);
    args.expect("test");
    args.expect("testString");
    args.expect("testInteger");

    pargs_n::functor fn = [](std::string arg) {
        if (arg == "true") {
            return true;
        } else {
            return false;
        }
    };

    args.expect("testFunctor", fn);

    bool parse_valid = args.parse();

    if (!parse_valid) {
        std::cerr << "Invalid arguments" << std::endl;
        exit(1);
    } else {
        std::string some_val = args.get_arg_or_default("someVal", "default_val");
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