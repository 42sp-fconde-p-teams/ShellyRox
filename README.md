_This project has been created as part of the 42 curriculum by fconde-p._

# Description

This project intends to ~~drives us crazy~~ make us learn the main concepts of a shell interpreter like Bash.

A shell interpreter must read a prompt and deal with the content to give a satisfatory response deppending on the input. For this we have the following process:

```
|INPUT| --> |TOKENIZER| --> |PARSER| --> |EXECUTOR| --> |OUTPUT|
```

After this process, it should wait for a new prompt.

## Tokenizer

Here the system splits the input in a list of tokens (not propperly words) that are classified in types that can be WORD, PIPE, REDIR_OUT, REDIR_IN, HEREDOC or APPEND. Those are operation signals except for WORD. This is a special token that later will be processed at the parser.

## Parser

The parser will parse (duh =P) the content of the token list to an abstract syntax three (AST). Here we will expand the content indicated by '$',

## Executor

This will run the comands following the AST. If there is some OS function, it will access from the system. And if there are some built in functions it will be run from the project itself.

# Instructions

To compile, use the `make` comand.\
To clean the objects created, do a `make clean`.\
To clean the objects created and the executable, do a `make fclean`.\
To run the binary, after compile the project, run `./minishell`. It will bring Shelly to life.

If you want to go further, you can check our unit tests made for this project. It was a blessing for us protecting us from ourselves and from each other.

## AI

We wanted to use a mature aproach in AI on this project. Our main concern was learn how to use AI efficiently but without falling into the pit of cognitive debt. So, by the beggining of the project, Carlos made a Gemini Gem called _Shelly_ that would helps us. It was feeded with the context of our project and, to spice a little bit, it was designed with a sarcastic and acid personality. It was really funny to read their responses pointing out our mistakes and concept misunderstandings.

As we studied more about AI and accordingly to the needs we had at our jobs, it showed up to as as an opportunity to test ways to write code in a way that everything fit right in place without breaking our system and without taking to much time from us writting long prompts or having to ask several times the same thing. For this, we followed the suggestions given by Fabio Akita at his blog aftes a deep dive that he took in software develompent with AI (the article is listed in Resources section below). He tells us to be the software engineer leading a crew of developers (the AI itself). So we need to design a clear and cohesive path to develop the system and pass to the AI small chunks of activities and describe in a fine way the requisites. Also, ask it to create unit tests that we -- and the AI -- could run to check if something was broken as the project goes on.

So we used

- Gemini Gem (Shelly): to conduct the concepts understanding and _tough love_;
- Gemini CLI (Filipe): mostly with the model gemma 4 (31B), opensource and unlimited for use;
- Claude Code (Carlos): 

Besides the AI usage, we kept track of all the development and architectural decisions (for the best and for the worst).

# Resources

