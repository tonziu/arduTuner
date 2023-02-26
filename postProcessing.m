clear all
close all
clc

%% Acquisition

s1 = serial('COM5', 'BaudRate', 115200);        
N = 10000;                                       

fopen(s1);
while(strcmp(fscanf(s1, '%c', 1), '\n'))
end

str1 = sprintf('%s', [' ', fscanf(s1, '%c', 80)]);
vector = zeros();

for i=1:N
    vector(i) = str2double(fscanf(s1, '%c', 80));
end

fclose(s1);
delete(instrfindall);

%% Plotting time signal

fsamp = 1000;                                    
t = 0:1/fsamp:N*1/fsamp-1/fsamp;
figure(1)
plot(t, vector);                               
v = vector;
grid on
xlabel('time [s]');
ylabel('Voltage [mV]');


%% FFT

yfft = abs(fft(vector))*2/length(vector);
f = fsamp/length(vector):fsamp/length(vector):fsamp/2-fsamp/length(vector);

figure(2)
plot(f, yfft(2:end/2))
grid on
xlabel('frequency [Hz]');

[val, index] = max(yfft(2:end));
note = f(index);
