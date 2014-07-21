Build with ndk-build
---------------------
Use ndkbuild.sh to build the library. It's just a wrapper to ndk-build. You must have ndk-build in your PATH.

```bash
$ ./ndkbuild.sh all # build
$ ./ndkbuild.sh clean # clean
```

The library build with above commands will be generated in obj/local/armeabi/. 


Build with traditional Makefile
---------------------------------
Alternatively, you can use tradittional makefile style build procedure.

You first need to generate android ndk toolchain by the following command(you can choose gcc or clang).

```bash
$ ${NDKHOME}/build/tools/make-standalone-toolchain.sh --platform=android-9 --toolchain=arm-linux-androideabi-4.6 --install-dir=$HOME/android-toolchain-arm-4.6
```

Then adjust parameters in android.env and Makefile.android.

Finally type the following command to build

```bash
$ make -f Makefile.android all # build
$ make -f Makefile.android clean # clean
```

The library build with above commands will be generated in ./ .


Use the library in Android project
----------------------------------
You need to copy the library file (libtest.a) to jni/lib/ directory of your android project. Then please refere to the Android.mk of the jni project to see how to include prebuilt libraries.
