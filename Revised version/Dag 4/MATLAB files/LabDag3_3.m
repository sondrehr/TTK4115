

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
 
p_2 = [-5 -6 -7 -7 -8]; 

L = place(A_2', C', p_2)';


subplot(3, 2, 1);
load Estimators.mat;
load Encoder.mat;
load pitch.mat
load elevation_rate.mat
plot(Encoder(1,:), Encoder(4,:));
title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on

hold on

plot(Estimators(1,:), Estimators(2,:));
plot(pitch(1,:), pitch(2,:));
legend('Encoder', 'Estimators',  'Reference');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 2);

plot(Encoder(1,:), Encoder(5,:))
title('Pitch rate');
xlabel('Time');
ylabel('Pitch(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(3,:));
legend('Encoder', 'Estimators');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 3);

plot(Encoder(1,:), Encoder(6,:));
title('Elevation');
xlabel('Time');
ylabel('Elevation(rad)');
grid on

hold on

plot(Estimators(1,:), Estimators(4,:));
legend('Encoder', 'Estimators');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 4);

plot(Encoder(1,:), Encoder(7,:));
title('Elevation rate');
xlabel('Time');
ylabel('Elevation(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(5,:));
plot(elevation_rate(1,:), elevation_rate(2,:));
legend('Encoder', 'Estimators', 'Reference');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

subplot(3, 2, 5);

plot(Encoder(1,:), Encoder(3,:));
title('Travel rate');
xlabel('Time');
ylabel('Travel(rad/s)');
grid on

hold on

plot(Estimators(1,:), Estimators(6,:));
legend('Encoder', 'Estimators');
