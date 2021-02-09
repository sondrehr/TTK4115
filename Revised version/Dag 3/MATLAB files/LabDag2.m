% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 1;
Joystick_gain_y = -1;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

%Poles 
y_1 = -1; % first pole 
y_2 = -2; % second pole

%New parameters 

V_0 = 8; % constant voltage 
K_f = 1/V_0; %Motor force constant
K_1 = K_f/(2*m_p*l_p); %Gain constant
K_2 = l_h*K_f/(m_c*(l_c)^2 +2*m_p*(l_h)^2);
K_pd = -(y_1 + y_2)/K_1; % D gain 
K_pp = (y_1*y_2)/K_1; % P gain

k_11 = 1;
k_12 = 5;
k_13 = 3;
k_21 = 2;
k_22 = 6;
k_23 = 4;

%K = [k_11 k_12 k_13; k_21 k_22 k_23]
A = [0 1 0 0 0;
    0 0 0 0 0;
    0 0 0 0 0;
    1 0 0 0 0;
    0 0 1 0 0];
B = [0 0;
    0 K_1;
    K_2 0;
    0 0;
    0 0];
Q = [15 0 0 0 0;
    0 3 0 0 0
    0 0 10 0 0;
    0 0 0 5 0;
    0 0 0 0 5];
R = [1 0;
    0 1];
p = [-4 -7 -6];

%K = place(A, B, p);
K = lqr(A, B, Q, R);
F = [K(1,1) K(1,3); K(2,1) K(2,3)];
%F = [2 6; 1.4 9];

subplot(2,1,1);

load pitch.mat;
plot(pitch(1,:), pitch(2,:));
hold on;
plot(pitch(1,:), pitch(3,:));
title('Pitch');
xlabel('Time');
ylabel('Pitch(rad)');
grid on;
legend('Reference', 'Value');


subplot(2,1,2);

load elevation_rate.mat;
plot(elevation_rate(1,:), elevation_rate(2,:));
hold on
plot(elevation_rate(1,:), elevation_rate(3,:));
title('Elevation rate');
xlabel('Time');
ylabel('Elevation(rad/s)');
grid on
legend('Reference', 'Value')

