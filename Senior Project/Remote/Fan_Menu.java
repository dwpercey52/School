/*******************************************************
 * Name: Andrew Boven && Darrell Percey    Last Modified: 3/9/2017
 * Intro: Starts up a Fan menu for the android app. When a
 * device is register to the main menu as a Fan this class
 * will run.
 *********************************************************/

package school.remote_test;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class Fan_Menu extends AppCompatActivity {


    String ip = "0.0.0.0";
    Button power;
    Button low;
    Button mid;
    Button high;
    Socket sock;
    InetAddress addr;
    PrintWriter out;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fan__menu);

        //Declaring all the buttons used for testing codes to send
        power = (Button) findViewById(R.id.toggleButton);
        low = (Button) findViewById(R.id.lowButton);
        mid = (Button) findViewById(R.id.midButton);
        high = (Button) findViewById(R.id.highButton);

        //Gathers the ip from the main menu bundle
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
            sendInformation(31000);
        else if(view.getId() == low.getId())
            sendInformation(30100);
        else if(view.getId() == mid.getId())
            sendInformation(30110);
        else if(view.getId() == high.getId())
            sendInformation(30120);
        else
            sendInformation(30000);

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

