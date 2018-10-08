function [fft_x,fft_y]=fft_demo(N,fft_data)
fs = 14000000;   %²ÉÑùÆµÂÊ
n=0:N-1;
fft_1=fft(fft_data,N);
mag=abs(fft_1);
f=n*fs/N;
fft_x = f(1:N/2);
fft_y = mag(1:N/2);
