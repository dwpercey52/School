package school.remote_test;


import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.widget.Toast;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class MyService extends Service {

    private final IBinder myBinder = new LocalService();
    Socket sock;
    InetAddress addr;
    PrintWriter out;

    @Override
    public IBinder onBind(Intent intent){
        sock = new Socket();
        Toast.makeText(this,"Service started", Toast.LENGTH_LONG).show();
        Runnable connect = new connectSocket();
        new Thread(connect).start();
        return myBinder;
    }

    public class LocalService extends Binder {
        MyService getService(){
            return MyService.this;
        }

    }

    @Override
    public void onCreate(){
        super.onCreate();

    }


    public void sendOnSocket(int message){


        class sendSocket implements Runnable{
            private int mess;
            public sendSocket(int mess){
                this.mess = mess;
            }

            @Override
            public void run(){
                out.println(mess);
            }
        }
        Thread send = new Thread(new sendSocket(message));
        send.start();

    }



    class connectSocket implements Runnable {

        @Override
        public void run() {
            try {
                addr = InetAddress.getByName("192.168.1.143");
                sock = new Socket(addr,30000);
                out = new PrintWriter(sock.getOutputStream(),true);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        try {
            sock.close();
        } catch (IOException e) {

            e.printStackTrace();
        }
        sock = null;
    }
}
