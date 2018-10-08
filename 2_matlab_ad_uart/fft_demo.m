function [fft_x,fft_y]=fft_demo(N,fft_data)
fs = 1400000;   %采样频率
%fs = 1399900;
%根据已知周期信号的计算结果是否可以反推出单片机的采样频率
n=0:N-1;
fft_1=fft(fft_data,N);
% fft_1=fft_1-mean(fft_1);
mag=abs(fft_1);
f=n*fs/N;
fft_x = f(1:N/2);
fft_y = mag(1:N/2);
