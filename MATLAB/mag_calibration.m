% this file is meant to display the amazing utility of sphereFit.m
function a = mag_calibration(filename)
data = load(filename);
X = data(:,2:end);

[Center_LSE,Radius_LSE] = sphereFit(X);
 
figure(42);clf;
plot3(X(:,1),X(:,2),X(:,3),'r.')
hold on;daspect([1,1,1]);
[Base_X,Base_Y,Base_Z] = sphere(20);
surf(Radius_LSE*Base_X+Center_LSE(1),...
    Radius_LSE*Base_Y+Center_LSE(2),...
    Radius_LSE*Base_Z+Center_LSE(3),'faceAlpha',0.3,'Facecolor','m')
title({['Sphere fit with ' num2str(size(X,1)) ' points: '];...
    ['Predicted Center: ' num2str(Center_LSE) ', Radius: ' num2str(Radius_LSE)]});
view([45,28])
legend({'Data','LSE Sphere'},'location','W')
a = 1;