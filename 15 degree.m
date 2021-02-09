p_3 = eig(A-B*K);
pole1 = -1;
pole2 = -(cosd(15))+1j*sind(15);
pole3 = -(cosd(15))-1j*sind(15);
pole4 = -(cosd(2*15))+1j*sind(2*15);
pole5 = -(cosd(2*15))-1j*sind(2*15);

p_4 = [pole1, pole2, pole3, pole4, pole5] * 20;


L = place(A_2', C', p_4)';