#!/usr/bin/env bash

declare __WHI=$(tput setaf 7)
declare __BLU=$(tput setaf 4)
declare __RED=$(tput setaf 1)
declare __BOL=$(tput bold)
declare RST=$(tput sgr0)
declare CLI="$__WHI"
declare ERR="$__BLU $__BOL"
declare EXI="$__RED $__BOL"

#function bar_setup() {
  # curl -sL ${__bar_bz2_url} --output /tmp/bar-1.4.bz2.gz
  # curl -sL ${__bar_md5_url} --output /tmp/bar-1.4.md5
  # [[ $(md5 -s - /tmp/bar-1.4.bz2.gz </tmp/bar-1.4.md5) ]] && {
  #    (cd /tmp && tar xfz /tmp/bar.bz2.gz && cd - )>/dev/null
  #  /tmp/bar-1.4/bar -D > lib/bar.inc
  # } || ( printf "${ERR}! cant process/unpack bar script !! BUT CONTINUING !!\n${RST}" )
#}

function is_excluded?() {
  for file in ${__excl_files}; do
    [[ ${file} == *${files}* ]] && return 1
  done
  return 0
}

function is_os?() {
  case $(uname) in
  *Linux*)  printf "linux"   ;;
  *Darwin*) printf "macosx"  ;;
  *SunOS*)  printf "solaris" ;;
  *BSD*)    printf "bsd"     ;;
  esac
  return
}

function is_distro?() {
  case $(< "/etc/*release*") in
  *Debian* | *Ubuntu*)
    printf "debian"
  ;;
  *"Red Hat"* | *CentOS*)
    printf "rh"
  ;;
  esac
  return
}

function install_pkgs() {
  case $(uname) in
  *Linux*)
    $(which apt-get &>/dev/null) || {
      echo "not debian based, do this manually."
      exit 1
    }
    sudo apt-get install -y ${d_pkg_debian}
  ;;
  *Darwin*)
    brew install ${__pkg_macosx_homebrew} || exit 1
    brew upgrade --require-sha
    brew update 
    brew cleanup -s
    brew doctor
  ;;
  esac
}

