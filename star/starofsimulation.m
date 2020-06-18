%  m = 256;
% n = 56;
%  A = 0*ones(160,320);
%  B = uint8(A);
%  imshow(B)
data = xlsread('C://Users//w//Desktop//star//data//starofsimulation.xlsx');
row_data = size(data,1);%求出二维数组的行数
w = 960;
h = 540;
A=0*ones(h,w);
deta = 0.1726;
for i=1:row_data
        x_c=(data(i,5));
        y_c=(data(i,6));
        %C=255/2.512^(data(i,2)-4);
        C=255;
        A(int16(h/2+x_c),int16(w/2+y_c))=C; 
        A(int16(h/2+x_c-1),int16(w/2+y_c-1))=C;
        A(int16(h/2+x_c),int16(w/2+y_c-1))=C;
        A(int16(h/2+x_c-1),int16(w/2+y_c+1))=C;
        A(int16(h/2+x_c+1),int16(w/2+y_c-1))=C;
        A(int16(h/2+x_c-1),int16(w/2+y_c))=C;
        A(int16(h/2+x_c+1),int16(w/2+y_c))=C;
        A(int16(h/2+x_c),int16(w/2+y_c+1))=C;
        A(int16(h/2+x_c+1),int16(w/2+y_c+1))=C;
        %fprintf('%d,%d,%d\n',160+x*10,160+y*10,C);
end
%B=uint8(A);
%C=imnoise(B,'gaussian');
%subplot(1,2,1);imshow(B);
%subplot(1,2,2);imshow(C);
imshow(B);
%h = fspecial('gaussian',3);
%D = medfilt(C,[3,3]);



