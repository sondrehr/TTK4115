
subplot(3, 1, 1);
load Encoder.mat;
plot(Encoder(1,:), Encoder(5,:));
title('Pitch rate');
xlabel('Time');
ylabel('Pitch(rad/s)');
grid on

hold on

load EulerRates.mat;
plot(EulerRates(1,:), EulerRates(2,:));

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(2,:));
legend('Encoder', 'EulerAngles');



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 1, 2);

load Encoder.mat;
plot(Encoder(1,:), Encoder(7,:))
title('Elevation rate');
xlabel('Time');
ylabel('Elevation(rad/s)');
grid on

hold on

load EulerRates.mat;
plot(EulerRates(1,:), EulerRates(3,:));


%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(3,:));
legend('Encoder', 'EulerAngles');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 1, 3);

load Encoder.mat;
plot(Encoder(1,:), Encoder(3,:));
title('Travel rate');
xlabel('Time');
ylabel('Travel(rad/s)');
grid on

hold on

load EulerRates.mat;
plot(EulerRates(1,:), EulerRates(4,:));

%hold on

%load EulerRates_NoEncoder.mat;
%plot(EulerRates_NoEncoder(1,:), EulerRates_NoEncoder(4,:));
legend('Encoder', 'EulerAngles');
