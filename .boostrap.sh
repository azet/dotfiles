#!/usr/bin/env bash

[ $(git) && $(zsh) && $(wget) ] || {
    echo "need git, zsh and wget!"
    exit 1
}

# install grml zsh config
wget -O .zshrc http://git.grml.org/f/grml-etc-core/etc/zsh/zshrc

# install grml screen config
wget -O .screenrc http://git.grml.org/f/grml-etc-core/etc/grml/screenrc_generic

# install janus vim  distribution
curl -Lo- https://bit.ly/janus-bootstrap | bash

# clone superior email client config
echo -e "\n\n\nrun \"sudo apt-get install urlview muttprint muttprint-manual mutt-patched w3m mutt\"\n\n\n"
git clone git@github.com:azet/muttrc.git .muttrc

echo "done."
