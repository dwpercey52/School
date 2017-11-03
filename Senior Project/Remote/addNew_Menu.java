/*******************************************************
 * Name: Darrell Percey    Last Modified: 2/11/2017
 * Intro: When the user enters into this screen it will
 * display some user input boxes and a number picker. This will
 * allow the user to add new types of buttons to the main menu
 * screen.
 *********************************************************/
package school.remote_test;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.CheckBox;
import android.widget.NumberPicker;

public class addNew_Menu extends AppCompatActivity {


    //Declaring checkboxes of each type.
    private CheckBox Light;
    private CheckBox Bath;
    private CheckBox TV;
    private CheckBox Fan;
    private NumberPicker portPick;
    int portNumber;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_new__menu);

        //Setting object values.
        Light = (CheckBox) findViewById(R.id.typeLight);
        Bath = (CheckBox) findViewById(R.id.typeBath);
        TV = (CheckBox) findViewById(R.id.typeTV);
        Fan = (CheckBox) findViewById(R.id.typeFan);

        //Setting up numberpicker wheel
        portPick = (NumberPicker) findViewById(R.id.portNumber);
        portPick.setMinValue(1);
        portPick.setMaxValue(6);
        portPick.setWrapSelectorWheel(true);

        //Updates the values of the numberpicker as it changes.
        portPick.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
            @Override
            public void onValueChange(NumberPicker picker, int oldVal, int newVal){
                portNumber = newVal;
            }
        });


    }


    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Ensures that only one of the amount checkboxes
     * are checked at any given time. This is to avoid confusion
     * to the system when passing values.
     *********************************************************/
    public void checkBox(View view){

        if(view.getId() == Light.getId()){
            Bath.setChecked(false);
            TV.setChecked(false);
            Fan.setChecked(false);
        }
        else if(view.getId() == Bath.getId()){
            Light.setChecked(false);
            TV.setChecked(false);
            Fan.setChecked(false);
        }
        else if(view.getId() == Fan.getId()){
            Bath.setChecked(false);
            TV.setChecked(false);
            Light.setChecked(false);
        }
        else if(view.getId() == TV.getId()){
            Bath.setChecked(false);
            Light.setChecked(false);
            Fan.setChecked(false);
        }

    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Checks all the boxes to see which one is clicked.
     * Once it is found the value is set so that it can pass the type
     * back to the main menu to create the button.
     *********************************************************/
    public void sendType(View view) {
        int type = 0;
        if(Light.isChecked()){
            type = 1;
        }
        else if(Bath.isChecked()){
            type = 2;
        }
        else if(TV.isChecked()){
            type = 3;
        }
        else if(Fan.isChecked()){
            type = 4;
        }

        Intent intent = new Intent();
        intent.putExtra("Type",type);
        intent.putExtra("Port",portNumber);
        setResult(RESULT_OK, intent);
        finish();
    }
}
