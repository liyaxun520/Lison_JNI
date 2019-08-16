package com.ls.jnilsdemo

import android.Manifest
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.ls.jnilib.jni.JNITest
import android.support.v4.app.ActivityCompat.shouldShowRequestPermissionRationale
import android.Manifest.permission
import android.widget.Toast
import com.tbruyelle.rxpermissions2.RxPermissions



class MainActivity : AppCompatActivity() {

    private val TAG:String = MainActivity::class.java.simpleName

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var string = JNITest.getString()
        Log.d(TAG,"c返回   $string")

        JNITest.setNumber(1000)
        var number = JNITest.getNumber()
        Log.d(TAG,"c返回   $number")

        var stringToChar = JNITest.changeStringToChar("测试数据JNi传输")
        Log.d(TAG,"c返回   $stringToChar")

        getPermission()

        var strCpy = JNITest.stringCopy("abcdefghijkllmvopqrstuvwxyz")
        Log.d(TAG,"c返回   $strCpy")


        var intArray = intArrayOf(1, 3, 5, 7, 9, 10)
        var sum = JNITest.addIntByteArray(intArray)
        Log.d(TAG,"c返回  求和   $sum")
    }

    private fun getPermission() {
        val rxPermissions = RxPermissions(this)
        rxPermissions.request(Manifest.permission.WRITE_EXTERNAL_STORAGE)
            .subscribe { permission ->
                if (permission) {
                    var readSnNum = JNITest.readSnNum()
                    Log.d(TAG,"c返回   $readSnNum")
                }else{
                    Toast.makeText(MainActivity@this,"未获取到权限",Toast.LENGTH_SHORT).show()
                }
            }
    }
}
