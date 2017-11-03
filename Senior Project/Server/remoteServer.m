%{ 
Program: remoteServer.m  Made By: Darrell Percey && Andrew Boven
TCP server that checks for connects from the Android based remote
and sends data to parseData function to decide on what to send to 
HUB device for computing. Also lays an interface for debugging
%}

clear all;
global Light
global Fan
global FanSpeed
global BTemp
global BLevel
Light = 0;
Fan = 0;
FanSpeed = 0;
BTemp = 0;
BLevel = 0;

%Setup of original connection and socket
tCmd = tcpip('0.0.0.0', 30000, 'NetworkRole', 'server');
set(tCmd,'InputBufferSize',1000);
set(tCmd,'OutputBufferSize',1000);
disp('Waiting for connection...');
fopen(tCmd);
disp('Connection accpeted...');
%MyTelnetCommand = '(sendCommand cmd_Start 0 -1 1)';
%MyTelnetCommandConverted = double(MyTelnetCommand)';
%fprintf(tCmd, MyTelnetCommandConverted);

%While loop waits for data and time out after 15seconds
while(true)
tic
    while(tCmd.BytesAvailable<=0)
        drawnow
        x = toc;
        if( x > 15)
            fclose(tCmd);
            disp('User timed out...');
            disp('Waiting for new connection...');
            fopen(tCmd);
            disp('New connection accepted...');
            tic
        end
    end
    
    %reads data from socket and passes to Parse
    %if code 50000 received drops connection and looks for new one
    response = fscanf(tCmd,'%d', tCmd.BytesAvailable);
    fprintf('Code: %d \n',response);
    str = num2str(response);
    parseData(response);
    
    %Drops connection and searches for a new one
    if(str(1) == '5')
        fclose(tCmd);
        disp('Activity Closed....');
        disp('Waiting for new connection...');
        fopen(tCmd);
        disp('New connection accpeted...');
    end
end

fclose(tCmd);
