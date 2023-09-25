.PHONY: all build clean

FLAGS=-g++ -Wall -Wextra -Werror -pedantic -std=c++17
TEST_FLAGS=-lgtest -pthread
SOURCE = model/s21_parser.cc model/s21_validator.cc
OS_DEPENDENT_FLAGS = -lgtest -lpthread -fprofile-arcs -ftest-coverage
TEST_FILES = tests/test.cc

all: install

install: uninstall
	mkdir -p build
	cd build && cmake ..
	make -C build

uninstall:
	rm -rf SmartCalc_v2.tar
	rm -rf build
	rm -rf SmartCalc_v2.app

dvi:
	doxygen Doxyfile
	cd docs/html && open index.html
		
dist:
	tar -C ./build -cf SmartCalc_v2.tar SmartCalc_v2.app

test_m1:
	cd build && ./SmartCalc_v2_test
	cd build && make coverage && cd out && open index.html
	
test:
	$(FLAGS) $(SOURCE) tests/test.cc $(TEST_FLAGS) -o test
	./test

gcov_report:
	$(FLAGS) --coverage $(SOURCE) $(TEST_FILES) -o test -g $(OS_DEPENDENT_FLAGS)
	./test
	lcov -t "test" -c -d ./ --no-external -o test.info
	genhtml -o report test.info

clean:
	rm -rf *.gcno *.gcda
	rm -rf test_output
	rm -rf build
	rm -rf test test.info
	rm -Rf html/ latex/
	rm -rf SmartCalc_v2.app
	rm -rf *.tar
	rm -rf docs
	rm -rf report
	rm -rf test.dSYM 
