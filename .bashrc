# path
export PATH=$PATH:/home/vincentz/p4/sw/main/apps/p4review

# android
export ANDROID_SDK_ROOT=~/Downloads/adt-bundle-linux-x86_64-20130729/sdk
export NDKROOT=~/Downloads/android-ndk-r8e
export ANDROID_NDK=~/Downloads/android-ndk-r8e
alias log='adb logcat'
alias grepadb='adb logcat | grep'

# bin alias
alias source='source ~/.bashrc'
alias greprn='grep -rn'
alias ls='ls --color'
alias ll='ls -l --color'
alias la='ls -la --color'

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
