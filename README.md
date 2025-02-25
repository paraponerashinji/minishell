# minishell

DID LIST:

I connected the parsing with the pipes, you can now exec files\
Env var are now implemented\
implemented input and output redirection\
TODO LIST:

Valgrind correction:\
memleak in the parsing, valgrind error when execve (??)\
Parsing : double characters specifiers, and cleaning\
I enventually will have to rewrite all the parsing because its too ugly\
Integrate special pipes, clean the pipes code\
Implement Echo, cd, export, unset, end\
Implement env variables\

Bonus:\
Implement &&, || and *
