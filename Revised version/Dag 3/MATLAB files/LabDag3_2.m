


subplot(3, 2, 1);

plot(AngleTF(1,:), AngleTF(2,:));
load Encoder.mat;
plot(Encoder(1,:), Encoder(4,:));
title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on

hold on

load EulerRates.mat;
plot(AngleTF(1,:), AngleTF(2,:));
hold on

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(2,:));
legend('Encoder', 'TF pitch');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 2);
load Encoder.mat;
plot(Encoder(1,:), Encoder(5,:));
title('Pitch rate');
xlabel('Time');
ylabel('Pitch(rad/s)');
grid on

hold on

load EulerRates.mat;
plot(EulerRates(1,:), EulerRates(2,:));
hold on
plot(NoEncoder(1,:), NoEncoder(2,:));

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(2,:));
legend('Encoder', 'EulerAngles', 'Without encoder');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 3);
load Encoder.mat;
plot(Encoder(1,:), Encoder(6,:));
title('Elevation');
xlabel('Time');
ylabel('Elevation(rad)');
grid on

hold on

load AngleTF.mat;
plot(AngleTF(1,:), AngleTF(3,:));


%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(2,:));
legend('Encoder', 'TF elevation');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 4);

load Encoder.mat;
load NoEncoder.mat;
load EulerRates.mat;
plot(Encoder(1,:), Encoder(7,:))
title('Elevation rate');
xlabel('Time');
ylabel('Elevation(rad/s)');
grid on

hold on


plot(EulerRates(1,:), EulerRates(3,:));
hold on
plot(NoEncoder(1,:), NoEncoder(3,:));

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(3,:));
legend('Encoder', 'EulerAngles', 'Without encoder');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 5);

load Encoder.mat;
plot(Encoder(1,:), Encoder(3,:));
title('Travel rate');
xlabel('Time');
ylabel('Travel(rad/s)');
grid on

hold on

load EulerRates.mat;
plot(EulerRates(1,:), EulerRates(4,:));
hold on
plot(NoEncoder(1,:), NoEncoder(4,:));

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(4,:));
legend('Encoder', 'EulerAngles', 'Without encoder');
