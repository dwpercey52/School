/*******************************************************
 * Name: Darrell Percey    Last Modified: 3/9/2017
 * Intro: Starts up a Bath menu for the android app. When a
 * device is register to the main menu as a Bath this class
 * will run.
 *********************************************************/

package school.remote_test;

import android.content.Context;
import android.support.annotation.IdRes;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.CheckBox;
import android.widget.TextView;
import android.view.View;
import android.widget.Toast;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class Bath_Menu extends AppCompatActivity {

    //Min for lowest temperature and max for highest set
    //Each checkbox is declared for later user
    private int min = 65;
    private int max = 100;
    String ip = "0.0.0.0";
    String codeSet;
    Button send;
    Socket sock;
    InetAddress addr;
    PrintWriter out;
    int value;
    private SeekBar waterTemperatureBar;
    private TextView temperatureDisplay;
    private CheckBox waterAmount1, waterAmount2, waterAmount3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bath__menu);

        //Setting the objects of each of the checkboxes
        waterAmount1 = (CheckBox) findViewById(R.id.waterAmount1);
        waterAmount2 = (CheckBox) findViewById(R.id.waterAmount2);
        waterAmount3 = (CheckBox) findViewById(R.id.waterAmount3);
        send = (Button) findViewById(R.id.startButton);

        //Setting object for the seekBar and the text update of the seekbar
        waterTemperatureBar = (SeekBar) findViewById(R.id.waterTemperatureBar);
        temperatureDisplay = (TextView) findViewById(R.id.temperatureText);
        waterTemperatureBar.setMax((max-min));

        //Builds the socket on launch of bath menu
        ip = getIntent().getStringExtra("IP");
        startSocket(ip);

        //Sets the listener to the seek bar so that the updated value will display on screen
        waterTemperatureBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar waterTemperatureBar, int progress, boolean fromUser) {
                value = min + (progress);
                temperatureDisplay.setText(String.valueOf(value));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

    }





    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: Ensures that only one of the amount checkboxes
     * are checked at any given time. This is to avoid confusion
     * to the system when passing values.
     *********************************************************/
    public void checkBoxSingle(View view){

        if(view.getId() == waterAmount1.getId()){
            waterAmount2.setChecked(false);
            waterAmount3.setChecked(false);
        }
        else if(view.getId() == waterAmount2.getId()){
            waterAmount1.setChecked(false);
            waterAmount3.setChecked(false);
        }
        else if(view.getId() == waterAmount3.getId()){
            waterAmount2.setChecked(false);
            waterAmount1.setChecked(false);
        }

    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: This will later send a message over to the system.
     * For now it displays information that the bath will start
     * or that they need to put a proper input. If the amounts picked are
     * okay then the program will compile a string to send over to the TCP
     * server with the appropriate coding for the protocol.
     *********************************************************/
    public void startBath(View view){
        boolean startOkay = false;
        if(!waterAmount1.isChecked() && !waterAmount2.isChecked() && !waterAmount3.isChecked()){
           startOkay =  displayMessage(1);
        }
        else{
           startOkay = displayMessage(2);
            codeSet = "4";
            if(value < 100){
                codeSet = codeSet.concat("0");
                codeSet = codeSet.concat(Integer.toString(value));
            }
            else{
                codeSet = codeSet.concat(Integer.toString(value));
            }


            if(waterAmount1.isChecked())
                codeSet = codeSet.concat("2");
            else if(waterAmount2.isChecked())
                codeSet = codeSet.concat("1");
            else
                codeSet = codeSet.concat("0");

            sendInformation(Integer.valueOf(codeSet));
        }
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 2/11/2017
     * Function: pushes the toast to the screen for the user to see
     *********************************************************/
    public boolean displayMessage(int var){
        boolean startOkay = false;
        Context context = getApplicationContext();
        int time = Toast.LENGTH_SHORT;
        CharSequence text;

        if(var == 1){
            text = "Pick a water amount";
        }
        else{
            text = "Starting";
            startOkay = true;
        }

        Toast toast = Toast.makeText(context,text,time);
        toast.show();
        return startOkay;
    }


    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Overwrites the back button to send code 50000
     * to the server which indiciates to close the TCP socket
     * and look for a new connection.
     *********************************************************/
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)  {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            sendInformation(50000);

            finish();
        }
        return true;
    }


    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Pushes the integer over the socket from the
     * Printwriter.
     *********************************************************/
    public void sendInformation(int x){
        class sendSocket implements Runnable{
            private int mess;
            public sendSocket(int mess){
                this.mess = mess;
            }

            @Override
            public void run(){
                if(out != null) {
                    out.println(mess);
                }
            }
        }

        Thread send = new Thread(new sendSocket(x));
        send.start();
    }


    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Takes the IP passed from the main meny and sets up
     * the TCP socket to the server.
     *********************************************************/
    public void startSocket(String ip) {

        class MakeSocket implements Runnable{
            private String server;
            public MakeSocket(String server){this.server = server;}

            @Override
            public void run () {
                try {
                    addr = InetAddress.getByName(server);
                    sock = new Socket(addr, 30000);
                    out = new PrintWriter(sock.getOutputStream(), true);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

        if(sock == null){
            Thread make = new Thread(new MakeSocket(ip));
            make.start();
        }
    }
}
