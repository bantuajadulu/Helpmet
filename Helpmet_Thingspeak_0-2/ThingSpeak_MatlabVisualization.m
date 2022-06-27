readChannelID = [1421256];
readAPIKey = '1QJ4X6H5K784DHLC';
writeChannelID = [1421256];
writeAPIKey = 'SQZSOC8VVKBCKHC1';

data_latih = [  92	2668;187	4324;256	11365; 234	1303;
147	5288; 46	6739;272	4653;177	2838;208	8270;
267	3100;237	12106;309	4840;228	2713;
260	11282;296	7402;273	19150;202	1240;289	4146;
10	1352;11	3451;9	1774;19	3178;25	2254;10	2380;11	4677;9	2597;10	1731;11	1011;
10	1633;10	1628;]
Y = [1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;0;0;0;0;0;0;0;0;0;0;0;0];
fs=data_latih(:,1); v=data_latih(:,2);
flat=(fs-mean(fs))/std(fs);
vlat=(v-mean(v))/std(v);
dlat=[flat,vlat];
nbayes = fitcnb(dlat, Y, 'Distribution', 'normal');
datji = [200 3207]%thingSpeakRead(readChannelID, 'ReadKey', readAPIKey, 'Field',[3 4]);
fu=datji(:,1);vu=datji(:,2);
fuji=(fu-mean(fs))/std(fs);
vuji=(vu-mean(v))/std(v);
uji=[fuji,vuji];
analyzedData = predict(nbayes,uji);
if analyzedData == 1
    faceColorPatch=[1 1 0];
    prediksi='Kecelakaan';
else 
    faceColorPatch=[0 1 0];
   prediksi='Berjalan';
end
figure
rectangle('Position',[1,3,5,10],'FaceColor',faceColorPatch,'EdgeColor',faceColorPatch,...
    'LineWidth',3)
 ax=gca;
 set(ax, 'Visible','off')
 dim = [0.4 0.5 0 0.1];
 annotation('textbox',dim,'String',prediksi,'FontSize',20,'FitBoxToText','on');