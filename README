===========================================================================

Dronity 0.7 experimental build (community edition)
it's a trinty port to Android, wow!

Android Kernel Fuzzer based and forked from
Trinity 1.4
https://github.com/kernelslacker/trinity
(please read README.trinity)
All the credit for the awesome trinity goes to Dave Jones davej@redhat.com

ported by Vito Rallo (vito.rallo@gmail.com)

===========================================================================

Crosscompile Dronity for platform >21 (Android 5.0) and/or AARCH64

1) get Android NDK from Google
2) run make-standalone-toolchain to get a standalone compiler

./make-standalone-toolchain.sh --toolchain=aarch64-linux-android-4.9 --platform=android-21 --install-dir=/opt/toolchain --ndk-dir=/opt/android-ndk-r10c --system=linux-x86_64

3) important: set your toolchain bin in env PATH, add it to .bashrc

echo "PATH=$PATH:/opt/toolchain/bin" >> ~/.bashrc
source ~/.bashrc

4) edit config.h and uncomment or be sure that 
#define P21 1 
and 
#define AARCH64 1 (in case you are compiling with armv8 toolchain)

4) compile dronity, you are now ready to go!

 make CROSS_COMPILE=aarch64-linux-android- CC=aarch64-linux-android-gcc 

(specify here the type of compiler you want, this example is based on aarch64 compiler for android version 4.9 ndk version 10c from Google)

============================================================================

Crosscompile Dronity for platform 19 (Android 4.4) and hopefully below (not tested)

1) get Android NDK from Google
2) run make-standalone-toolchain to get a standalone compiler (android_sdk_root/build/tools)

./make-standalone-toolchain.sh --toolchain=arm-linux-androideabi-4.9 --platform=android-19 --install-dir=/opt/toolchain --ndk-dir=/opt/android-ndk-r10c --system=linux-x86_64

3) important: set your toolchain bin in env PATH, add it to .bashrc

echo "PATH=$PATH:/opt/toolchain/bin" >> ~/.bashrc
source ~/.bashrc

4) edit config.h and COMMENT or be sure that 
// #define P21 1 
and 
// #define AARCH64 1
ARE COMMENTED!!!!


4) compile dronity, you are now ready to go!

 make CROSS_COMPILE=aarch64-linux-android- CC=aarch64-linux-android-gcc 

(specify here the type of compiler you want, this example is based on aarch64 compiler for android version 4.9 ndk version 10c from Google)

=============================================================================

supported standalone toolchains as of android-ndk-r10e:

aarch64-linux-android-4.9 aarch64-linux-android-clang3.5 aarch64-linux-android-clang3.6 arm-linux-androideabi-4.8 arm-linux-androideabi-4.9 arm-linux-androideabi-clang3.5 arm-linux-androideabi-clang3.6 llvm-3.5 llvm-3.6 mips64el-linux-android-4.9 mips64el-linux-android-clang3.5 mips64el-linux-android-clang3.6 mipsel-linux-android-4.8 mipsel-linux-android-4.9 mipsel-linux-android-clang3.5 mipsel-linux-android-clang3.6 renderscript x86-4.8 x86-4.9 x86-clang3.5 x86-clang3.6 x86_64-4.9 x86_64-clang3.5 x86_64-clang3.6

=============================================================================

Troubleshooting:

1) cannot run on 4.4 even if the file is compiled for 32bit dynamically linked?
try to comment this line from the Makefile

LDFLAGS += -fPIE -pie

this is required as of Android 5.0 only!

2) I see a warning while compiling getline.c ...
that's fine... close your eyes for now!
