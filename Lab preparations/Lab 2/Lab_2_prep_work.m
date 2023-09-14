clc;
clear all;

syms Lp Lh Kf Jp Je;
Lp = 1;
Lh = 1;
Kf = 0.1
Jp = 3
Je = 4

A = [0 1 0 0 0; 0 0 0 0 0; 0 0 0 0 0; -1 0 0 0 0; 0 0 -1 0 0];
B = [0 0; 0 (Lp*Kf/Jp); (Lh*Kf/Je) 0; 0 0; 0 0];
G = [0 0; 0 0; 0 0; 1 0; 0 1]
C = [1 0 0; 0 0 1];
D = 0;

sys = ss(A,B,C,D)
