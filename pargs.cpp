#include "pargs.h"

#include <iostream>

#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace pargs_n {
    struct pair_t {
        string key;
        string val;
    };

    bool verify_expected_arguments(std::map<std::string, std::string>* arguments,
                                   std::vector<std::string>* expected_arguments,
                                   std::map<std::string, functor>* expected_functor_map);
    bool is_argument(char *long_arg);
    pair_t get_argument(char *long_arg);

    pargs::pargs(int arg_count, char **arg_value)
            : argc(arg_count), argv(arg_value) {}

    bool pargs::parse() {
        if (argc < 2) {
            return false;
        }

        for (int i = 0; i < argc; i++) {
            if (is_argument(argv[i])) {
                pair_t arg = get_argument(argv[i]);
                arguments[arg.key] = arg.val;
            }
        }

        return verify_expected_arguments(&arguments, &expected_arguments, &expected_functor_map);
    }

    void pargs::expect(std::string argument) {
        expected_arguments.push_back(argument);
    }

    void pargs::expect(std::string argument, functor fn) {
        expected_arguments.push_back(argument);
        expected_functor_map[argument] = fn;
    }

    std::string pargs::get_arg(std::string argument) {
        if (arguments.find(argument) != arguments.end()) {
            return arguments[argument];
        } else {
            return "";
        }
    }

    std::string pargs::get_arg_or_default(std::string argument, std::string default_value) {
        string value = pargs::get_arg(argument);
        return value.empty() ? default_value : value;
    }

    void pargs::set_error_message(std::string error_message) {
        err_msg = error_message;
    }

    std::string pargs::error_message() {
        return err_msg;
    }

    bool pargs::help_asked() {
        return arguments.find("help") != arguments.end();
    }

    void pargs::print_all_args() {
        for (auto it = arguments.begin(); it != arguments.end(); ++it) {
            cout << it->first << ": " << it->second << endl;
        }
    }

    bool verify_expected_arguments(std::map<std::string, std::string>* arguments,
            std::vector<std::string>* expected_arguments,
            std::map<std::string, functor>* expected_functor_map) {
        for (auto const& expected_arg : *expected_arguments) {
            if (arguments->find(expected_arg) == arguments->end()) {
                return false;
            }

            if (expected_functor_map->find(expected_arg) != expected_functor_map->end()) {
                functor fn = expected_functor_map->at(expected_arg);
                bool is_valid = fn(arguments->at(expected_arg));
                if (!is_valid) {
                    return false;
                }
            }
        }

        return true;
    }

    bool is_argument(char *long_arg) {
        string str(long_arg);
        return str.find("--") == 0;
    }

    pair_t get_argument(char *long_arg) {
        string arg(long_arg);
        unsigned long pos_eq = arg.find('=');
        if (pos_eq != string::npos) {
            return {arg.substr(2, pos_eq - 2), arg.substr(pos_eq + 1, arg.length())};
        } else {
            return {arg.substr(2, arg.length()), ""};
        }
    }
}