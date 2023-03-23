%% Load all files and store arrays in workspace
% data1 = load('pikk.mat');

%% Plot figures
figure(1)
plot(data1.ans)
grid on;
legend('Pitch [rad]', 'Step response');
xlabel('Time [s]');
ylabel('Value');
xlim([0 10])
title('Case 1.1.1: \lambda_1 = \lambda_2 = -1');

