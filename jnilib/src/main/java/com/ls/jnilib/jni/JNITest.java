package com.ls.jnilib.jni;

public class JNITest {


    //javah -d cpp com.ls.jnilib.jni.JNITest  尽量将静态方法放在同一个类中
    static {
        System.loadLibrary("jnidemo");
    }

    public native static String getString();

    public static native void setNumber(int mumber);

    public static native int getNumber();

    public static native String changeStringToChar(String input);

    public static native String readSnNum();

    public static native String stringCopy(String source);

    public native static int addIntByteArray(int[] byteArray);
}
