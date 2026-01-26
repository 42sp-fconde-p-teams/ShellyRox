CC          = cc
CFLAGS      = -g3 -Wextra -Werror -Wall -I.
LIBFT_DIR   = ./lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a
C_FILES     = src/ft_sample.c \
				src/ft_sample_fail.c \
				src/ft_sample_success.c
				
LIBS        = $(LIBFT) -ldl -lglfw -pthread -lm
HEADERS     = -I . -I $(LIBFT_DIR) -I$(TEST_DIR)
TARGETS     = minishell

# Tests section
TEST_DIR    = tests
TEST_SRCS   = $(TEST_DIR)/test-ft_sample.c \
                $(TEST_DIR)/test-ft_sample_fail.c \
                $(TEST_DIR)/test-ft_sample_success.c
TEST_BINS   = $(TEST_SRCS:.c=.out)
REPORT_LOG  = test_report.log

# Alvo principal de teste
test: 
	@rm -f $(REPORT_LOG)
	@echo "🧪 RELATÓRIO DE TESTES UNITÁRIOS - $(shell date)" > $(REPORT_LOG)
	@echo "------------------------------------------" >> $(REPORT_LOG)
	@# Executa os testes ignorando falhas individuais para continuar a suite (-)
	-@$(MAKE) run_test_bins --no-print-directory
	@# Processamento do Resumo Final
	@TOTAL=$$(grep -c "Case:" $(REPORT_LOG) || echo 0); \
	PASSED=$$(grep -c "\[PASS\]" $(REPORT_LOG) || echo 0); \
	FAILED=$$(grep -c "\[FAIL\]" $(REPORT_LOG) || echo 0); \
	echo "" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	echo "📊 RESUMO FINAL:" >> $(REPORT_LOG); \
	echo "  Total de casos: $$TOTAL" >> $(REPORT_LOG); \
	echo "  ✅ Sucessos:     $$PASSED" >> $(REPORT_LOG); \
	echo "  ❌ Falhas:       $$FAILED" >> $(REPORT_LOG); \
	echo "==========================================" >> $(REPORT_LOG); \
	cat $(REPORT_LOG); \
	if [ $$FAILED -gt 0 ]; then exit 1; fi

run_test_bins: $(TEST_BINS)

# Regra de compilação e execução por arquivo
$(TEST_DIR)/%.out: $(TEST_DIR)/%.c $(LIBFT)
	@echo "\n📄 Arquivo: $<" >> $(REPORT_LOG)
	@$(CC) $(CFLAGS) $(C_FILES) $< $(HEADERS) $(LIBS) -o $@ 2>> $(REPORT_LOG) || \
		(echo "  ❌ Erro de compilação no arquivo de teste!" >> $(REPORT_LOG) && exit 0)
	@# Executa o binário e anexa a saída (pass/fail das funções) ao log
	@./$@ >> $(REPORT_LOG) 2>&1 || true
	@rm -f $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.PHONY: all clean fclean re test run_test_bins