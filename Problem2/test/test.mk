.DEFAULT_GOAL:= test

TEST_BINARY:=../../bin/ArrayTransformExample

SUM:= -o sum
PROD:= -o prod
DELTA:= -o delta

TEST_OUTPUT:=TestOutput
EXPECTED_OUTPUT:=ExpectedOutput

#Caller sets these
OPERATION:=
VALUES:=

TEST_COMMAND=$(TEST_BINARY) $(OPERATION) $(VALUES)

run-test-command:
	@$(TEST_COMMAND) > $(TEST_OUTPUT) 2>&1

compare-test-output:
	@diff -u $(EXPECTED_OUTPUT) $(TEST_OUTPUT)
	@rm -f $(TEST_OUTPUT)
	@echo "Test succeeded!"

test: run-test-command compare-test-output
