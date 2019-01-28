package com.example.oceanlong.ndkmaintest;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    Button mBtnTest;
    EditText mEditTest;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
        mBtnTest = findViewById(R.id.test_btn);
        mEditTest = findViewById(R.id.test_input);
        mBtnTest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                final String s = mEditTest.getText().toString();
                for (int i = 0 ; i < 5 ; i++){
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            nativeToast(s);
                        }
                    }).start();
                }
            }
        });

    }

    public native void init();

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void nativeToast(String text);

    public static void toast(String text){
        Toast.makeText(MyAppImpl.getAppContext(), text, Toast.LENGTH_SHORT).show();
    }
}
