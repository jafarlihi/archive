package jafarlihi.github.io.spinnerimages;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.ArrayAdapter;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ImageView;
import android.view.View;

public class MainActivity extends AppCompatActivity implements OnItemSelectedListener {

    ImageView imageBox;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Spinner spinner = (Spinner) findViewById(R.id.spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.cool_planets_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        imageBox = (ImageView) findViewById(R.id.imageView);

        spinner.setOnItemSelectedListener(this);
    }

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
        String selected = parent.getItemAtPosition(pos).toString();

        switch (selected) {
            case "Earth":
                imageBox.setImageResource(R.drawable.earth);
                break;
            case "Mars":
                imageBox.setImageResource(R.drawable.mars);
                break;
            case "Jupiter":
                imageBox.setImageResource(R.drawable.jupiter);
                break;
            case "Saturn":
                imageBox.setImageResource(R.drawable.saturn);
                break;
        }
    }

    public void onNothingSelected(AdapterView<?> parent) {

    }
}
