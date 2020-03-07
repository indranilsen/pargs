#if [[ -f libpargs.a ]]; then
#    rm libpargs.a
#fi
#
#if [[ -f pargs.h ]]; then
#    rm pargs.h
#fi
#
#if [[ -f test ]]; then
#    rm test
#fi
#
#cp ../build/libpargs.a .
#cp ../pargs.h .
#
#g++ -std=c++11 test.cpp -L$(pwd) -lpargs -o test

./PargsTest --test --testString=hello --testInteger=100 --testFunctor=true
./PargsTest --someVal=override_default_val --testInteger=100 --testString=hello --test --testFunctor=true
./PargsTest --test --testString=hello --testInteger=100 --testFunctor=false
./PargsTest --testString=hello --testInteger=100 --testFunctor=true
./PargsTest --test --testInteger=100 --testFunctor=true
./PargsTest --test --testString=hello --testInteger=100
