%% Load all files and store arrays in workspace
load('Lab_2_case_files\lab_2_case_1_4.mat')

%% Plot figures
figure(1)
plot(helidata(1,:), helidata(2,:), helidata(1,:), helidata(3,:), helidata(1,:), helidata(4,:), helidata(1,:), helidata(5,:), helidata(1,:), helidata(6,:));
grid on;
legend('Travel [rad]', 'Travel rate [rad/s]', 'Pitch [rad]', 'Pitch rate [rad/s]', 'u [rad]');
xlabel('Time [s]');
ylabel('Value');
xlim([0 35]);
ylim([-1 1]);
title('Case 1.1: Q = 1, P = 0');

