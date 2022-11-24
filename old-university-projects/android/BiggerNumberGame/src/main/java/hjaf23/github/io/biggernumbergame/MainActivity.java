package jafarlihi.github.io.biggernumbergame;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.view.View;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int fn;
    private int sn;
    private int score = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        newRound();
    }

    protected void newRound() {
        Button Button1 = (Button) findViewById(R.id.button);
        Button Button2 = (Button) findViewById(R.id.button2);
        Random randGen = new Random();
        fn = 0;
        sn = 0;

        Button1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                fnSelected();
            }
        });

        Button2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                snSelected();
            }
        });


        while (fn == sn) {
            fn = randGen.nextInt(100);
            sn = randGen.nextInt(100);
        }

        Button1.setText(String.valueOf(fn));
        Button2.setText(String.valueOf(sn));
    }

    protected void fnSelected() {
        if (fn > sn) {
            Toast.makeText(this, "Correct number selected!", Toast.LENGTH_LONG).show();
            score++;
        } else {
            Toast.makeText(this, "Wrong number selected.", Toast.LENGTH_LONG).show();
            score--;
        }

        TextView scoreboard = (TextView) findViewById(R.id.textView);
        scoreboard.setText("Points: " + score);
        newRound();
    }

    protected void snSelected() {
        if (sn > fn) {
            Toast.makeText(this, "Correct number selected!", Toast.LENGTH_LONG).show();
            score++;
        } else {
            Toast.makeText(this, "Wrong number selected.", Toast.LENGTH_LONG).show();
            score--;
        }

        TextView scoreboard = (TextView) findViewById(R.id.textView);
        scoreboard.setText("Points: " + score);
        newRound();
    }
}
