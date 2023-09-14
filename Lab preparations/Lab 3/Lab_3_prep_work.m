clc;
clear all;

syms L2 Jl lp lh Kf Je Jp s

A = [0 1 0 0 0;
     0 0 0 0 0;
     0 0 0 1 0;
     0 0 0 0 0;
  -L2/Jl 0 0 0 0];

B = [0 0;
     0 (lp*Kf/Jp);
     0 0;
     (lh*Kf/Je) 0;
     0 0];

C = [1 0 0 0 0;
     0 1 0 0 0;
     0 0 1 0 0;
     0 0 0 1 0;
     0 0 0 0 1];
 
f = det(s*eye(5) - A);

P =[-1,-2,-3,-4,-5];

L = place(A',C',P)'