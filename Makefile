.PHONY: mian
main.out:*.cpp
	g++ $^ -o $@

.PHONY: clean
clean:
	rm -rf *.out
	rm -rf .vscode