
close all
figure('Color',[1 1 1])

title('huboplus right foot')
xlabel('x')
ylabel('y')
axis equal
set(gca,'XLim',[-0.2,0.2],'XGrid','on','YLim',[-0.2,0.2],'YGrid','on');

hold on

%%
c = [-0.051823 -0.005];
a = [0.068674 0.076];
rectangle('Position',[c(1)-a(1), c(2)-a(2), 2*a(1), 2*a(2)])

c = [-0.024997 0];
a = [0.0955 0.0434325];
rectangle('Position',[c(1)-a(1), c(2)-a(2), 2*a(1), 2*a(2)],'EdgeColor','r')

c = [-0.044682 0.0355];
a = [0.0758145 0.0355];
rectangle('Position',[c(1)-a(1), c(2)-a(2), 2*a(1), 2*a(2)],'EdgeColor','b')



c = [-0.075749 -0.005];
a = [0.0757485 0.045];
rectangle('Position',[c(1)-a(1), c(2)-a(2), 2*a(1), 2*a(2)])


%%

c = [0.023602 -0.033546];    % center position
a = [0.035 0.0327485 ];    % half width, height
angle = -55;  % angle in degree
w = 2*a(1); h = 2*a(2);
x = c(1)-a(1); y = c(2)-a(2);
xv=[x x+w x+w x   x];
yv=[y y   y+h y+h y];
%plot(xv,yv,'y');
%rotate 
R(1,:)=xv - c(1);
R(2,:)=yv - c(2);
alpha=angle*2*pi/360;
XY=[cos(alpha) -sin(alpha); sin(alpha) cos(alpha)]*R;
XY(1,:) = XY(1,:) + c(1);
XY(2,:) = XY(2,:) + c(2);
plot(XY(1,:),XY(2,:),'m');


c = [0.030742 0.028546];    % center position
a = [0.0240315 0.035 ];    % half width, height
angle = -35;  % angle in degree
w = 2*a(1); h = 2*a(2);
x = c(1)-a(1); y = c(2)-a(2);
xv=[x x+w x+w x   x];
yv=[y y   y+h y+h y];
%plot(xv,yv,'y');
%rotate 
R(1,:)=xv - c(1);
R(2,:)=yv - c(2);
alpha=angle*2*pi/360;
XY=[cos(alpha) -sin(alpha); sin(alpha) cos(alpha)]*R;
XY(1,:) = XY(1,:) + c(1);
XY(2,:) = XY(2,:) + c(2);
plot(XY(1,:),XY(2,:),'r');

%axis([-10 10 10 10])

%%
c = [-0.120497 -0.050];
r = 0.031;
t = 0:0.1:2*pi;
rx = r*cos(t)+c(1);
ry = r*sin(t)+c(2);
plot(rx,ry);

c = [-0.120497 0.040];
r = 0.031;
t = 0:0.1:2*pi;
rx = r*cos(t)+c(1);
ry = r*sin(t)+c(2);
plot(rx,ry);

%%
plot(0,0,'go','LineWidth',1);

%%
quiver(0,0,0,0.2,'g');
quiver(0,0,0.2,0,'g');

%%
%m = 0.0955 -0.024997
%n = 0.0355 + 0.0355
%l = -0.075749 - 0.0757485

xx = [-0.1515 0.0705 0.0705 -0.1515 -0.1515];
yy = [0.071   0.071  -0.081 -0.081  0.071];
plot(xx, yy,'--','Color',[0.5,0.5,0.5]);
 
%%
hold off
