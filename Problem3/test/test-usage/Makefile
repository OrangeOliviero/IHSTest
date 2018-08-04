include ../test.mk

.DEFAULT_GOAL:= test-override

# We simply want to confirm that no string prints the usage, but don't
#  want to be so brittle that we break any time the usage output changes
# The grep command will fail if it fails to find the string, which will
#  cause the test to fail
TEST_COMMAND:=$(TEST_COMMAND) | grep Usage > /dev/null

test-override:
	@$(TEST_COMMAND) || (echo "Test failed - Usage not found"; exit 2)
	@echo "Test succeeded!"
