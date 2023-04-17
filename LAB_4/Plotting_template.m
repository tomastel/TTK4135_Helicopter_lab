%% Load all files and store arrays in workspace
load('Lab_4_case_files\lab4_case_1_1.mat')

%% Plot figures
figure(10)
subplot(411)
plot(helidata(1,:), helidata(2,:), helidata(1,:), helidata(3,:));
grid on;
legend('Travel [rad]', 'Travel rate [rad/s]');
xlabel('Time [s]');
ylabel('Value');

subplot(412)
plot(helidata(1,:), helidata(4,:), helidata(1,:), helidata(5,:));
grid on;
legend('Pitch [rad]', 'Pitch rate [rad/s]');
xlabel('Time [s]');
ylabel('Value');

subplot(413)
plot(helidata(1,:), helidata(6,:), helidata(1,:), helidata(7,:));
grid on;
legend('Elevation [rad]', 'Elev. rate [rad/s]');
xlabel('Time [s]');
ylabel('Value');

subplot(414)
plot(helidata(1,:), helidata(8,:), helidata(1,:), helidata(9,:));
grid on;
legend('pc [rad]', 'ec [rad]');
xlabel('Time [s]');
ylabel('Value');
xlim([0 20]);
% ylim([-1 1]);
title('Case 1.1: Q = 1, P = 0');
