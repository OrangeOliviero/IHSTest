.DEFAULT_GOAL:=test

TEST_BINARY:=../../bin/PalindromeFinder

# User-supplied
STRING:=

TEST_COMMAND=$(TEST_BINARY) $(STRING)

TEST_OUTPUT:=TestOutput
EXPECTED_OUTPUT:=ExpectedOutput

.PHONY: test run-test validate-test

run-test-command:
	@$(TEST_COMMAND) > $(TEST_OUTPUT) 2>&1

compare-test-output:
	@diff -u $(EXPECTED_OUTPUT) $(TEST_OUTPUT)
	@rm -f $(TEST_OUTPUT)

test: run-test-command compare-test-output
	@echo "Test succeeded!"
