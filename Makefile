.PHONY: mian
main.out:*.cpp
	g++ $^ -o $@

.PHONY: clear
clear:
	rm -rf *.out