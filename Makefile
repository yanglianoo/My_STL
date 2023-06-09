.PHONY: mian
main.out:*.cpp
	g++ $^ -o $@

.PHONY: clean
clear:
	rm -rf *.out