
subplot(3,2,1);
load Encoder.mat;
load Kalman.mat;
load pitch.mat;
load Measurement.mat;
plot(Measurement(1,:), Measurement (2,:));
title('Pitch')
xlabel('Time');
ylabel('Pitch(rad)');
grid on
hold on
plot(Encoder(1,:), Encoder(4,:));
hold on
plot(Kalman(1,:), Kalman(2,:));
plot(pitch(1,:), pitch(2,:));
legend('Measurement', 'Encoder', 'Kalman', 'reference');

subplot(3,2,2);
plot(Measurement(1,:), Measurement (3,:));
title('Pitch rate')
xlabel('Time');
ylabel('Pitch rate(rad/s)');
grid on
hold on
plot(Encoder(1,:), Encoder(5,:));
hold on
plot(Kalman(1,:), Kalman(3,:));
legend('Measurement', 'Encoder', 'Kalman');

subplot(3,2,3);
plot(Measurement(1,:), Measurement (4,:));
title('Elevation')
xlabel('Time');
ylabel('Elevation(rad)');
grid on
hold on
plot(Encoder(1,:), Encoder(6,:));
hold on
plot(Kalman(1,:), Kalman(4,:));
legend('Measurement', 'Encoder', 'Kalman');

subplot(3,2,4);
plot(Measurement(1,:), Measurement (5,:));
title('Elevation rate')
xlabel('Time');
ylabel('Elevation rate(rad/s)');
grid on
hold on
plot(Encoder(1,:), Encoder(7,:));
hold on
plot(Kalman(1,:), Kalman(5,:));
plot(elevation_rate(1,:), elevation_rate(2,:))
legend('Measurement', 'Encoder', 'Kalman', 'reference');


subplot(3,2,5);
plot(Encoder(1,:), Encoder(2,:));
title('Travel')
xlabel('Time');
ylabel('Travel(rad)');
grid on
hold on
plot(Kalman(1,:), Kalman(6,:));
legend('Encoder', 'Kalman');

subplot(3,2,6);
plot(Measurement(1,:), Measurement (6,:));
title('Travel rate')
xlabel('Time');
ylabel('Travel rate(rad/s)');
hold on
plot(Encoder(1,:), Encoder(3,:));
hold on
plot(Kalman(1,:), Kalman(7,:));
legend('Measurement', 'Encoder', 'Kalman');


