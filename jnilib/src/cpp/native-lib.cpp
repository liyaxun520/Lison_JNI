//
// Created by Administrator on 2019/8/15.
//
#include<stdio.h>
#include<jni.h>
#include "string"
#define LOG_TAG  "C_TAG"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

int Ret = 0;   //声明全局变量

extern "C" {
/*
 * Class:     com_ls_jnilib_jni_JNITest
 * Method:    getString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ls_jnilib_jni_JNITest_getString
  (JNIEnv *env,jclass jclass){

      return  env->NewStringUTF("lison is here");
  };
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ls_jnilib_jni_JNITest_setNumber(JNIEnv *env, jclass type, jint mumber) {
    //对全局变量赋值
    Ret = mumber;

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_ls_jnilib_jni_JNITest_getNumber(JNIEnv *env, jclass type) {

    return Ret;
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_ls_jnilib_jni_JNITest_changeStringToChar(JNIEnv *env, jclass type, jstring input_) {
    const char *input = env->GetStringUTFChars(input_, 0);


    env->ReleaseStringUTFChars(input_, input);

    return env->NewStringUTF(input);
}extern "C"


int FileGetLine( FILE* fp, char* buffer, int maxlen ){
    int i = 0;
    char ch1;
    if ( fp == NULL ){
        printf( "file descriptor NULL\n" );
        return -1;
    }

    while( i < maxlen )
    {
        ch1 = fgetc( fp );

        if ( ch1 == '\n' || ch1 == 0x00 || feof(fp)!=0 ) break;

        if ( ch1 == '\r' ) continue;

        if ( ch1 == 0x0C || ch1 == 0x1A )/* 换页符('\f')和替换符也算有效字符 */
        {
            buffer[i++] = ch1;
            break;
        }
        buffer[i++] = ch1;
    }
    buffer[i] = '\0';
    if( i == 0 ) return -1;

    return i;
}

extern "C"
JNIEXPORT jstring JNICALL Java_com_ls_jnilib_jni_JNITest_readSnNum(JNIEnv *env, jclass type) {
//mnt/sdcard/snNum.dat
    FILE *FP = NULL;
    char aucBuff[4096] = {0};
    int iLen = 0;
    std::string str ="";

    FP = fopen("mnt/sdcard/snNum.dat", "rb");
    if(FP == NULL)
    {
        printf("Error**** open file %s faile\r\n","SN不存在");
        return NULL;
    }

    while(!feof(FP)) {
        memset(aucBuff, 0, sizeof(aucBuff));

        iLen = FileGetLine(FP, aucBuff, sizeof(aucBuff));

        printf("\r\n\r\nRead data:%s\r\n", aucBuff);

        str += aucBuff;
    }

    fclose(FP);


    return env->NewStringUTF(str.c_str());
}extern "C"
JNIEXPORT jstring JNICALL
Java_com_ls_jnilib_jni_JNITest_stringCopy(JNIEnv *env, jclass type, jstring source_) {
    const char *source = env->GetStringUTFChars(source_, 0);

    //定义新的字符数组
    char cap[128];
    strcpy(cap,source);

    env->ReleaseStringUTFChars(source_, source);

    return env->NewStringUTF(cap);  //strupr，函数的一种，将字符串s转换为大写形式。只能在VC中使用
}extern "C"
JNIEXPORT jint JNICALL
Java_com_ls_jnilib_jni_JNITest_addIntByteArray(JNIEnv *env, jclass type, jintArray byteArray_) {

    int i,sum = 0;

    jsize  len = env->GetArrayLength(byteArray_);
    jint *byteArray = env->GetIntArrayElements(byteArray_, NULL);
    for(i = 0;i<len;i++){
        sum  += byteArray[i];
    }

    env->ReleaseIntArrayElements(byteArray_, byteArray, 0);
    return sum;
}