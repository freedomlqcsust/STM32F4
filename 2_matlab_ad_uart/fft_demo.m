function [fft_x,fft_y]=fft_demo(N,fft_data)
fs = 1400000;   %����Ƶ��
%fs = 1399900;
%������֪�����źŵļ������Ƿ���Է��Ƴ���Ƭ���Ĳ���Ƶ��
n=0:N-1;
fft_1=fft(fft_data,N);
% fft_1=fft_1-mean(fft_1);
mag=abs(fft_1);
f=n*fs/N;
fft_x = f(1:N/2);
fft_y = mag(1:N/2);
