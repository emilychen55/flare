package com.example.emilychen55.flare_v2;

import android.app.Activity;
import android.app.ActionBar;
import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.os.Build;
import android.content.Intent;
import android.widget.Button;
import com.parse.Parse;
import com.parse.ParseObject;
import com.parse.ParseQuery;
import com.parse.GetCallback;
import com.parse.ParseException;
import android.view.Menu;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.Switch;
import android.widget.TextView;
import android.os.Vibrator;
import android.util.Log;
import java.util.Timer;
import java.util.TimerTask;

public class Flare extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_flare);
        if (savedInstanceState == null) {
            getFragmentManager().beginTransaction()
                    .add(R.id.container, new PlaceholderFragment())
                    .commit();
        }
        Parse.initialize(this, "yC0kRgQVWDOjKZfvWtJrITDbzdDmEEqg6WKrjXoc", "6CSoQcuB7XNewa7Q7h9gC25dbsQCi5HCegJspxis");
    }

    private Timer timer = new Timer();
    private TimerTask timerTask;
    public void dataStream(View view) {
        timerTask = new TimerTask() {
            @Override
            public void run() {
                ParseQuery<ParseObject> query = ParseQuery.getQuery("LightStatus");
                query.orderByDescending("createdAt");
                query.getFirstInBackground(new GetCallback<ParseObject>() {
                    public void done(ParseObject object, ParseException e) {
                        TextView lightQuant = (TextView) findViewById(R.id.lightQuantity);
                        if (e == null) {
                            // object will be your game score
                            lightQuant.setText(Integer.toString(object.getInt("value")) + " ADC");
                            Log.d("value", Integer.toString(object.getInt("value")));
                        } else {
                            // something went wrong
                            lightQuant.setText("n/a");
                        }
                    }
                });
            }
        };
        timer.schedule(timerTask, 0, 1000);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.flare, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_flare, container, false);
            return rootView;
        }
    }

    // Switch
    public void switchInit(View view) {
        boolean on = ((Switch) view).isChecked();
        Vibrator v = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        if (on) {
            // Enable Vibrate for 500 milliseconds and lightOn
            lightOn();
            v.vibrate(500);
        } else {
            // Disable Vibrate and lightOff
            lightOff();
            v.cancel();
        }
    }

    // Lighting functions
    public void lightOn() {
        ParseObject lightCommand = new ParseObject("LightCommand");
        lightCommand.put("command", 1);
        lightCommand.saveInBackground();
    }
    public void lightOff() {
        ParseObject lightCommand = new ParseObject("LightCommand");
        lightCommand.put("command", 0);
        lightCommand.saveInBackground();
    }
}
