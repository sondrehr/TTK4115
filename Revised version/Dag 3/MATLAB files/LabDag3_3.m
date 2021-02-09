
PORT = 12;

J_y = m_c * l_c^2 + 2*m_p*(l_h^2 + l_p^2);
L_4 = l_h * K_f;
K_3 = L_4*V_0/J_y;

K_2 = 0.4;

A_2 = [0 1 0 0 0;
    0 0 0 0 0;
    0 0 0 1 0;
    0 0 0 0 0;
    K_3 0 0 0 0];

B_2 = [0 0;
    0 K_1;
    0 0;
    K_2 0;
    0 0];

C = [1 0 0 0 0; 
    0 1 0 0 0;
    0 0 1 0 0;
    0 0 0 1 0;
    0 0 0 0 1];
 
%p_2 = [-6 -6 -7 -10 -10];
p_3 = eig(A-B*K);
pole1 = -1;
pole2 = -(cosd(15))+1j*sind(15);
pole3 = -(cosd(15))-1j*sind(15);
pole4 = -(cosd(2*15))+1j*sind(2*15);
pole5 = -(cosd(2*15))-1j*sind(2*15);

p_4 = [pole1, pole2, pole3, pole4, pole5] * 20;


L = place(A_2', C', p_4)';

subplot(3, 2, 1);
load Estimators.mat;
load Encoder.mat;
load pitch.mat
load IMU.mat
load elevation_rate.mat
plot(IMU(1,:), IMU(2,:));
hold on
plot(Encoder(1,:), Encoder(4,:));
title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on
hold on

plot(Estimators(1,:), Estimators(2,:));
plot(pitch(1,:), pitch(2,:));
legend('IMU', 'Encoder', 'Estimator', 'reference');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 2);


plot(IMU(1,:), IMU(3,:));
hold on
plot(Encoder(1,:), Encoder(5,:))
title('Pitch rate');
xlabel('Time');
ylabel('Pitch rate(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(3,:));
legend('IMU', 'Encoder', 'Estimator');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 3);

plot(IMU(1,:), IMU(4,:));
hold on
plot(Encoder(1,:), Encoder(6,:));
title('Elevation');
xlabel('Time');
ylabel('Elevation(rad)');
grid on

hold on

plot(Estimators(1,:), Estimators(4,:));
legend('IMU', 'Encoder', 'Estimator');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 4);

plot(IMU(1,:), IMU(5,:));
hold on
plot(Encoder(1,:), Encoder(7,:));
title('Elevation rate');
xlabel('Time');
ylabel('Elevation rate(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(5,:));
plot(elevation_rate(1,:), elevation_rate(2,:));
legend('IMU', 'Encoder', 'Estimator', 'reference');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 5);

plot(IMU(1,:), IMU(6,:));
hold on
plot(Encoder(1,:), Encoder(3,:));
title('Travel rate');
xlabel('Time');
ylabel('Travel(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(6,:));
legend('IMU', 'Encoder', 'Estimator');
