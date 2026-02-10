
unit-tests:
	@$(MAKE) -C ./tests

clean:
	@$(MAKE) clean -C ./tests

fclean: clean
	@rm -rf ./test/test_report.log
	@$(MAKE) fclean -C ./tests