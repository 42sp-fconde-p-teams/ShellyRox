CC          = cc
CFLAGS      = -g3 -Wextra -Werror -Wall
LIBFT_DIR   = ../lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

# IMPORTANTE: Garanta que nenhum desses arquivos tenha uma função main()
C_FILES     = ../src/ft_sample.c \
              ../src/ft_sample_fail.c \
              ../src/ft_sample_success.c

LIBS        = $(LIBFT) # -ldl -lglfw -pthread -lm
HEADERS     = -I. -I$(LIBFT_DIR) -I$(TEST_DIR)

# Tests section
TEST_DIR    = ./
TEST_SRCS   = $(TEST_DIR)/test-ft_sample.c \
                $(TEST_DIR)/test-ft_sample_fail.c \
                $(TEST_DIR)/test-ft_sample_success.c
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
	@TOTAL=$$(grep -c "Case:" $(REPORT_LOG) || echo 0); \
	PASSED=$$(grep -c "\[PASS\]" $(REPORT_LOG) || echo 0); \
	FAILED=$$(grep -c "\[FAIL\]" $(REPORT_LOG) || echo 0); \
	echo "" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	echo "📊 Summary:" >> $(REPORT_LOG); \
	echo "  Total cases: $$TOTAL" >> $(REPORT_LOG); \
	echo "  ✅ Pass:      $$PASSED" >> $(REPORT_LOG); \
	echo "  ❌ Fail:      $$FAILED" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	cat $(REPORT_LOG); \
	if [ $$FAILED -gt 0 ]; then exit 1; fi

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

fclean: clean
	@rm -rf minishell $(REPORT_LOG)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

.PHONY: test run_test_bins clean fclean