%The code used to convert from a continuous state space to a discrete one.
A_3 = [0 1 0 0 0 0;
       0 0 0 0 0 0;
       0 0 0 1 0 0;
       0 0 0 0 0 0;
       0 0 0 0 0 1;
       K_3 0 0 0 0 0];

B_3 = [0 0;
       0 K_1;
       0 0;
       K_2 0;
       0 0;
       0 0];

C_2 = [1 0 0 0 0 0; 
       0 1 0 0 0 0;
       0 0 1 0 0 0;
       0 0 0 1 0 0;
       0 0 0 0 0 1];
   
%Above we have expanded the original A,B and C matrices to include the
%extra travel state

c_syst = ss(A_3, B_3, C_2, 0);
d_syst = c2d(c_syst, 0.002);

