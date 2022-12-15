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

`
function brew_install()

{
	
	cd /goinfre
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
	
	cd homebrew/bin && ./brew install readline
}

`

2. Close your current terminal, re-open and write brew_install in your terminal. Wait for it to end!
3. Finally you can go where u cloned this project and you can execute like this `./minishell`
