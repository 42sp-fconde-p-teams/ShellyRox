CC          = cc
CFLAGS      = -g3 -Wextra -Werror -Wall
LIBFT_DIR   = ../lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

# IMPORTANTE: Garanta que nenhum desses arquivos tenha uma função main()
C_FILES     = ../src/parsing/parser.c \
              ../src/parsing/expander/expander.c \
              ../src/parsing/expander/remove_quotes.c \
              ../src/parsing/expander/variable_expansion.c \
              ../src/parsing/expander/tilde_expansion.c \
              ../src/parsing/expander/token_insertion.c \
              ../src/parsing/fsm/set_tokens.c \
              ../src/parsing/fsm/get_token_len.c \
              ../src/execution/redirections.c \
              ../src/execution/executor.c \
              ../src/execution/pipes.c	\
              ../src/execution/heredoc.c \
              ../src/utils/get_env_value.c \
              ../src/utils/cleanup.c \
              ../src/utils/env_set.c \
              ../src/utils/env_init.c \
              ../src/utils/env_array.c \
              ../src/parsing/fsm/clear_token_list.c \
              ../src/builtins/env.c \
              ../src/builtins/pwd.c \
              ../src/builtins/cd.c \
							../src/builtins/exit.c \
							../src/builtins/export.c

LIBS        = $(LIBFT) # -ldl -lglfw -pthread -lm
HEADERS     = -I. -I$(LIBFT_DIR) -I$(TEST_DIR) -I..

# Tests section
TEST_DIR    = ./
TEST_SRCS   = $(TEST_DIR)/test-parser.c \
				$(TEST_DIR)/test-set_tokens.c \
				$(TEST_DIR)/test-get_token_len.c \
				$(TEST_DIR)/test-executor.c \
				$(TEST_DIR)/test-expander.c \
				$(TEST_DIR)/test-heredoc.c \
				$(TEST_DIR)/test-pipe.c \
				$(TEST_DIR)/test-clear_token_list.c \
				$(TEST_DIR)/test-env.c \
				$(TEST_DIR)/test-pwd.c \
				$(TEST_DIR)/test-exit.c \
				$(TEST_DIR)/test-cd.c \
				$(TEST_DIR)/test-env_manager.c
TEST_BINS   = $(TEST_SRCS:.c=.out)
REPORT_LOG  = test_report.log

# Alvo principal de teste
test: $(LIBFT)
	@rm -f $(REPORT_LOG)
	@echo "TEST REPORT - $(shell date)" > $(REPORT_LOG)
	@echo "------------------------------------------" >> $(REPORT_LOG)
	@# Run binaries ignoring errors for the jog to keep running
	-@$(MAKE) run_test_bins --no-print-directory
	@# Final summary processing
	@TOTAL=$$(grep -c "Case:" $(REPORT_LOG)); \
	PASSED=$=$$(grep -c "\[PASS\]" $(REPORT_LOG)); \
	FAILS=$$(grep -c "\[FAIL\]" $(REPORT_LOG)); \
	ERRORS=$$(grep -c "\[ERROR\]" $(REPORT_LOG)); \
	echo "" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	echo "📊 Summary:" >> $(REPORT_LOG); \
	echo "  Total cases:  $$TOTAL" >> $(REPORT_LOG); \
	echo "  ✅ Pass:      $$PASSED" >> $(REPORT_LOG); \
	echo "  ❌ Fail:      $$FAILS" >> $(REPORT_LOG); \
	echo "  ⚠️  Errors:    $$ERRORS" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	cat $(REPORT_LOG); \
	if grep -qE "\[FAIL\]|\[ERROR\]" $(REPORT_LOG); then \
		echo "\033[0;31m\n[!] Test suite failed.\033[0m"; \
		exit 1; \
	else \
		echo "\033[0;32m\n[+] Test suite passed successfully.\033[0m"; \
		exit 0; \
	fi

single: $(LIBFT)
	@echo "Compiling individual test file for: $(T)"
	$(CC) $(CFLAGS) $(C_FILES) test-$(T).c $(HEADERS) $(LIBS) -o unit_test.out

run_test_bins: $(TEST_BINS)

# Regra de compilação e execução por arquivo
$(TEST_DIR)/%.out: $(TEST_DIR)/%.c
	@# Tries to compile. If fail, log it to log file.
	@$(CC) $(CFLAGS) $(C_FILES) $< $(HEADERS) $(LIBS) -o $@ >> $(REPORT_LOG) 2>&1 || \
		(echo "\nFile: $<" >> $(REPORT_LOG) && \
		 echo "      [ERROR] Compilation failed" >> $(REPORT_LOG) && exit 0)
	@# If binary was created, runs it and cleans it
	@if [ -f $@ ]; then \
		echo "\nFile: $<" >> $(REPORT_LOG); \
		./$@ >> $(REPORT_LOG) 2>&1 || true; \
		rm -f $@; \
	fi

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	rm -f *.out

fclean: clean
	@rm -rf minishell $(REPORT_LOG)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

.PHONY: test run_test_bins clean fclean
