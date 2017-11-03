%{ 
Program: remoteServer.m  Made By: Darrell Percey
Parses the data received from the TCP server built in remoteServer.m
will be divided into device by first number and key coded after device
type is decided.
Light: {1}0000
TV: {2}0000
Fan: {3}0000
Bath: {4}0000
%}
function parseData(x)
    global Light;
    global Fan;
    global FanSpeed;
    global BTemp;
    global BLevel;
    
    st = num2str(x);
    
    if(st(1) == '1')
        if(Light == 0)
            Light = 1;
            disp('Light On');
        else
            Light = 0;
            disp('Light Off');
        end
    elseif(st(1) == '2')
        if(st(2) == '1')
            disp('TV-Power');
        elseif(st(2) == '2')
            disp('TV-Channel Up');
        elseif(st(2) == '3')
            disp('TV-Channel Down');
        elseif(st(2) == '4')
            disp('TV-Volume Up');
        elseif(st(2) == '5')
            disp('TV-Volume Down');
        elseif(st(2) == '6')
            disp('TV-Menu');
        elseif(st(2) == '7')
            disp('TV-Source');
        end
    elseif(st(1) == '3')
        if(st(2) == '1')
            if(Fan == 1)
                disp('Fan Off');
                Fan = 0;
            else
                disp('Fan On');
                Fan = 1;
            end
        elseif(st(3) == '1')
            if(st(4) == '0')
                disp('Fan Speed Low');
            elseif(st(4) == '1')
                disp('Fan Speed Mid');
            elseif(st(4) == '2')
                disp('Fan Speed High');
            end
            FanSpeed = str2num(st(4));
        end
    elseif(st(1) == '4')
        BTemp = str2num(st(2:4));
        if(st(5) == '0')
            fprintf('Temperature: %d  Amount: Quarter \n',BTemp);
        elseif(st(5) == '1')
            fprintf('Temperature: %d  Amount: Half \n',BTemp);
        elseif(st(5) == '2')
            fprintf('Temperature: %d  Amount: Full \n',BTemp);
        end
        BLevel = str2num(st(5));
    end
end