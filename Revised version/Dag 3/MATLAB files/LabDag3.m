
subplot(3, 2, 1);

load Encoder.mat;
load Gyro.mat;
plot(Encoder(1,:), Encoder(5,:));
title('Pitch rate');
grid on
hold on


plot(Gyro(1,:), Gyro(2,:));
legend('Encoder', 'Gyro');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 3);
load Encoder.mat;
plot(Encoder(1,:), Encoder(7,:));
title('Elevation rate');
grid on;
hold on

plot(Gyro(1,:), Gyro(3,:));
legend('Encoder', 'Gyro');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 5);
load EulerRates.mat;
plot(Encoder(1,:), Encoder(3,:));
title('Travel rate');
grid on;
hold on

plot(Gyro(1,:), Gyro(4,:));
legend('Encoder', 'Gyro');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 2);
load eulerAngles.mat;
plot(eulerAngles(1,:), eulerAngles(2,:));
title('a_x');
xlabel('Time');
ylabel('PitchRate(rad/s)');
grid on;
legend('Accelerometer');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 4);
plot(eulerAngles(1,:), eulerAngles(3,:));
title('a_y');
xlabel('Time');
ylabel('PitchRate(rad/s)');
grid on;
legend('Accelerometer');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 6);
plot(eulerAngles(1,:), eulerAngles(4,:));
title('a_z');
xlabel('Time');
ylabel('PitchRate(rad/s)');
grid on;
legend('Accelerometer');
