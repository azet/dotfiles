# dotfiles
*bootstraps my personal environment and utilities in an OS agnostic manner.*

currently there is built in support for Linux (Debian) and Mac OS X.

this project also bootstraps necessary packages depending on OS, distro
and machine-type (take a look at `bootstrap.conf`). you might want to add
or remove some packages. Linux-specific performance analysis and debugging
tools may require a current 3.x-line Linux kernel. I currently run a
[customized 4.2.x
kernel](https://gist.github.com/azet/c3d83ac6307f0938686a) manually [patching bluetooth](https://gist.github.com/azet/44df72dfdaa67484c4d9) to use a Apple Magic Trackpad.

## Bootstrapping and configuration
1. clone in `$HOME`.
2. `./bootstrap [--desktop] [--debug]`.
3. **optional**: configure `~/.mutt/accounts/*`, `~/.goobookrc`.

## TODO
* write coherent setup routine in `bootstrap`
* qtile for xfce4
* 'Enterprise Linux' (CentOS, RHEL, SL,..) packages
* FreeBSD specifics & ports
* Solaris specifics & packages

## OS/Distro Notes
### Linux (Debian)
* Window Manager: xfce4 customized

### Apple MacOS X
* Bootstraps via plists/settings and various in-line hacks for
  environment/userland setup
* Primarily uses `brew(1)` (Homebrew) for packages as well as
  git submodules in `foreign/` directory for supporting user-land apps.
* Multiple hacks for defaulting to prefered applications (i.e. for
  `open(1)`, browsers, editors etc.
* !!! Due to increased use of MacBooks for primary workstations/laptops
  many things in these dot-files have been neglected when it comes to
  some Linux specifics, others haven't. Fav'd cli tools have changed 
  over time. But OS X now provides a GNU Userland, which makes a lot of
  compatability issues easier. Beware though that some things may seem
  quite OS X-centric as a lot of development on Linux is now done via
  remote hosts, directly on VMs (VMWare Fusion as well as Parallels
  the latter for ease-of-use and integration lately, esp. when it comes
  to EE/electronics related testing/dev tools i.e. analog devices SW)


## fzf
Gets a special thank you here. I've been using it extensively and have
integrated it with tmux, as well as some OS-agnostic aliases.

## zsh
These dot-files bootstrap from bourne shell and bash, but are meant to
be used with `ZSH` (Z-Shell) as the primary user-land command line,
various integrations, aliases (see: fzf above) and hacks have been in
place from the very beginning to latest additions. Among them many
zshell plugins loaded via `~/.zshrc.local` - take a look to get a better
understanding of what's going on or what you may want to use/rather do
not want in your environment.

1. `prompt ...` changes the layout of the "PS" setting (incl. UTF-8
  colors, terminal depending, xterm256 where possible to have some
  semblence of portability as well as uniformity.
2. `toggle-fzf-tab` enables fzf functions you may want to try out.
3. `fzind` is an alias for searching directories and files. Function 
    keys F1 and F2 are avaiable apart from using CTRL+D/F (dir/file)
    search. F1 opens a given selection with `vim(1)` while F2 copies
    the file-contents to the clipboard (pbcopy on OS X) for pasting.

- zsh is used by myself on all terminals (Linux, Windows/WSL, Unixes and of course MacOS X)


## License
Some configurations are cherry-picked from across the internet. Original
work is licensed as follows:

http://opensource.org/licenses/MIT

The MIT License (MIT)

Copyright (c) 2014 Aaron Zauner <azet@azet.org>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
