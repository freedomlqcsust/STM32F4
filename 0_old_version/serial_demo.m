%ʹ��matlab�򿪵��Դ��ڶ�ȡ����
clear
close
a = instrfind;
delete(a);
str = 'please input com:\n';
n = input(str,'s');
%�½�һ�����ڶ���
obj = serial(n);
%-----------------------------------%
%obj.BytesAvailableFcnMode='byte';
obj.InputBufferSize=4096*2;
obj.BytesAvailableFcnCount=48;
obj.BaudRate=115200;
%-----------------------------------%
str1 = 'please input ad_point:\n';
d_num = input(str1);
fopen(obj);
%�·��ɼ��������Ϊ0x05(����������ֵ����ô����λ���յ�16�������������ַ���
% fprintf(obj,'%x',15);
% fwrite(obj,hex2dec(50),'uint8');
fwrite(obj,hex2dec('50'),'uint8');
fwrite(obj,hex2dec('51'),'uint8');
%��ȡָ��������AD���ݣ���Ҫ����λ�����
ad_data = fread(obj,d_num,'uint16');
plot(ad_data);
%filenameΪ��������ɣ��ļ����ݣ���ǰʱ����ļ���׺

%�����ļ��� adtemp_��ǰ����.txt
% file_name = ['adtemp_',datestr(now,30),'.txt'];
file_name = ['adtemp_',datestr(now,30),'.csv'];
% �򿪶�Ӧ�ļ������ļ����粻���� �½�
fileID = fopen(file_name,'w+');
% 
%fwrite(fileID,dec2hex(ad_data),'uint16');
fprintf(fileID,'%d\n',ad_data);

fclose(obj);
