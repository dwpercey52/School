/*******************************************************
 * Name: Andrew Boven && Darrell Percey   Last Modified: 3/9/2017
 * Intro: Starts up a TV menu for the android app. When a
 * device is register to the main menu as a TV this class
 * will run.
 *********************************************************/

package school.remote_test;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.appindexing.Thing;
import com.google.android.gms.common.api.GoogleApiClient;

import java.net.InetAddress;
import java.io.*;
import java.net.*;



public class TV_menu extends AppCompatActivity {

    String ip = "0.0.0.0";
    Socket sock;
    InetAddress addr;
    PrintWriter out;
    Button power;
    Button ChUp;
    Button ChDown;
    Button VolUp;
    Button VolDown;
    Button Menu;
    Button Source;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tv_menu);

        //Declares all the buttons to test for code to send over to server
        power = (Button) findViewById(R.id.powerButton);
        ChUp = (Button) findViewById(R.id.ChUp);
        ChDown = (Button) findViewById(R.id.ChDown);
        VolUp = (Button) findViewById(R.id.VolUp);
        VolDown = (Button) findViewById(R.id.VolDown);
        Menu = (Button) findViewById(R.id.menuButton);
        Source = (Button) findViewById(R.id.sourceButton);

        //Gathers the IP from the main menu bundle
        ip = getIntent().getStringExtra("IP");
        startSocket(ip);
    }

    /*******************************************************
     * Name: Darrell Percey    Last Modified: 3/9/2017
     * Function: Sends the code over to the server based on a
     * code protocol we created. This is sent based on the button
     * that was pressed.
     *********************************************************/
    public void setCode(View view){

        if(view.getId() == power.getId())
            sendInformation(21000);
        else if(view.getId() == ChUp.getId())
            sendInformation(22000);
        else if(view.getId() == ChDown.getId())
            sendInformation(23000);
        else if(view.getId() == VolUp.getId())
            sendInformation(24000);
        else if(view.getId() == VolDown.getId())
            sendInformation(25000);
        else if(view.getId() == Menu.getId())
            sendInformation(26000);
        else if(view.getId() == Source.getId())
            sendInformation(27000);
        else
            sendInformation(20000);
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

