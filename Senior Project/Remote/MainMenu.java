/*******************************************************
 * Name: Darrell Percey    Last Modified: 2/11/2017
 * Intro: Main menu for controlling buttons of a multi-device
 * remote. The functions listed here should allow for adding
 * and deleting devices from the home menu.
 *********************************************************/

package school.remote_test;

import android.content.ComponentName;
import android.content.Context;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.support.v7.widget.*;
import android.support.v7.widget.ActionMenuView;
import android.view.MenuInflater;
import android.view.View;
import android.widget.*;
import android.widget.PopupMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.PopupMenu.OnMenuItemClickListener;

public class MainMenu extends AppCompatActivity {

    private MainMenu test;

    //Declaring an object to control each of the 6 buttons.
    MyService myServ;
    boolean servBound = false;
    Button but1;
    Button but2;
    Button but3;
    Button but4;
    Button but5;
    Button but6;
    EditText ipText;
    EditText deleteNum;
    String serverIP = "0.0.0.0";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_menu);

        //Labels objects for each button by putting it with a button in XML layout
        but1 = (Button) findViewById(R.id.button1);
        but2 = (Button) findViewById(R.id.button2);
        but3 = (Button) findViewById(R.id.button3);
        but4 = (Button) findViewById(R.id.button4);
        but5 = (Button) findViewById(R.id.button5);
        but6 = (Button) findViewById(R.id.button6);
        deleteNum = (EditText) findViewById(R.id.deleteText);
        ipText = (EditText) findViewById(R.id.ipAddress);

        SharedPreferences mainButtons = getSharedPreferences("main_pref",MODE_PRIVATE);

        //Uses shared pref. to restore previous values in buttons.


        setType(but1,mainButtons.getInt("button1", 0));
        setType(but2,mainButtons.getInt("button2", 0));
        setType(but3,mainButtons.getInt("button3", 0));
        setType(but4,mainButtons.getInt("button4", 0));
        setType(but5,mainButtons.getInt("button5", 0));
        setType(but6,mainButtons.getInt("button6", 0));
        serverIP = mainButtons.getString("ip","0.0.0.0");



    }



    @Override
    protected void onStart(){
        super.onStart();
    }

    @Override
    protected void onStop(){
        super.onStop();
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
    }



    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Changes the IP address of the server
     * and saves it so when the program is launched it will remember
     * the last used IP.
     *********************************************************/
    public void changeAddress(View view){
        SharedPreferences.Editor mainEditor = getSharedPreferences("main_pref",MODE_PRIVATE).edit();
        serverIP = ipText.getText().toString();
        Toast.makeText(this,"IP changed",Toast.LENGTH_SHORT).show();
        mainEditor.putString("ip",serverIP);
        mainEditor.apply();
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Starts a light menu for a light device
     * simple on/off switch function
     * Sends the ip for socket
     *********************************************************/
    public void LightAct(View view) {
        Intent Light = new Intent(this, Light_Menu.class);
        Light.putExtra("IP",serverIP);
        startActivity(Light);
    }

    /*******************************************************
     * Name: Andrew Boven && Darrell Percey   Last Modified: 3/9/2017
     * Function: Starts a menu for a fan device
     * will use the layout for activity of a fan---> See Fan XML
     * Sends the ip for socket
     *********************************************************/
    public void FanAct(View view){
        Intent Fan = new Intent(this, Fan_Menu.class);
        Fan.putExtra("IP",serverIP);
        startActivity(Fan);
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Starts a bath menu for bath device
     * will use the layour for activity of a bath---> See Bath XML
     * Sends the ip for socket
     *********************************************************/
    public void BathAct(View view) {
        Intent Bath = new Intent(this, Bath_Menu.class);
        Bath.putExtra("IP",serverIP);
        startActivity(Bath);
    }

    /*******************************************************
     * Name: Andrew Boven    Last Modified: 3/9/2017
     * Function: Starts a TV menu for a TV will use a
     * layout for a TV activity---> See TV XML
     * Sends the IP for socket
     *********************************************************/
    public void TVAct(View view) {
        Intent TV = new Intent(this, TV_menu.class);
        TV.putExtra("IP",serverIP);
        startActivity(TV);
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Generates the activity for adding a new button
     * Layout is produced from XML file --->See AddNew XML
     *********************************************************/
    public void addNewButton(View view){
        Intent addNew = new Intent(this, addNew_Menu.class);
        startActivityForResult(addNew, 1);
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Blank function for when buttons are cleared
     * of their type (Fan/Light/ETC)
     *********************************************************/
    public void clearAct(View view){
        // Do nothing
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Decides which button is suppose to be deleted
     * based on the user's input in the edittext field and sets
     * it to a type 0 "free" button.
     *********************************************************/
    public void deleteButton(View view){
        SharedPreferences.Editor mainEditor = getSharedPreferences("main_pref",MODE_PRIVATE).edit();

        String i = deleteNum.getText().toString();

        int typeSet = Integer.valueOf(i);
        if( typeSet <= 6 || typeSet >= 1){
            switch(typeSet){
                case 1:
                    setType(but1, 0);
                    mainEditor.putInt("button1",0);
                    break;
                case 2:
                    setType(but2, 0);
                    mainEditor.putInt("button2",0);
                    break;
                case 3:
                    setType(but3, 0);
                    mainEditor.putInt("button3",0);
                    break;
                case 4:
                    setType(but4, 0);
                    mainEditor.putInt("button4",0);
                    break;
                case 5:
                    setType(but5, 0);
                    mainEditor.putInt("button5",0);
                    break;
                case 6:
                    setType(but6, 0);
                    mainEditor.putInt("button6",0);
                    break;
            }

            mainEditor.commit();
        }
        else{
            Context con = getApplicationContext();
            int time = Toast.LENGTH_SHORT;
            String text = "Put a proper delete value!";
            Toast deleteError = Toast.makeText(con,text,time);
            deleteError.show();
        }
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: When returning from the addNew activity
     * the results are pulled in for the checkBox that was ticked
     * which gives a type 0-4 (Free/Light/Bath/TV/Fan)
     *********************************************************/
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        SharedPreferences.Editor mainEditor = getSharedPreferences("main_pref",MODE_PRIVATE).edit();
        if (requestCode == 1) {
            if (resultCode == RESULT_OK) {
                int type = data.getIntExtra("Type",0);
                int port = data.getIntExtra("Port",0);
                switch(port){
                    case 1:
                        setType(but1,type);
                        mainEditor.putInt("button1",type);
                        break;
                    case 2:
                        setType(but2,type);
                        mainEditor.putInt("button2",type);
                        break;
                    case 3:
                        setType(but3,type);
                        mainEditor.putInt("button3",type);
                        break;
                    case 4:
                        setType(but4,type);
                        mainEditor.putInt("button4",type);
                        break;
                    case 5:
                        setType(but5,type);
                        mainEditor.putInt("button5",type);
                        break;
                    case 6:
                        setType(but6,type);
                        mainEditor.putInt("button6",type);
                        break;
                    default:
                        break;
                }
                mainEditor.commit();

            }
        }
    }


    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Passed from the acitvity return. The button that
     * will change is passed over found already and the type is set
     * here. This changes the text and onClick listener for a new
     * function type.
     *********************************************************/
    private void setType(Button b, int type){
        switch(type){
            case 0:
                b.setText("Free");
                b.setOnClickListener(new View.OnClickListener(){
                    @Override
                    public void onClick(View v){
                        clearAct(v);
                    }
                });
                break;
            case 1:
                b.setText("Light");
                b.setOnClickListener(new View.OnClickListener(){
                    @Override
                    public void onClick(View v){
                        LightAct(v);
                    }
                });
                break;
            case 2:
                b.setText("Bath");
                b.setOnClickListener(new View.OnClickListener(){
                    @Override
                    public void onClick(View v){
                        BathAct(v);
                    }
                });
                break;
            case 3:
                b.setText("TV");
                b.setOnClickListener(new View.OnClickListener(){
                    @Override
                    public void onClick(View v){
                        TVAct(v);
                    }
                });
                break;
            case 4:
                b.setText("Fan");
                b.setOnClickListener(new View.OnClickListener(){
                    @Override
                    public void onClick(View v){
                        FanAct(v);
                    }
                });
                break;
            default:
                break;
        }
    }
}

