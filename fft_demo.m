function [fft_x,fft_y]=fft_demo(N,fft_data)
fs = 14000000;   %采样频率
n=0:N-1;
% t=n/fs;
%信号
%fx=0.5*sin(2*pi*15*t)+2*sin(2*pi*40*t);
% fx=0.5*sin(2*pi*150*t);

fft_1=fft(fft_data,N);
mag=abs(fft_1);
f=n*fs/N;

fft_x = f(1:N/2);
fft_y = mag(1:N/2);
% plot(f(1:N/2),mag(1:N/2));