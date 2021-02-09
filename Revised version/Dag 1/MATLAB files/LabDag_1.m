



subplot(2, 1, 1);
load Encoder.mat;
load Reference.mat
plot(Reference(1,:), Reference(2,:));

title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on
% hold on
%plot(enc_1_2(1,:), enc_1_2(4,:));
hold on
plot(enc_3_4(1,:), enc_3_4(4,:));
% % hold on
% %plot(enc_3_4(1,:), enc_3_4(4,:));
% % hold on
% % plot(enc_4_5(1,:), enc_4_5(4,:));
% % hold on
% % plot(enc_5_6(1,:), enc_5_6(4,:));
hold on
plot(IQ1531055(1,:), IQ1531055(3,:));
hold on
plot(Estimators(1,:), Estimators(2,:));
% hold on
% plot(enc_joy34(1,:), enc_joy34(4,:));
legend('Reference','-2 -3', '-1+i -1-i', '-2+3i -2-3i');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(2, 1, 2);

plot(Reference(1,:), Reference(3,:));
title('Elevation');
xlabel('Time');
ylabel('Elevation(rad)');
grid on
% hold on
% plot(enc_1_2(1,:), enc_1_2(6,:));
hold on
plot(enc_2_3(1,:), enc_2_3(6,:));
% hold on
% plot(enc_3_4(1,:), enc_3_4(6,:));
% hold on
% plot(enc_4_5(1,:), enc_4_5(6,:));
% hold on
% plot(enc_5_6(1,:), enc_5_6(6,:));
hold on
plot(enc_1i_1i(1,:), enc_1i_1i(6,:));
hold on
plot(enc_2i_3i(1,:), enc_2i_3i(6,:));
% hold on
% plot(enc_joy34(1,:), enc_joy34(4,:));
legend('Reference','-2 -3', '-1+i -1-i', '-2+3i -2-3i');

