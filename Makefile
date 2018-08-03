.DEFAULT_GOAL:= all

PROBLEMS:=$(sort $(wildcard Problem*))

define create-problem-targets
all: $(1)-all
test: $(1)-test
clean: $(1)-clean

$(1)-all:
	@echo "Building $(1)"
	@echo "-------------------------------------------"
	@$(MAKE) --no-print-directory -C $(1) all
	@echo "-------------------------------------------"

$(1)-test:
	@echo "Testing $(1)"
	@echo "-------------------------------------------"
	@$(MAKE) --no-print-directory -C $(1) test
	@echo "-------------------------------------------"

$(1)-clean:
	@echo "Cleaining $(1)"
	@echo "-------------------------------------------"
	@$(MAKE) --no-print-directory -C $(1) clean
	@echo "-------------------------------------------"
endef

$(foreach problem,$(PROBLEMS),$(eval $(call create-problem-targets,$(problem))))
