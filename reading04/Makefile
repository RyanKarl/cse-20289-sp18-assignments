test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-exists test-head

test-scripts:
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading04/test_exists.sh
	curl -sLO https://gitlab.com/nd-cse-20289-sp18/cse-20289-sp18-assignments/raw/master/reading04/test_head.sh
	chmod +x test_*.sh

test-exists:
	./test_exists.sh

test-head:
	./test_head.sh
