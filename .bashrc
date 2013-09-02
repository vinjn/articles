# ~/.profile: executed by the command interpreter for login shells.
# This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
# exists.
# see /usr/share/doc/bash/examples/startup-files for examples.
# the files are located in the bash-doc package.

# the default umask is set in /etc/profile; for setting the umask
# for ssh logins, install and configure the libpam-umask package.
#umask 022

# if running bash
# if [ -n "$BASH_VERSION" ]; then
#     # include .bashrc if it exists
#     if [ -f "$HOME/.bashrc" ]; then
# 	. "$HOME/.bashrc"
#     fi
# fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

# android
export ANDROID_SDK_ROOT=~/Downloads/adt-bundle-linux-x86_64-20130729/sdk
export NDKROOT=~/Downloads/android-ndk-r8e
export ANDROID_NDK=~/Downloads/android-ndk-r8e

# bin alias
alias log='adb logcat'
alias grepadb='adb logcat | grep'
alias source='source ~/.bashrc'
alias greprn='grep -rn'

# p4
export P4CONFIG=.p4config
alias p4m='p4merge'
alias p4review='/home/vincentz/p4/sw/main/apps/p4review/p4review.pl'
alias p4rmerge='/home/vincentz/p4/sw/main/apps/p4review/p4rmerge.pl'

# cd alias
alias ..='cd ..'
alias ...='cd ../../../'
alias ....='cd ../../../../'
alias .....='cd ../../../../'
alias .4='cd ../../../../'
alias .5='cd ../../../../..'
