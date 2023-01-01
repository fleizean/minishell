# Minishell - @42Kocaeli

<b> beauty minishell made by eyagiz and fyurtsev </b>

https://user-images.githubusercontent.com/66090171/207823446-38c2ed2c-d099-4bc4-a5c5-cd676af1a08c.mov

## About

This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors. Enjoy it!


## Installation & Usage

### Requirements
The only requirements are:

- GNU make
- Readline library
- GCC

### Building the program

1. Open terminal and go HOME with `cd ~`, write this `vim .zshrc` and add this code:

```
function brew_install()
{
	cd /goinfre
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
	cd homebrew/bin && ./brew install readline
}
```


2. Close your current terminal, re-open and write brew_install in your terminal. Wait for it to end!
3. Finally you can go where u cloned this project and you can execute like this `./minishell`
4. Don't forget if you switch to another computer on campus you must write again `brew_install` for installion.


### Mandatory

- Can only use C
- Must respect the school imposed coding style
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use Libft
- Handle program interruption (Ctrl + D)

### Some Issues and How Did ve Fixed it
If we have solved it, it will appear as drawn, if we have not solved it, only the problem will be written.

- Firstly if u write only "unset" terminal will suppress segmentation fault to screen. The solution is simple, I will do it when I am available. We need to check if in the unset part, just it!
- 


### My Partner

<b>[fyurtsev](https://github.com/fyurtsev)</b>
