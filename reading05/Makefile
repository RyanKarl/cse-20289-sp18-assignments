test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-sort test-cut test-uniq

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading05/test_sort.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading05/test_cut.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading05/test_uniq.sh
	chmod +x test_*.sh

test-sort:
	./test_sort.sh

test-cut:
	./test_cut.sh

test-uniq:
	./test_uniq.sh
