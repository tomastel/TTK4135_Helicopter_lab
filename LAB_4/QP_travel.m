% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Flåten

%% Initialization and model definition
init03; % Change this to the init file corresponding to your helicopter

% Discrete time system model. x = [lambda r p p_dot e e_dot]'
dt	= 0.25; % sampling time
A1 = [1 dt 0 0 0 0;
      0 1 (-K_2*dt) 0 0 0;
      0 0 1 dt 0 0;
      0 0 (-K_1*K_pp*dt) (1-K_1*K_pd*dt) 0 0;
      0 0 0 0 1 dt;
      0 0 0 0 (-K_3*K_ep*dt) (1-K_3*K_ed*dt)];
  
B1 = [0 0; 0 0; 0 0; K_1*K_pp*dt 0; 0 0; 0 K_3*K_ep*dt];

% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                                  % Lambda
x2_0 = 0;                                   % r
x3_0 = 0;                                   % p
x4_0 = 0;                                   % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                                   %e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';      % Initial values

% Time horizon and initialization
N  = 40;                               % Time horizon for states
M  = N;                                 % Time horizon for inputs
T = (N+40)*dt;                     % Simulation time
time_steps = [0:dt:T]';            % Array for time steps;
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -pi/2;                   % Lower bound on control
uu 	    = pi/2;                   % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Nonlinear constraints
nonlcon = @elev_con;

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                                % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                                % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);
Q1(1,1) = 1;                              % Weight on state x1
% Q1(2,2) = 0;                              % Weight on state x2
% Q1(3,3) = 0;                              % Weight on state x3
% Q1(4,4) = 0;                              % Weight on state x4
% Q1(5,5) = 0;                              % Weight on state x5
% Q1(6,6) = 0;                              % Weight on state x6
R = [1 0;
     0 1];                                % Weight on input
G = gen_q(Q1,R,N,M);                      % Generate Q, hint: gen_q
c = zeros(N*mx+M*mu,1);                   % Generate c, this is the linear constant term in the QP

%% Calculate LQR gain matrix
Q_lqr = [1 0 0 0 0 0;
         0 1 0 0 0 0;
         0 0 1 0 0 0;
         0 0 0 1 0 0;
         0 0 0 0 1 0;
         0 0 0 0 0 1];
     
R_lqr = [1 0;
         0 1];

K = dlqr(A1,B1, Q_lqr, R_lqr)

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = zeros(N*mx, 1);                    % Generate b
beq(1:6, 1) = A1*x0;

%% Solve QP problem with linear model
% tic
% [z,lambda] = quadprog(2*G, c, [], [], Aeq, beq, vlb, vub, x0); % hint: quadprog. Type 'doc quadprog' for more info 
% t1=toc;

%% Solve QP problem with a nonlinear constraint
f = @(x) 1/2*x'*G*x;                     % Objective function?
tic
z = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, nonlcon);
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+G(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
ufake  = [0; 0; z(N*mx+1:N*mx+M*mu)]; % Control input from solution
u = zeros(N+1,2);
for i = 1:size(u,1)
    u(i,1) = ufake(2*i-1);
    u(i,2) = ufake(2*i);
end

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x4 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x4 from solution

num_variables = 5/dt;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u(:,1); zero_padding];
u2   = [zero_padding; u(:,2); zero_padding];
x1  = [x1_0*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

u_ts = timeseries([u1 u2], time_steps);
x_ts = timeseries([x1 x2 x3 x4 x5 x6], time_steps);

%% Plotting
t = 0:dt:dt*(length(u1)-1);

figure(2)
subplot(811)
stairs(t,u1),grid
ylabel('pc')
subplot(812)
stairs(t,u2),grid
ylabel('ec')
subplot(813)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(814)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(815)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(816)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')
subplot(817)
plot(t,x5,'m',t,x5','mo'),grid
xlabel('tid (s)'),ylabel('e')
subplot(818)
plot(t,x6,'m',t,x6','mo'),grid
xlabel('tid (s)'),ylabel('edot')

function [c, ceq] = elev_con(x)
    alpha = 0.2; betta = 20; lambda_t = 2*pi/3; N=40; nx = 6;
    c = zeros(N,1);
    for i=1:N
        c(i) = alpha*exp(-betta*(x(nx*(i-1)+1)-lambda_t)^2) - x(nx*(i-1)+5);
    end
    ceq = [];
end
