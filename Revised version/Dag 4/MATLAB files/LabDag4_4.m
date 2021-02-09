

subplot(2, 1, 1);
plot(pitch(1,:), pitch(2, :));
title('Comparison pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on
hold on
plot(enc_3_4(1,:), enc_3_4(4, :));
hold on
plot(IQ1531055(1,:), IQ1531055(3, :));
hold on
plot(Estimators(1,:), Estimators(2, :));
hold on
plot(Kalman(1,:), Kalman(2, :));
legend('Reference', 'day 1', 'day 2', 'day 3', 'day 4');



subplot(2, 1, 2);
plot(elevation_rate(1,:), elevation_rate(2, :));
title('Comparison elevation rate');
xlabel('Time');
ylabel('Elevation rate(rad/s)');
grid on
% hold on
% plot(enc_3_4(1,:), enc_3_4(6, :));
hold on
plot(IQ1531055(1,:), IQ1531055(5, :));
hold on
plot(Estimators(1,:), Estimators(5, :));
hold on
plot(Kalman(1,:), Kalman(5, :));

legend('Reference', 'day 2', 'day 3', 'day 4');