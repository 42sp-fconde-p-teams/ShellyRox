CC          = cc
CFLAGS      = -g3 -Wextra -Werror -Wall -I.
LIBFT_DIR   = ./lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

C_FILES     = src/ft_sample.c \
                src/ft_sample_fail.c \
                src/ft_sample_success.c

LIBS        = $(LIBFT) -ldl -lglfw -pthread -lm

HEADERS     = -I . -I $(LIBFT_DIR)

TARGETS     = minishell

# tests section
TEST_DIR    = tests
TEST_SRCS   = $(TEST_DIR)/test-ft_sample.c \
                $(TEST_DIR)/test-ft_sample_fail.c \
                $(TEST_DIR)/test-ft_sample_success.c

TEST_BINS   = $(TEST_SRCS:.c=.out)
# Arquivo temporário para rastrear falhas
ERROR_LOG   = .test_failures

# Alvo principal de teste
test: 
	@rm -f $(ERROR_LOG)
	@$(MAKE) run_test_bins --no-print-directory
	@if [ -f $(ERROR_LOG) ]; then \
		echo "\n\033[0;31m[!] ALGUNS TESTES FALHARAM:\033[0m"; \
		cat $(ERROR_LOG); \
		exit 1; \
	else \
		echo "\n\033[0;32m[+] Todos os testes concluídos com sucesso.\033[0m"; \
	fi

# Alvo intermediário para disparar a regra de pattern
run_test_bins: $(TEST_BINS)

# Regra para compilar e rodar cada teste individualmente
$(TEST_DIR)/%.out: $(TEST_DIR)/%.c $(LIBFT)
	@echo "Compilando: $<"
	@$(CC) $(CFLAGS) $(C_FILES) $< $(HEADERS) $(LIBS) -o $@
	
	@# Executa capturando a saída. Se falhar, anexa o output ao log de erros.
	@./$@ > temp_output.log 2>&1 || \
	(echo "  -> Arquivo: $@" >> $(ERROR_LOG) && \
	 cat temp_output.log >> $(ERROR_LOG) && \
	 echo "--------------------------------" >> $(ERROR_LOG) && \
	 false)
	 
	@# Se chegou aqui, passou. Limpa os temporários.
	@rm -f $@ temp_output.log

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(TARGETS)

$(TARGETS): $(C_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(C_FILES) $(HEADERS) $(LIBS) -o $@
	@echo "==> Shelly was successfully compiled!"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "==> Simple clean done!"

fclean: clean
	@rm -rf $(TARGETS) $(ERROR_LOG)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "==> Full clean done!"

re: fclean all

.PHONY: all clean fclean re test run_test_bins