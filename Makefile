.PHONY: mian
main.out:*.cpp
	g++ $^ -o $@ -std=c++11

.PHONY: clean
clean:
	rm -rf *.out
	rm -rf .vscode