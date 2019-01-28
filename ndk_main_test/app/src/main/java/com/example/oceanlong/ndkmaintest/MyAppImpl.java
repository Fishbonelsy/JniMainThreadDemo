package com.example.oceanlong.ndkmaintest;

import android.app.Application;
import android.content.Context;

/**
 * Created by oceanlong on 2018/10/17.
 */

public class MyAppImpl extends Application {

    private static Context mContext;

    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
    }

    public static Context getAppContext(){
        return mContext;
    }


}
