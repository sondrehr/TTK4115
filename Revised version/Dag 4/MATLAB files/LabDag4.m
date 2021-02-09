
subplot(3,2,1);
load Values_while_flying.mat;
load Values_while_stationary.mat;
plot(Values_while_flying(1,:), Values_while_flying(2,:));
title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
hold on
plot(Values_while_stationary(1,:), Values_while_stationary(2,:));
legend('while flying', 'stationary');

subplot(3,2,2);
plot(Values_while_flying(1,:), Values_while_flying(3,:));
title('Pitch rate');
xlabel('Time');
ylabel('Pitch rate(rad/s)');
hold on
plot(Values_while_stationary(1,:), Values_while_stationary(3,:));
legend('while flying', 'stationary');

subplot(3,2,3);
plot(Values_while_flying(1,:), Values_while_flying(4,:));
title('Elevation');
xlabel('Time');
ylabel('Elevation(rad)');
hold on
plot(Values_while_stationary(1,:), Values_while_stationary(4,:));
legend('while flying', 'stationary');

subplot(3,2,4);
plot(Values_while_flying(1,:), Values_while_flying(5,:));
title('Elevation rate');
xlabel('Time');
ylabel('Elevation rate(rad/s)');
hold on
plot(Values_while_stationary(1,:), Values_while_stationary(5,:));
legend('while flying', 'stationary');

subplot(3,2,5);
plot(Values_while_flying(1,:), Values_while_flying(6,:));
title('Travel rate');
xlabel('Time');
ylabel('Travel rate(rad/s)');
hold on
plot(Values_while_stationary(1,:), Values_while_stationary(6,:));
legend('while flying', 'stationary');

R_d = cov(Values_while_flying(2:6,1501:end)');



          
          
          