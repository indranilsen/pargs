#ifndef PARGS_PARGS_H
#define PARGS_PARGS_H

#include <string>
#include <map>
#include <vector>

namespace pargs_n {
    class pargs {
    private:
        int argc;
        char **argv;
        std::string err_msg;
        std::vector<std::string> expected_arguments;
        std::map<std::string, std::string> arguments;
    public:
        pargs(int arg_count, char **arg_value);

        bool parse();
        void expect(std::string argument);
        std::string get_arg(std::string argument);
        std::string get_arg_or_default(std::string argument, std::string default_value);
        void set_error_message(std::string error_message);
        std::string error_message();
        bool help_asked();
        void print_all_args();
    };
}

#endif //PARGS_PARGS_H