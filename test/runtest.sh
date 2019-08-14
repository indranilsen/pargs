if [[ -f libpargs.a ]]; then
    rm libpargs.a
fi

if [[ -f pargs.h ]]; then
    rm pargs.h
fi

if [[ -f test ]]; then
    rm test
fi

cp ../build/libpargs.a .
cp ../pargs.h .

g++ -std=c++11 test.cpp -L$(pwd) -lpargs -o test

#./test --test --testString=hello --testInteger=100 --testFunctor=true
#./test --someVal=override_default_val --testInteger=100 --testString=hello --test --testFunctor=true
#./test --test --testString=hello --testInteger=100 --testFunctor=false
#./test --testString=hello --testInteger=100 --testFunctor=true
#./test --test --testInteger=100 --testFunctor=true
#./test --test --testString=hello --testInteger=100
