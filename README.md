# 42_Minishell

On this Project, we had to create a simple shell. The shell should be able to prompt a user, then read a command from the user and execute it. The shell should also be able to execute built-in commands and environmental variables.

## Clonning repository

```bash
git clone https://github.com/mionzeras/42_Minishell.git
cd 42_Minishell
```

## How to run

```bash
make
./minishell
```

## Try some commands

```bash
"echo Hello World"
"cd .."
"pwd"
"< /etc/passwd grep root | cut -d: -f1"
"< infile.txt grep -v a | sort | cat -e > outfile.txt"
"export VAR=42"
"echo $VAR"
"unset VAR"
"env"
"exit"
```


## How to clean

```bash
make clean
```

## How to fclean

```bash
